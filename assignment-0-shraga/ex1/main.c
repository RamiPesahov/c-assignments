#include <stdio.h>

#ifdef _WIN32
#define NL "\n"
#elif __linux__
#define NL "\r\n"
#endif

int main(){
    printf("This is my first C program"NL);
    return 0;
}