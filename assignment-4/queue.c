#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

   char *prev_song; 
    char *cur_song;
    char **queue_songs;
    int capacity;
    int front;
    int rear;
    int size;

void create_queue(Queue *q) {

    if(q == NULL) {

        printf("ERROR: NULL Queue pointer.\n");
        exit(1);
    }
    
    q -> queue_songs = (char **) malloc(MAX_Q_SIZE * sizeof(char *));

    if((q -> queue_songs) == NULL) {

        printf("ERROR: Failed to allocate songs array.\n");
        exit(1);        
    }

    q -> front = 0;
    q -> size = 0;
    q -> rear = 0;

    // q -> capacity = ;
    // q -> prev_song = ;
    // q -> cur_song = ;
    
}


void queue_add_song(Queue *q, Database *db, const char *title) {

    printf("ERROR: NULL queue pointer.\n");

    printf("ERROR: NULL database pointer.\n");

    printf("ERROR: NULL title.\n");

    printf("ERROR: Song was not found in database.\n");

    printf("ERROR: Queue is full.\n");

    printf("ERROR: Failed to allocate memory for song title.\n");
}



void queue_next_song(Queue *q) {

    printf("ERROR: NULL queue pointer.\n");

    printf("ERROR: Queue is empty.\n");
}


void print_queue(const Queue *q) {
    printf("ERROR: NULL queue pointer.\n");

    printf("Queue is empty.\n");

    printf("Queue contents:\n");
}

void free_queue(Queue *q) {
    printf("ERROR: NULL queue pointer.\n");
}
