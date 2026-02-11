#include <stdio.h>
typedef struct{
    int whole; // The integer part of the number
    int num; // numerator
    int den; // denominator
} mixnum;

typedef struct mix_t
{
    mixnum num; // The mixed number
    struct mix_t *next; // a pointer to the next
} mixnum_sh;

unsigned int gcd(unsigned int a, unsigned int b){
    while(b != 0){
        unsigned int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

void makegood(mixnum *x){ // 2nd try: problem with negatives handling
    if(x->den < 0){
        x->den = -x->den;
        x->num = -x->num;
    }
    while(x->num < 0) {
        x->num += x->den;
        x->whole -= 1;
    }

    int wholes = x->num / x->den;
    if(wholes){
        x->whole += wholes;
        x->num -= wholes * x->den;
    }

    int gcd_value = gcd(x->den, x->num);
    x->den /= gcd_value;
    x->num /= gcd_value;
}


mixnum addmix(mixnum a, mixnum b){ // 1st try!
    mixnum sum = {0, 0, 0};
    sum.whole = a.whole + b.whole;
    int newden = a.den * b.den;
    a.num *= b.den;
    b.num *= a.den;
    sum.num = a.num + b.num;
    sum.den = newden;
    makegood(&sum);
    return sum;
}

mixnum sum(mixnum_sh *head) {
    mixnum sum = {0, 0, 0};
    mixnum_sh * current = head; 
    while(current != NULL){
        sum = addmix(sum, current->num);
        current = head->next;
    }
    return sum;
}

mixnum_sh *getmixnum(int w, int num, int den) {

}

int main(){
    mixnum number_a = {
        .whole = 10,
        .num = 50,
        .den = 9
    };
    mixnum number_b = {
        .whole = 5,
        .num = 5,
        .den = 3
    };
    mixnum good_number = addmix(number_a, number_b);
    makegood(&number_a);
    makegood(&number_b);
    printf("a: %d + %d / %d | ", number_a.whole, number_a.num, number_a.den);
    printf("b: %d + %d / %d | ", number_b.whole, number_b.num, number_b.den);
    printf("\"Good\": %d + %d / %d\n", good_number.whole, good_number.num, good_number.den);
    return 0;
}