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

int subString(char *str, char *sub_str){

    int index = 0, start_str = 0;
    for (int i = 0; str[i] != '\0' ||  sub_str[index] != '\0'; i++) {
        
        if(str[i] == sub_str[index]) {

            index++;
            start_str++;
        } 
        else {

            index = 0;
            start_str - 0;
        }
    }
    return (start_str == strlen(str));
}


int countstr(char *arr[], char *s) {

    int res = 0;
    while(*arr) {

        res += subString(*arr, s);
        arr++;
    }
    return res;
}