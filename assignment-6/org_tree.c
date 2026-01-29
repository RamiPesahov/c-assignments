#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "org_tree.h"


static Node* create_node(char *f, char *s, char *fp, char *pos) {

    Node *new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return NULL;
    
    strncpy(new_node->first, f, MAX_FIELD - 1);
    new_node -> first[MAX_FIELD - 1] = '\0';

    strncpy(new_node->second, s, MAX_FIELD - 1);
    new_node -> second[MAX_FIELD - 1] = '\0';

    strncpy(new_node->fingerprint, fp, MAX_FIELD - 1);
    new_node -> fingerprint[MAX_FIELD - 1] = '\0';
    
    strncpy(new_node->position, pos, MAX_POS - 1);
    new_node -> position[MAX_POS - 1] = '\0'; 
    
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->supports_head = NULL;
    new_node->next = NULL;
    
    return new_node;
}

static void add_support(Node *hand, Node *support) {

    if (hand->supports_head == NULL) {
        hand->supports_head = support;
    }
    else {
        Node *temp = hand->supports_head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = support;
    }
}

Org build_org_from_clean_file(const char *path) {

    FILE *file = fopen(path, "r");
    Org org = {NULL, NULL, NULL};
    if (!file) return org;

    char line[MAX_FIELD * 2];
    char f[MAX_FIELD], s[MAX_FIELD], fp[MAX_FIELD], pos[MAX_POS];
    
    
    while (fgets(line, sizeof(line), file)) {
        if (strlen(line) <= 1) continue; // Empty line
        
        sscanf(line, "First Name: %[^\n]", f);
        fgets(line, sizeof(line), file);
        sscanf(line, "Second Name: %[^\n]", s);
        fgets(line, sizeof(line), file);
        sscanf(line, "Fingerprint: %[^\n]", fp);
        fgets(line, sizeof(line), file);
        sscanf(line, "Position: %[^\n]", pos);

        Node *new_node = create_node(f, s, fp, pos);

        if (strcmp(pos, "Boss") == 0) {
            org.boss = new_node;

        } else if (strcmp(pos, "Right Hand") == 0) {
            
            org.right_hand = new_node; 
            if (org.boss) 
                org.boss->right = new_node;

        } else if (strcmp(pos, "Left Hand") == 0) {
            
            org.left_hand = new_node;
            if (org.boss) 
                org.boss->left = new_node;

        } else if (strcmp(pos, "Support Right") == 0) {
          
            if (org.right_hand)
                add_support(org.right_hand, new_node);

        } else if (strcmp(pos, "Support Left") == 0) {
            
            if (org.left_hand) 
                add_support(org.left_hand, new_node);

        }
    }
    fclose(file);
    return org;
}

void print_tree_order(const Org *org) {
  
    // TODO: implement
    if (!org || !org->boss) return;

    // Boss
    printf("Boss: %s %s, Fingerprint: %s\n", org->boss->first, org->boss->second, org->boss->fingerprint);

    // Right hand and support
    if (org->right_hand) {
        printf("Right Hand: %s %s, Fingerprint: %s\n", org->right_hand->first, org->right_hand->second, org->right_hand->fingerprint);
        Node *curr = org->right_hand->supports_head;
        while (curr) {
            printf("  Support Right: %s %s, Fingerprint: %s\n", curr->first, curr->second, curr->fingerprint);
            curr = curr->next;
        }
    }

    // Left hand and support
    if (org->left_hand) {
        printf("Left Hand: %s %s, Fingerprint: %s\n", org->left_hand->first, org->left_hand->second, org->left_hand->fingerprint);
        Node *curr = org->left_hand->supports_head;
        while (curr) {
            printf("  Support Left: %s %s, Fingerprint: %s\n", curr->first, curr->second, curr->fingerprint);
            curr = curr->next;
        }
    }
}

static void free_list(Node *head) {
    while (head) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

void free_org(Org *org) {
    
    // TODO: implement
    if (!org) return;
    
    if (org->right_hand) {
        free_list(org->right_hand->supports_head);
        free(org->right_hand);
    }
    if (org->left_hand) {
        free_list(org->left_hand->supports_head);
        free(org->left_hand);
    }
    
    if (org->boss) free(org->boss);
    
    org->boss = org->left_hand = org->right_hand = NULL;
}
