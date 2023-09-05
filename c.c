#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int main() {
    int fd[2];
    char s[100];
    pipe(fd);
    if (!fork())
    {
        read(0, s, 10);
        write(1, s, 10);
        write(1, "\n", 1);
        while(1);
    }
    read(0, s, 10);
    write(1, "\n", 1);
    write(1, s, 10);
    return 0;
}