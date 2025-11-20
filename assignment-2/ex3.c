#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TARGET (9 * 9 * 9)
#define MIN_TARGET (-9*9)
#define MAX_INPUT 999
#define MIN_INPUT 000
#define MAX_LINE 1000

int apply_op(int a, int b, char op)
{
    if (op == '+')
        return a + b;
    if (op == '-')
        return a - b;
    return a * b; // op == '*'
}

int evaluate(int d1, int d2, int d3, char op1, char op2)
{
    // Check for multiplications
    if (op1 == '*'){
        int left = d1 * d2;
        return apply_op(left, d3, op2);
    }
    else if (op2 == '*'){
        int right = d2 * d3;
        return apply_op(d1, right, op1);
    }
    else{
        int tmp = apply_op(d1, d2, op1);
        return apply_op(tmp, d3, op2);
    }
}

int main(void){
    char num_text[MAX_LINE];
    int num, target;
    printf("Enter a 3-digit integer:\n");
    
    if (scanf("%999s", num_text) != 1){
        printf("Invalid input. Must be a 3-digit number.\n");
        return 0;
    }
    num = atoi(num_text);

    if (num < MIN_INPUT || num > MAX_INPUT){
        printf("Invalid input. Must be a 3-digit number.\n");
        return 0;
    }

    printf("Enter target value:\n");
    if (scanf("%d", &target) != 1){
        printf("Invalid target.\n");
        return 0;
    }
    if (target < MIN_TARGET || target > MAX_TARGET){
        printf("Invalid target. target %d is outside of range.\n", target);
        return 0;
    }

    // extract digits
    int d0 = num / 100;
    int d1 = (num / 10) % 10;
    int d2 = num % 10;

    // all 6 permutations
    int perms[6][3] = {
        {d0, d1, d2},
        {d0, d2, d1},
        {d1, d0, d2},
        {d1, d2, d0},
        {d2, d0, d1},
        {d2, d1, d0}};

    char ops[3] = {'+', '-', '*'};
    int count = 0;

    for (int p = 0; p < 6; p++){
        int a = perms[p][0];
        int b = perms[p][1];
        int c = perms[p][2];

        // all operator combinations
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (evaluate(a, b, c, ops[i], ops[j]) == target){
                    count++;
                }
            }
        }
    }

    printf("Found %d ways to reach the target using +, - and * operations.\n", count);
    return 0;
}
