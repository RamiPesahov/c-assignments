#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

#define NOT_FOUND -1

void create_database(Database *db, int initial_capacity) {
    
    if(db == NULL) {

        printf("ERROR: NULL Database pointer.\n");
        exit(1);
    }

    db -> songs = (Song **) malloc(initial_capacity * sizeof(Song *));
   
    if((db -> songs) == NULL) {

        printf("ERROR: Failed to allocate songs array.\n");
        exit(1);
    }
    
    db -> capacity = initial_capacity;
    db -> count = 0;
}

void db_add_song(Database *db, Song *s) {

    if(db == NULL) {

        printf("ERROR: NULL Database pointer.\n");
        exit(1);
    }

    if (s == NULL) {

        printf("ERROR: NULL Song pointer.\n");
        exit(1);
    }

    if((db -> count) == (db -> capacity)) { 

        int new_capacity = (db -> capacity) * 2;
        Song **temp = (Song **) realloc((db -> songs) ,new_capacity * sizeof(Song *));
    
        if (temp == NULL)
        {
            printf("ERROR: Failed to expand database.\n");
            exit(1);
        }       

        (db -> songs) = temp;
        db -> capacity = new_capacity;
    }

    *((db -> songs) + (db -> count))  = s; // going to the end of the array of songs and setting there new song
    (db -> count)++;
}

void db_remove_song(Database *db, const char *title) {
    
    if(db == NULL) {
        printf("ERROR: NULL Database pointer.\n");
        exit(1);
    }

    if(title == NULL) {
        printf("ERROR: NULL title.\n");
        exit(1);
    }

    int found_removal = NOT_FOUND; // didn't find yet

    for (int i = 0; i < (db -> count) ; i++) {
        
        Song *temp = (db -> songs)[i];

        if((strcmp(temp -> title, title) == 0) && found_removal == NOT_FOUND) {

            found_removal = i;
            
            free(temp -> artist);
            free(temp -> title);
            free(temp);

            break;
        } 
    }

    if(found_removal == NOT_FOUND) { // didn't find the song

        printf("ERROR: Song not found in database.\n");
        return;
    }

    for (int i = found_removal; i < (db -> count) - 1; i++) // shifting the entries
    {
        (db -> songs)[i] = (db -> songs)[i + 1];
    }
    
    (db -> count)--;
}

void free_db(Database *db) {

    if(db == NULL) {

        printf("ERROR: NULL Database pointer.\n");
        exit(1);
    }

    for(int i = 0; i < (db -> count); i++) { // we have only count numbers of songs in the array in size capacity

        free((db -> songs)[i] -> title);
        (db -> songs)[i] -> title = NULL;

        free((db -> songs)[i] -> artist);
        (db -> songs)[i] -> artist = NULL;

        free((db -> songs)[i]);
        (db -> songs)[i] = NULL;
    }

    free(db -> songs);

    db -> songs = NULL;
}
