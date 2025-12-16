#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

void create_database(Database *db, int initial_capacity) {
    
    if(db == NULL) {

        printf("ERROR: NULL Database pointer.\n");
        exit(1);
    }

    db -> songs = (Song *) malloc(initial_capacity * sizeof(Song *));
   
    if((db -> songs) == NULL) {

        printf("ERROR: Failed to allocate songs array.\n");
        exit(1);
    }
    
    db -> capacity = 0;
    db -> count = 0;
}


void db_add_song(Database *db, Song *s) {

    printf("ERROR: NULL Database pointer.\n");

    printf("ERROR: NULL Song pointer.\n");

    printf("ERROR: Failed to expand database.\n");
}

void db_remove_song(Database *db, const char *title) {
    printf("ERROR: NULL Database pointer.\n");

    printf("ERROR: NULL title.\n");

    printf("ERROR: Song not found in database.\n");

}

void free_db(Database *db) {

    printf("ERROR: NULL Database pointer.\n");

}
