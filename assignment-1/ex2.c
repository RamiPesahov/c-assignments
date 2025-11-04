#include <stdio.h>

int main() {

    int grade, failed_attemps = 0;

    printf("Please enter the exam score (0-100):\n");
    scanf("%d",&grade);

    while(grade > 100 || grade < 0) {
        
        failed_attemps++;

        if(failed_attemps == 3) {

            printf("The user has inserted 3 consecutive times an invalid score.\n");
            printf("Exiting the program!\n");
            return 0;
        }

        printf("Invalid exam score: %d\n",grade);
        printf("Please enter a new exam score in the range 0-100:\n");
        scanf("%d",&grade);
    }

    switch(grade / 10) {

        case 9:
        case 10:
            printf("Grade: A\n");
            printf("Excellent work!\n");
            break;

        case 8:
            printf("Grade: B\n");
            printf("Well done.\n");
            break;
            
        case 7:
            printf("Grade: C\n");    
            printf("Not bad! You can do better..\n");
            break;

        case 6:
            printf("Grade: D\n");
            printf("You passed, but there is room for improvement.\n");
            break;
            
        case 5:
            printf("Grade: E\n");
            printf("Barely passed - you should work harder next time.\n");
            break;

        case 1:
        case 2:
        case 3:
        case 4:
        case 0:
            printf("Grade: F\n");
            printf("You Failed - you need to review the material.\n");
            break;
    }

    return 0;
}