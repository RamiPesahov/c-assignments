#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOT_FOUND -1

   char *prev_song; 
    char *cur_song;
    char **queue_songs;
    int capacity; // max number of elements in the queue
    int front;
    int rear;
    int size;

void create_queue(Queue *q) { 

    if(q == NULL) {

        printf("ERROR: NULL Queue pointer.\n");
        exit(1);
    }
    
    q -> queue_songs = (char **) malloc(MAX_Q_SIZE * sizeof(char *));
    q -> prev_song = NULL;
    q -> cur_song = NULL;

    if((q -> queue_songs) == NULL) {

        printf("ERROR: Failed to allocate songs array.\n");
        exit(1);        
    }

    q -> front = 0;
    q -> size = 0;
    q -> rear = 0;
    q -> capacity = MAX_Q_SIZE;
}

void queue_add_song(Queue *q, Database *db, const char *title) {

    if(q == NULL) {

        printf("ERROR: NULL queue pointer.\n");
        exit(1);
    }

    if (db == NULL) {
        
        printf("ERROR: NULL database pointer.\n");
        exit(1);
    }
    
    if(title == NULL) {

        printf("ERROR: NULL title.\n");
        exit(1);
    }

    
    int found_song = NOT_FOUND;  
    for (int i = 0; i < db -> count; i++)
    {
        if(strcmp((db -> songs)[i] -> title, title) == 0) {
            found_song = i;
            break;    
        }
    }
    
    if(found_song == NOT_FOUND){
        
        printf("ERROR: Song was not found in database.\n");
        return;
    }
    
    if((q -> size) >= (q -> capacity)) {

        printf("ERROR: Queue is full.\n");
        return;
    }
    
    (q -> queue_songs)[q -> rear] = (char *) malloc((strlen(title) + 1) * sizeof(char)); // + 1 because we need to alloacte for \0 char

    if((q -> queue_songs)[q -> rear] == NULL) {

        printf("ERROR: Failed to allocate memory for song title.\n");
        return; // should we exit or return
    }

    strcpy((q -> queue_songs)[q -> rear], title);

    (q -> size)++;
    (q -> rear) = (q -> rear + 1) % (q -> capacity);
}

void queue_next_song(Queue *q) { // didn't finish yet

    if(q == NULL) {

        printf("ERROR: NULL queue pointer.\n");
        exit(1);
    }

    if((q -> size) == 0) {

        printf("ERROR: Queue is empty.\n");
        return;
    }

    free(q -> prev_song);
    q -> prev_song = q -> cur_song;
    q -> cur_song = q -> queue_songs[q -> front];
    q -> queue_songs[q -> front] = NULL; 
    q -> front  = (q -> front + 1) % q -> capacity;
    (q -> size)--;
}


void print_queue(const Queue *q) {
    
    if (q == NULL)
    {
        printf("ERROR: NULL queue pointer.\n");
        exit(1);
    }
    
    if(q -> size == 0) {

        printf("Queue is empty.\n");
        return; // check if it's good
    }

    printf("Queue contents:\n");
    for (int i = 0; i < q -> size; i++)
    {
        int temp = ((q -> front) + i) % (q -> capacity); 
        printf("%d. %s\n",i + 1,q -> queue_songs[temp]);
    }
    
}

void free_queue(Queue *q) {

    if(q == NULL) {

        printf("ERROR: NULL queue pointer.\n");
        exit(1);
    }

    if(q -> prev_song != NULL) {

        free(q -> prev_song);
        q -> prev_song = NULL;
    }

    if(q -> cur_song != NULL) {

        free(q -> cur_song);
        q -> cur_song = NULL;
    } 

    if((q -> queue_songs) != NULL) {
       
        for (int i = 0; i < q -> size; i++) {

            int position = ((q -> front) + i) % (q -> capacity);

                free((q -> queue_songs)[position]);
                (q -> queue_songs)[position] = NULL;
        }
    }
        
    free(q);
    q = NULL;  
}