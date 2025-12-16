#include "song.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void set_song(Song *s, const char *title, const char *artist,
              int duration, Genre genre) {

    printf("ERROR: NULL Song pointer.\n");

    printf("ERROR: NULL title pointer.\n");

    printf("ERROR: NULL artist pointer.\n");

    printf("ERROR: Failed to allocate memory for title.\n");

    printf("ERROR: Failed to allocate memory for artist.\n");
}


void print_song(const Song *s) {
    printf("ERROR: NULL Song pointer.\n");

    printf("ERROR: Song has NULL fields.\n");

    printf("Title: %s, Artist: %s, Duration: %ds, Genre: %s\n",
           , , ,
           );
}

void free_song(Song *s) {
    printf("ERROR: NULL Song pointer.\n");
}
