#include <stdio.h>

#ifdef _WIN32
#define NL "\n"
#elif __linux__
#define NL "\r\n"
#endif

int main(){
    printf("   /\\"NL
            "  /  \\"NL
            " /    \\"NL
            "/      \\"NL
            "--------"NL
            "|      _ |"NL
            "|     |_||"NL
            "|  __    |"NL
            "| |  |   |"NL
            "| |  |___|"NL);

    return 0;
}