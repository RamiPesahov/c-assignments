#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "song.h"
#include "database.h"
#include "queue.h"

#ifdef DEBUG

void test_songs();
void test_database();
void test_queue();
void print_separator(const char *title);

int main() {
    printf("=== COMPREHENSIVE TEST SUITE ===\n\n");
    
    test_songs();
    test_database();
    test_queue();
    
    printf("\n=== ALL TESTS COMPLETED ===\n");
    return 0;
}

void print_separator(const char *title) {
    printf("\n");
    printf("=================================================\n");
    printf("  %s\n", title);
    printf("=================================================\n");
}

void test_songs() {
    print_separator("TESTING SONG FUNCTIONS");
    
    // Test 1: Create and print songs with different genres
    printf("\n--- Test 1: Creating songs with all genres ---\n");
    Song * song1 = malloc(sizeof(Song));
    Song * song2 = malloc(sizeof(Song));
    Song * song3 = malloc(sizeof(Song)); 
    Song * song4 = malloc(sizeof(Song)); 
    Song * song5 = malloc(sizeof(Song));
    
    set_song(song1, "Blinding Lights", "The Weeknd", 202, POP);
    printf("Song 1: ");
    print_song(song1);
    
    set_song(song2, "Bohemian Rhapsody", "Queen", 354, ROCK);
    printf("Song 2: ");
    print_song(song2);
    
    set_song(song3, "Take Five", "Dave Brubeck", 324, JAZZ);
    printf("Song 3: ");
    print_song(song3);
    
    set_song(song4, "Moonlight Sonata", "Beethoven", 900, CLASSICAL);
    printf("Song 4: ");
    print_song(song4);
    
    set_song(song5, "HUMBLE.", "Kendrick Lamar", 177, HIPHOP);
    printf("Song 5: ");
    print_song(song5);
    
    // Free songs
    printf("\n--- Freeing song memory ---\n");
    free_song(song1);
    free_song(song2);
    free_song(song3);
    free_song(song4);
    free_song(song5);
    printf("All songs freed successfully.\n");
}

void test_database() {
    print_separator("TESTING DATABASE FUNCTIONS");
    
    // Test 1: Create database with small initial capacity
    printf("\n--- Test 1: Create database ---\n");
    Database * db = malloc(sizeof(Database));
    create_database(db, 2);
    printf("Database created with capacity: %d, count: %d\n", db->capacity, db->count);
    
    // Test 2: Add songs to database
    printf("\n--- Test 2: Add songs to database ---\n");
    Song * song1 = malloc(sizeof(Song));
    Song * song2 = malloc(sizeof(Song));
    Song * song3 = malloc(sizeof(Song)); 
    Song * song4 = malloc(sizeof(Song)); 
    Song * song5 = malloc(sizeof(Song));
    
    set_song(song1, "I Know The End", "Phoebe Bridgers", 321, ROCK);
    set_song(song2, "Smoke Signals", "Phoebe Bridgers", 298, POP);
    set_song(song3, "Funeral", "Phoebe Bridgers", 312, ROCK);
    set_song(song4, "Demi Moore", "Phoebe Bridgers", 285, POP);
    set_song(song5, "Scott Street", "Phoebe Bridgers", 267, ROCK);
    
    db_add_song(db, song1);
    printf("Added '%s' - Capacity: %d, Count: %d\n", song1->title, db->capacity, db->count);
    
    db_add_song(db, song2);
    printf("Added '%s' - Capacity: %d, Count: %d\n", song2->title, db->capacity, db->count);
    
    // Test 3: Database expansion (should double capacity)
    printf("\n--- Test 3: Database expansion ---\n");
    db_add_song(db, song3);
    printf("Added '%s' - Capacity: %d, Count: %d (should have doubled)\n", 
           song3->title, db->capacity, db->count);
    
    db_add_song(db, song4);
    printf("Added '%s' - Capacity: %d, Count: %d\n", song4->title, db->capacity, db->count);
    
    db_add_song(db, song5);
    printf("Added '%s' - Capacity: %d, Count: %d\n", song5->title, db->capacity, db->count);
    
    // Test 4: Display all songs in database
    printf("\n--- Test 4: Display all songs in database ---\n");
    for (int i = 0; i < db->count; i++) {
        printf("%d. ", i + 1);
        print_song(db->songs[i]);
    }
    
    // Test 5: Remove a song from database
    printf("\n--- Test 5: Remove song from database ---\n");
    printf("Removing 'Smoke Signals'...\n");
    db_remove_song(db, "Smoke Signals");
    printf("After removal - Capacity: %d, Count: %d\n", db->capacity, db->count);
    
    printf("\nRemaining songs:\n");
    for (int i = 0; i < db->count; i++) {
        printf("%d. ", i + 1);
        print_song(db->songs[i]);
    }
    
    // Test 6: Try to remove non-existent song
    printf("\n--- Test 6: Remove non-existent song ---\n");
    db_remove_song(db, "Non Existent Song");
    
    // Test 7: Free database
    printf("\n--- Test 7: Free database ---\n");
    free_db(db);
    printf("Database freed successfully");
}

