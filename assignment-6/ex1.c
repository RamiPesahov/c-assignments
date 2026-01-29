#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_FIELD 128
#define MAX_ENTRIES 1000

typedef struct {
    char first[MAX_FIELD];
    char second[MAX_FIELD];
    char fp[MAX_FIELD];
    char pos[MAX_FIELD];
} Entry;

//TODO create functions that you can use to clean up the file

int is_corruption(char c) {
    return (c == '#' || c == '?' || c == '!' || c == '&' || c == '$');
}

// Function to clean the raw buffer from corruptions and newlines
void clean_buffer(char *dest, const char *src) {
    int j = 0;
    for (int i = 0; src[i] != '\0'; i++) {
        if (!is_corruption(src[i])) {
            dest[j++] = (src[i] == '\n' || src[i] == '\r') ? ' ' : src[i];
        }
    }
    dest[j] = '\0';
}

// Robust field extraction using tags
void extract_field(const char *buffer, const char *tag, const char *next_tag, char *dest) {
    char *start = strstr(buffer, tag);
    if (!start) return;
    start += strlen(tag);
    while (isspace(*start)) start++;

    char *end = next_tag ? strstr(start, next_tag) : NULL;
    int len = end ? (int)(end - start) : (int)strlen(start);
    
    if (len >= MAX_FIELD) len = MAX_FIELD - 1;
    strncpy(dest, start, len);
    dest[len] = '\0';
    
    char *back = dest + strlen(dest) - 1;
    while (back >= dest && isspace(*back)) {
        *back = '\0';
        back--;
    }
}
int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s <input_corrupted.txt> <output_clean.txt>\n", argv[0]);
        return 0;
    }
    
    // TODO: implement
    
    FILE *fin = fopen(argv[1], "r");
    if (!fin) return 0;

    fseek(fin, 0, SEEK_END);
    long size = ftell(fin);

    fseek(fin, 0, SEEK_SET);
    char *raw_content = malloc(size + 1);

    if (!raw_content) { fclose(fin); return 0; }

    fread(raw_content, 1, size, fin);
    raw_content[size] = '\0';
    fclose(fin);

    char *clean_content = malloc(size + 1);
    if (!clean_content) { free(raw_content); return 0; }

    clean_buffer(clean_content, raw_content);
    free(raw_content);

    Entry entries[MAX_ENTRIES];
    int count = 0;
    char *ptr = clean_content;

    while ((ptr = strstr(ptr, "First Name:")) && count < MAX_ENTRIES) {
        Entry e;
        extract_field(ptr, "First Name:", "Second Name:", e.first);
        extract_field(ptr, "Second Name:", "Fingerprint:", e.second);
        extract_field(ptr, "Fingerprint:", "Position:", e.fp);
        
        char *next_entry = strstr(ptr + 1, "First Name:");
        extract_field(ptr, "Position:", next_entry ? "First Name:" : NULL, e.pos);

        int duplicate = 0;
        for (int i = 0; i < count; i++) {
            if (strcmp(entries[i].fp, e.fp) == 0) {
                duplicate = 1;
                break;
            }
        }

        if (!duplicate) {
            entries[count++] = e;
        }
        ptr = next_entry ? next_entry : (ptr + strlen(ptr));
    }

    FILE *fout = fopen(argv[2], "w");
    if (fout) {
        const char *hierarchy[] = {"Boss", "Right Hand", "Left Hand", "Support Right", "Support Left"};
        for (int h = 0; h < 5; h++) {
            for (int i = 0; i < count; i++) {
                if (strcmp(entries[i].pos, hierarchy[h]) == 0) {
                    fprintf(fout, "First Name: %s\nSecond Name: %s\nFingerprint: %s\nPosition: %s\n\n",
                            entries[i].first, entries[i].second, entries[i].fp, entries[i].pos);
                }
            }
        }
        fclose(fout);
    }

    free(clean_content);
    return 0;
}
