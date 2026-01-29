#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "org_tree.h"
#define FP_LEN 9


static void print_success(int mask, char *op, char* fingerprint, char* First_Name, char* Second_Name)
{
    printf("Successful Decrypt! The Mask used was mask_%d of type (%s) and The fingerprint was %.*s belonging to %s %s\n",
                       mask, op, FP_LEN, fingerprint, First_Name, Second_Name);
}

static void print_unsuccess()
{
    printf("Unsuccesful decrypt, Looks like he got away\n");
}

static int is_printable_custom(unsigned char c) {

    if (c == '\0') return 1;
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) return 1;
    if (c >= '0' && c <= '9') return 1;
    if (c == ' ' || c == '\n' || c == '\r' || c == '\t') return 1;

    return 0;
}

// Decoding function that attempts to construct a string from the bits
static int try_decrypt(const char *cipher, const char *mask, Node *n, int s, char *op) {
    int cipher_len = (int)strlen(cipher);
    int mask_len = (int)strlen(mask);
    if (mask_len == 0) return 0;

    char decrypted_msg[2048] = {0};
    int msg_ptr = 0;

    for (int i = 0; i + 8 <= cipher_len; i += 8) {
        unsigned char current_char = 0;
        for (int j = 0; j < 8; j++) {
            int cipher_bit = cipher[i + j] - '0';
            int mask_bit = mask[((i + j) % mask_len)] - '0';
            int res_bit;

            if (strcmp(op, "XOR") == 0) res_bit = cipher_bit ^ mask_bit;
            else res_bit = cipher_bit & mask_bit;

            current_char |= (res_bit << (7 - j));
        }

        if (!is_printable_custom(current_char)) return 0;
        decrypted_msg[msg_ptr++] = (char)current_char;
    }
    
    decrypted_msg[msg_ptr] = '\0';
    print_success(s, op, n->fingerprint, n->first, n->second);
    printf("Decrypted message: %s\n", decrypted_msg);
    return 1;
}

// Scanning all members
static int scan_org(Node *n, const char *cipher, int s) {

    if (!n) return 0;
    
    const char *mask = n -> fingerprint + s;
    if (try_decrypt(cipher, mask, n, s, "XOR")) return 1;
    if (try_decrypt(cipher, mask, n, s, "AND")) return 1;

    if (scan_org(n->left, cipher, s)) return 1;
    if (scan_org(n->right, cipher, s)) return 1;

    Node *curr_support = n->supports_head;
    while (curr_support) {
        if (scan_org(curr_support, cipher, s)) return 1;
        curr_support = curr_support->next;
    }
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 4) {
        printf("Usage: %s <clean_file.txt> <cipher_bits.txt> <mask_start_s>\n", argv[0]);
        return 0;
    }
    
    // TODO: build the organization
    Org org = build_org_from_clean_file(argv[1]);
    if (!org.boss) {
        free_org(&org);
        return 0;
    }

    // TODO: attempt to decrypt the file
    FILE *f_cipher = fopen(argv[2], "r");
    if (!f_cipher) {
        free_org(&org);
        return 0;
    }
    char cipher_buffer[8192];
    if (!fgets(cipher_buffer, sizeof(cipher_buffer), f_cipher)) {
        fclose(f_cipher);
        free_org(&org);
        return 0;
    }
    fclose(f_cipher);

    // Cleaning unwanted chars from the end 
    cipher_buffer[strcspn(cipher_buffer, "\r\n")] = 0;

    int s = atoi(argv[3]);
    if (!scan_org(org.boss, cipher_buffer, s)) {
        print_unsuccess();
    }

    // TODO: free any memory you may have allocated
    free_org(&org);

    return 0;
}
