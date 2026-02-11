#include <stdio.h>

char toupper(char c){
    return c ^ 0x20;
}

void correct(char * c){
    int eos = 1;
    while(c != '\0'){
        if(eos && ('a' < *c) && (*c < 'z')) {
            *c = toupper(*c);
            eos = 0;
        }
        if(*c == '.') eos = 1;
        c++;
    }
    return;
}

int countstr(char *arr[], char *s){
    int count;
    for(int idx = 0; arr[idx] != NULL; idx++){
        if(strlen(arr[idx]) < strlen(s)) continue;
        for(int i = 0; i < strlen(arr[idx]) - strlen(s); i++){
            if(strcmp(arr[idx] + i, s) != 0) count++;
        }
    }
    return count;
}