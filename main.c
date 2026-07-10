#include <string.h>
#include <stdio.h>

const char* DEFAULT_FILE = "index.html";

char* path(char *req, size_t req_len) {
    char *start, *end;

    for (start = req; start[0] != ' '; start++) {
        if (!start[0]) {
            return NULL;
        }
    }

    start++;

    for (end = start; end[0] != ' '; end++) {
        if (!end[0]) {
            return NULL;
        }
    }

    if (end[-1] != '/') {
        end[0] = '/';
        end++;
    }

    if (end + strlen(DEFAULT_FILE) > req + req_len) {
        return NULL;
    }

    memcpy(end, DEFAULT_FILE, strlen(DEFAULT_FILE) + 1);

    return start + 1;
}

int main() {
    char *header = "HTTP/1.1 200 OK";

    printf("%s\n", header);

    char req1[] = "GET /jeff HTTP/1.1\nHost: example.com";
    printf("Should be \"jeff/index.html\": \"%s\"\n", path(req1, strlen(req1)));

    char req2[] = "GET /jeff/ HTTP/1.1\nHost: example.com";
    printf("Should be \"jeff/index.html\": \"%s\"\n", path(req2, strlen(req2)));

    char req3[] = "GET / HTTP/1.1\nHost: example.com";
    printf("Should be \"index.html\": \"%s\"\n", path(req3, strlen(req3)));

    char req4[] = "GET /jeff ";
    printf("Should be \"(null)\": \"%s\"\n", path(req4, strlen(req4)));

    return 0;
}