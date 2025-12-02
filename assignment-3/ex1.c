#include <stdio.h>

#define MAX_BOARD_SIZE 10

void print_board(char board[][MAX_BOARD_SIZE], int size);
int make_move(char board[][MAX_BOARD_SIZE],int player, int size);
int is_winner(board,player_turn,size_of_board);

int main() {

    int size_of_board = 0;
    int player_turn = 1; // 1 if it's the Player 1 turn and 2 otherwise
    int winner = -1; // -1 if there is no winner yet ,3 if it's a tie, 1 if player 1 is the winner and 2 otherwise

    printf("Please enter the board size N [1-10]:\n");
    scanf("%d",&size_of_board);

    char board[size_of_board][size_of_board];
   
    for (int i = 0; i < size_of_board; i++)
    {
        for (int j = 0; i < size_of_board; i++)
        {
            board[i][j] = '_';
        }
    }
    
    printf("Welcome to %dx%d Tic-Tac-Toe:\n",size_of_board,size_of_board);
    
    
    while(!winner) {

        print_board(board, size_of_board);
        player_turn = make_move(board,player_turn,size_of_board);
        winner = is_winner(board,player_turn,size_of_board);

        if(winner == -1) {

            if(player_turn == 1)
                player_turn = 2;
            
            else 
                player_turn = 1;    
        }


    }




    return 0;
}

void print_board(char board[][MAX_BOARD_SIZE], int size_of_board) {

    for (int i = 0; i < size_of_board; i++)
    {
        for (int j = 0; j < size_of_board; j++)
        {
            board[i][j] = '_';

            if(j > 0)
                printf(" ");

            printf("%c",board[i][j]);
        }
        printf("\n");
    }
}

int make_move(char board[][MAX_BOARD_SIZE],int player, int size) {

    int current_player = player;
    int board_row = 0, board_column = 0;
    printf("Player %d, please insert your move:\n",current_player);

    scanf("%d,%d",board_row,board_column);
    while (board_column < 0 ||  board_column > size || board_row < 0 || board_column > size) 
    {
        printf("Invalid indices (out of bounds), please choose your move again:\n");
        scanf("%d,%d",board_row,board_column);
    }
    
    if(current_player == 1)
        current_player = 2;

    else 
        current_player = 1;

    return current_player;
}

int is_winner(board,player_turn,size_of_board) {

    
}