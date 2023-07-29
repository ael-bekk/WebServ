#ifndef __HEADER_HPP__
#define __HEADER_HPP__

#include "../../../../bits/API.hpp"

class __header {
    private:
        std::string                         Method;
        std::string                         Connection;
        std::string                         Host;
        std::string                         Port;
        std::string                         path;
        std::string                         query;
        std::map<std::string, std::string>  Cookies;

        std::string                         Content_type;
        int                                 Content_Length;
        std::string                         unit;  // Content-Range: <unit> <range-start>-<range-end>/<size>
        int                                 Keep_Alive_time_out;
        int                                 keep_Alive_max;
        std::string                         Last_Modified;

    public:
        __header();
        ~__header();

        std::string                         get_Method();
        std::string                         get_Connection();
        std::string                         get_Host();
        std::string                         get_Port();
        std::string                         get_path();
        std::string                         get_query();
        std::map<std::string, std::string>  get_Cookies();
        std::string                         get_Content_type();
        int                                 get_Content_Length();
        std::string                         get_unit();
        int                                 get_Keep_Alive_time_out();
        int                                 get_keep_Alive_max();
        std::string                         get_Last_Modified();

        void                                set_Method(std::string Method);
        void                                set_Connection(std::string Connection);
        void                                set_Host(std::string Host);
        void                                set_Port(std::string Port);
        void                                set_path(std::string path);
        void                                set_query(std::string query);
        void                                set_Cookies(std::map<std::string, std::string> Cookies);
        void                                set_Content_type(std::string Content_type);
        void                                set_Content_Length(int Content_Length);
        void                                set_unit(std::string unit);
        void                                set_Keep_Alive_time_out(int Keep_Alive_time_out);
        void                                set_keep_Alive_max(int keep_Alive_max);
        void                                set_Last_Modified(std::string Last_Modified);

        void                                _insert();
};

#endif