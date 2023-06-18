#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>

int main() {
    const char *path = "exec.c";
    struct stat fileStat;

    if (stat(path, &fileStat) == 0) {
        printf("File size: %lld bytes\n", (long long)fileStat.st_size);
        printf("File permissions: %o\n", fileStat.st_mode & 0777);
    } else {
        perror("stat");
    }
    return 0;
}