void test_queue() {
    print_separator("TESTING QUEUE FUNCTIONS");
    
    // Setup: Create database and populate with songs
    printf("\n--- Setup: Creating database with songs ---\n");
    Database * db = malloc(sizeof(Database));
    create_database(db, 5);
    
    Song * song1 = malloc(sizeof(Song));
    Song * song2 = malloc(sizeof(Song));
    Song * song3 = malloc(sizeof(Song)); 
    Song * song4 = malloc(sizeof(Song)); 
    Song * song5 = malloc(sizeof(Song));

    set_song(song1, "I Know The End", "Phoebe Bridgers", 321, ROCK);
    set_song(song2, "Smoke Signals", "Phoebe Bridgers", 298, POP);
    set_song(song3, "Funeral", "Phoebe Bridgers", 312, ROCK);
    set_song(song4, "Demi Moore", "Phoebe Bridgers", 285, POP);
    set_song(song5, "Scott Street", "Phoebe Bridgers", 267, ROCK);
    
    db_add_song(db, song1);
    db_add_song(db, song2);
    db_add_song(db, song3);
    db_add_song(db, song4);
    db_add_song(db, song5);
    printf("Database created with %d songs.\n", db->count);
    
    // Test 1: Create queue
    printf("\n--- Test 1: Create queue ---\n");
    Queue * q = malloc(sizeof(Queue));
    create_queue(q);
    printf("Queue created - Capacity: %d, Size: %d\n", q->capacity, q->size);
    
    // Test 2: Add songs to queue
    printf("\n--- Test 2: Add songs to queue ---\n");
    queue_add_song(q, db, "I Know The End");
    printf("Added song. Queue size: %d\n", q->size);
    
    queue_add_song(q, db, "Smoke Signals");
    printf("Added song. Queue size: %d\n", q->size);
    
    queue_add_song(q, db, "Funeral");
    printf("Added song. Queue size: %d\n", q->size);
    
    queue_add_song(q, db, "Demi Moore");
    printf("Added song. Queue size: %d\n", q->size);
    
    queue_add_song(q, db, "Scott Street");
    printf("Added song. Queue size: %d\n", q->size);
    
    // Test 3: Print queue
    printf("\n--- Test 3: Print queue ---\n");
    print_queue(q);
    
    // Test 4: Try to add song not in database
    printf("\n--- Test 4: Add song not in database ---\n");
    queue_add_song(q, db, "Unknown Song");
    
    // Test 5: Play next songs
    printf("\n--- Test 5: Play next songs ---\n");
    printf("Current song: '%s'\n", q->cur_song);
    printf("Previous song: '%s'\n", q->prev_song);
    
    queue_next_song(q);
    printf("\nAfter queue_next_song():\n");
    printf("Current song: '%s'\n", q->cur_song);
    printf("Previous song: '%s'\n", q->prev_song);
    printf("Queue size: %d\n", q->size);
    
    queue_next_song(q);
    printf("\nAfter another queue_next_song():\n");
    printf("Current song: '%s'\n", q->cur_song);
    printf("Previous song: '%s'\n", q->prev_song);
    printf("Queue size: %d\n", q->size);
    
    // Test 6: Print queue after playing songs
    printf("\n--- Test 6: Print remaining queue ---\n");
    print_queue(q);
    
    // Test 7: Play all remaining songs
    printf("\n--- Test 7: Play all remaining songs ---\n");
    while (q->size > 0) {
        queue_next_song(q);
        printf("Now playing: '%s', Queue size: %d\n", q->cur_song, q->size);
    }
    
    // Test 8: Try to play from empty queue
    printf("\n--- Test 8: Try to play from empty queue ---\n");
    queue_next_song(q);
    
    // Test 9: Print empty queue
    printf("\n--- Test 9: Print empty queue ---\n");
    print_queue(q);
    
    // Test 10: Free queue
    printf("\n--- Test 10: Free queue ---\n");
    free_queue(q);
    printf("Queue freed successfully.\n");
    
    // Cleanup database
    printf("\n--- Cleanup: Free database ---\n");
    free_db(db);
    printf("Database freed successfully.\n");
}   

#endif