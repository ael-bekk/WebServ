#include "check_err.hpp"

__check_err::__check_err(__response &obj) : response(&obj) {}

std::string __check_err::insert_html_document(struct dirent* list, std::string path) {
    std::string type;
    std::string href(list->d_name);
    std::string new_path(path + list->d_name);
    DIR* test;
    int count(0);

    if ((test = opendir((path + list->d_name).c_str()))) {
        href += "/";
        while (readdir(test) && ++count < 3);
        type = ICONS_HOST + ((count == 3) ? "folder.png" : "empty_folder.png");
    } else {

        if (new_path.rfind('.') != std::string::npos)
            type = new_path.substr(new_path.rfind('.') + 1);

        if (Global().check_icon(type))
            type = ICONS_HOST + type + ".png";
        else {
            COUNT_CONTENT_LENT(new_path, count)
            type = ICONS_HOST + (count ? "file.png" : "empty_file.png");
        }
    }
    closedir(test);
    return HTML_DOCUMENT(type, href, list->d_name);
}

std::string __check_err::autoindex(std::string path) {
    std::string path_autoindex;
    DIR* dir = opendir(path.c_str());
    struct dirent* list;
    std::ofstream outfile;

    NEW_NAME(path_autoindex);
    mkdir("./Tmp", S_IRWXU | S_IRWXG);
    std::string tmp = "./Tmp/" + path_autoindex + ".html";
    Global().tmp_file[this->sock] = tmp;
    // std::cout << tmp << std::endl;
    outfile.open(tmp.c_str());
    if (!outfile.is_open() || dir == NULL) {
        Global().add_ResponseHeader(this->sock, "status", HTTP_404_NOT_FOUND);
        return "";
    }

    outfile << HTML_UP_BODY(path);
    while ((list = readdir(dir)) != NULL)
        if (list->d_name != CUR_DIR && list->d_name != OLD_DIR)
            outfile << this->insert_html_document(list, path);
    outfile << HTML_DOWN_BODY;

    closedir(dir);
    return tmp;
}

void __check_err::check_get() {
    std::string path = this->response->get_path();
    __location *location = this->response->get_location();
    int             status(0);
    DIR *test;

    // std::cout << path << std::endl;
    if AUTO_INDEXING() {
        std::vector<std::string> indexes(location->get_index());
        for (int i = 0; i < indexes.size() && !status; i++) {
            FILE_OPENED(std::string(path + indexes[i]), status)
            if (status) path += indexes[i];
        }
        if (!status) path = this->autoindex(path);
    } else if ((test = opendir((path).c_str()))) {
        Global().add_ResponseHeader(this->sock, "status", HTTP_301_MULTIPLE_CHOICE);
        this->response->set_path(this->response->get_req_path() + "/");
        closedir(test);
        return;
    }
    FILE_OPENED(path, status)
    if (!status)
        Global().add_ResponseHeader(this->sock, "status", HTTP_404_NOT_FOUND);
    else
        this->response->set_path(path);
}

void __check_err::check_post() {
    if (!TRANSFER_CHUNKED() && !TRANSFER_CONTENT_LENT())
        Global().add_ResponseHeader(this->sock, "status", HTTP_411_LENGTH_REQUIRE);
}

void __check_err::check_delete(std::string FolderPath) {
    DIR *dir = NULL;
    struct dirent *entry;
   
    if (!(dir = opendir(FolderPath.c_str()))) {
        if (!remove(FolderPath.c_str())) return;
        Global().add_ResponseHeader(this->sock, "status", HTTP_403_FORBIDDEN);
        return;
    }

    while (!ERROR_OCCURRED() && dir && (entry = readdir(dir)))
        if (entry->d_name != CUR_DIR && entry->d_name != OLD_DIR ) {
            std::string entryPath = std::string(FolderPath) + "/" + entry->d_name;

            if (entry->d_type == DT_DIR)
                this->check_delete(entryPath);
            else if (remove(entryPath.c_str()))
                Global().add_ResponseHeader(this->sock, "status", HTTP_403_FORBIDDEN);
        }
    if (!ERROR_OCCURRED()) {
        closedir(dir);
        if (rmdir(FolderPath.c_str()))
            Global().add_ResponseHeader(this->sock, "status", HTTP_403_FORBIDDEN);
    }
}

bool __check_err::header_err() {
    if (!IS_METHOD(Global().get_RequestHeader(this->sock, "Method"))) {
        if IS_OTHER_METHOD(Global().get_RequestHeader(this->sock, "Method"))
            Global().add_ResponseHeader(this->sock, "status", HTTP_501_NOT_IMPLEMENTED);
        else
            Global().add_ResponseHeader(this->sock, "status", HTTP_400_BAD_REQUEST);
    } else if (Global().get_RequestHeader(this->sock, "Path").empty())
        Global().add_ResponseHeader(this->sock, "status", HTTP_400_BAD_REQUEST);
    else if (Global().get_RequestHeader(this->sock, "Http") != "HTTP/1.1")
        Global().add_ResponseHeader(this->sock, "status", HTTP_505_HTTP_VERSION_NOT_SUPPORTED);
    else
        return false;
    return true;
}

void __check_err::check_errors() {
    if ERROR_OCCURRED() return;
    this->sock = this->response->get_sock();
    std::map<std::string, bool> allowed;

    if (this->response && this->response->get_location())
        allowed = this->response->get_location()->get_allow_methods();

    if (this->header_err())
        return;
    else if (allowed[GET_REQ_METHOD()]) {
        if POST()       this->check_post();
        if GET()        this->check_get();
        if DELETE()     this->check_delete(this->response->get_path());
    } else
        Global().add_ResponseHeader(this->sock, "status", HTTP_405_METHOD_NOT_ALLOWED);
}