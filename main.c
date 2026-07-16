#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

const char* DEFAULT_FILE = "index.html";

char* path(char *req) {
    char *start, *end;

    for (start = req; start[0] != ' '; start++) {
        if (!start[0]) {
            return NULL;
        }
    }

    start++;

    char *last_slash = NULL;
    char *last_dot = NULL;

    for (end = start; end[0] != ' '; end++) {
        switch (end[0]) {
            case '/':
                last_slash = end;
                break;
            case '.':
                last_dot = end;
                break;
            case '\0':
                return NULL;
            }
    }

    if (last_slash == NULL) {
        return NULL;
    }

    if (last_dot == NULL || last_slash > last_dot) {
        last_slash++;

        if (last_slash + strlen(DEFAULT_FILE) > req + strlen(req)) {
            return NULL;
        }

        memcpy(last_slash, DEFAULT_FILE, strlen(DEFAULT_FILE) + 1);
    } else {
        end[0] = '\0';
    }

    return start + 1;
}

void print_file(const char *path) {
    int fd = open(path, O_RDONLY);

    if (fd == -1) {
        printf("Error opening file %s\n", path);
        return;
    }

    struct stat metadata;

    if (fstat(fd, &metadata) == -1) {
        printf("Error getting file stats\n");
        goto metaerror;
    }

    char *buf = malloc(metadata.st_size + 1);

    if (buf == NULL) {
        printf("Memory allocation failed\n");
        goto buffererror;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    }

    ssize_t bytes_read = read(fd, buf, metadata.st_size);

    if (bytes_read == -1) {
        printf("Error reading file\n");
        goto buffererror;
    }

    buf[bytes_read] = '\0';
    printf("\n%s contents:\n\n%s\n", path, buf);

    buffererror:
        free(buf);

    metaerror:
        close(fd);
}

int main() {
    char req1[] = "GET / HTTP/1.1\nHost: example.com";
    print_file(path(req1));

    char req2[] = "GET /jeff HTTP/1.1\nHost: example.com";
    print_file(path(req2));

    char req3[] = "GET /static/images/logo.png HTTP/1.1\nHost: example.com";
    printf("%s\n", path(req3));
    print_file(path(req3));


    return 0;
}