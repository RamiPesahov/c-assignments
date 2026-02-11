#include <stdio.h>
#include <string.h>

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
            if(strncmp(arr[idx] + i, s, strlen(s)) != 0) count++;
        }
    }
    return count;
}

int countstr(char *arr[], char *s){
    int count;
    for(int idx = 0; arr[idx] != NULL; idx++){
        if(strlen(arr[idx]) < strlen(s)) continue;
        if(strstr(arr[idx], s) != NULL) count++;
    }
    return count;
}

int subString(char *str, char *sub_str){
    int index = 0;
    for (int i = 0; str[i] != '\0' ; i++) {
        if (sub_str[index] == '\0') break;

        if(str[i] == sub_str[index]) index++;
        else index = 0;

    }
    return (index == strlen(str));
}

int countstr(char *arr[], char *s) {

    int res = 0;
    while(*arr) {

        res += subString(*arr, s);
        arr++;
    }
    return res;
}


