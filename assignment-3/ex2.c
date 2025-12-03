#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING_LENGTH (10 + 1) // +1 because of the end-of-string char
#define MAX_NUMBER_OF_STRINGS_IN_POOL 20

int get_pool_of_strings(char string_pool[][MAX_STRING_LENGTH]);
void string_lowercase(char string[], int size);
int num_of_rotations(char search[], char pool[][MAX_STRING_LENGTH], int num_of_strings);
int is_rotation(char search[], char string_in_pool[]);

int main() {
    char search_string[MAX_STRING_LENGTH];
    char string_pool[MAX_NUMBER_OF_STRINGS_IN_POOL][MAX_STRING_LENGTH];
    
    char search_string_copy[MAX_STRING_LENGTH];
    char string_pool_copy[MAX_NUMBER_OF_STRINGS_IN_POOL][MAX_STRING_LENGTH];

    int rotations = 0;
    
    printf("Enter the search string:\n");
    scanf("%10[^\n]",search_string);
    getchar(); // flush the \n
    
    int num_of_strings = get_pool_of_strings(string_pool);
    
    strcpy(search_string_copy, search_string);

    for (int i = 0; i < num_of_strings; i++)
    {
        strcpy(string_pool_copy[i],string_pool[i]);
    }
    
    string_lowercase(search_string_copy,strlen(search_string_copy));

    for (int i = 0; i < num_of_strings; i++)
    {
        string_lowercase(string_pool_copy[i],strlen(string_pool_copy[i]));
    }
    
    rotations = num_of_rotations(search_string_copy, string_pool_copy,num_of_strings);
    
    printf("Number of rotations of \"%s\" in the strings pool is: %d\n",search_string,rotations);

    return 0;
}


int get_pool_of_strings(char string_pool[][MAX_STRING_LENGTH]) { // This function handles scanning the pool of strings and returns how much strings are in the pool 

     printf("Enter the strings pool:\n");
     int i;
     for (i = 0; i < MAX_NUMBER_OF_STRINGS_IN_POOL; i++)
     {
        if(scanf("%10[^\n]",string_pool[i]) == EOF) {
            break;
        }

        getchar(); // flush the \n    
     }
     getchar(); // flush the \n
     return i;
}

void string_lowercase(char string [], int size) {

    for (int i = 0; i < size; i++)
    {
        string[i] = tolower(string[i]);
    }
}

int num_of_rotations(char search[], char pool[][MAX_STRING_LENGTH], int num_of_strings) {

    int count = 0;

    for (int i = 0; i < num_of_strings; i++)
    {
        count += is_rotation(search,pool[i]);
    }
    return count;
}

int is_rotation(char search[], char string_in_pool[]) {

    size_t len = strlen(search);
    if(len != strlen(string_in_pool))
        return 0;

    if(len == 0)
        return 1;

    char concat_string [2 * MAX_STRING_LENGTH + 1]; // +1 beacuse of the end_of_string character
    strcpy(concat_string,search); // for example if search = "hello", so concat_string = "hello"
    strcat(concat_string,search); // for example if search = "hello", so concat_string = "hellohello"

    if (strstr(concat_string,string_in_pool) != NULL) // checks if string_in_pool in concat_string 
        return 1;

    return 0;    
}