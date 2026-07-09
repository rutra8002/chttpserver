#include <unistd.h>
#include <stdio.h>

int main() {
    int asd = 67;
    // write(1, asd, 420);
    // write(1, "\n", 1);
    // write(1, asd+420, 6000);
    printf("%s\n", (char *)&asd);

    char nasf = 'C';

    printf("%d\n", nasf);

    char* ggigga = "C++";

    printf("%d%d%d", *(ggigga+0), *(ggigga+1), *(ggigga+2));

    return 0;
}