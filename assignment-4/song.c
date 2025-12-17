#include "song.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void set_song(Song *s, const char *title, const char *artist,
              int duration, Genre genre) {

    // if any of the inputs is NULL and/or any malloc fails -> print and error message and exit(1)
    if(s == NULL) {

        printf("ERROR: NULL Song pointer.\n");
        exit(1);
    }

    if(title == NULL) {

        printf("ERROR: NULL title pointer.\n");
        exit(1);
    }

    if(artist == NULL) {

        printf("ERROR: NULL artist pointer.\n");
        exit(1);
    }

    int title_length = strlen(title);
    int artist_length = strlen(artist);

    // plus 1 because need to allocate also for the \0 of the end of the strings

    s -> title = (char *) malloc((title_length + 1) * sizeof(char));
    s -> artist = (char *) malloc((artist_length + 1) * sizeof(char));
    
    if((s -> title) == NULL) {

        printf("ERROR: Failed to allocate memory for title.\n");
        exit(1);
    }
    
    if((s -> artist) == NULL) {

        printf("ERROR: Failed to allocate memory for artist.\n");
        exit(1);
    }
    
    strcpy(s -> title, title);
    strcpy(s -> artist, artist);
    s -> genre = genre;
    s -> duration_in_seconds = duration;

}


void print_song(const Song *s) {

    if (s == NULL) {

        printf("ERROR: NULL Song pointer.\n");
        exit(1);
    } 

    if ((s -> title) == NULL || (s -> artist) == NULL) {
        
        printf("ERROR: Song has NULL fields.\n");
        exit(1);
    }
    
    printf("Title: %s, Artist: %s, Duration: %ds, Genre: %s\n", s -> title, s -> artist, s -> duration_in_seconds, s -> genre);
}

void free_song(Song *s) {

    if(s == NULL) {
        
        printf("ERROR: NULL Song pointer.\n");
        exit(1);
    }

    free(s -> title);
    free(s -> artist);
    free(s);

    s -> title = NULL;
    s -> artist = NULL;
    s = NULL;
}
