#include <unistd.h>

int main() {
    char* asd = "Hello World!";
    write(1, asd, 420);
    write(1, "\n", 1);
    write(1, asd+420, 6000);
    return 0;
}