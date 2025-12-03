#include <stdio.h>

#define MAX_BOARD_SIZE 10 
#define TIE 3
#define PLAYER1 1
#define PLAYER2 2
#define GAME_CONTINUES -1

void print_board(char board[][MAX_BOARD_SIZE + 1], int size);
void make_move(char board[][MAX_BOARD_SIZE + 1],int player, int size);
int is_winner(char board[][MAX_BOARD_SIZE + 1],int player_turn,int size_of_board);
int check_horizontal_line(char board[][MAX_BOARD_SIZE + 1],int player_turn,int size_of_board);
int check_vertical_line(char board[][MAX_BOARD_SIZE + 1],int player_turn,int size_of_board);
int check_diagonal_line(char board[][MAX_BOARD_SIZE + 1],int player_turn,int size_of_board);
int check_if_tie(char board[][MAX_BOARD_SIZE + 1], int size_of_board);
int has_both(char sequence[],int size_of_board);
void scan_indices(char board[][MAX_BOARD_SIZE + 1], int* board_row,  int* board_column, int size_of_board);

int main() {

    int size_of_board = 0;
    int player_turn = PLAYER1; // 1 if it's the Player 1 turn and 2 otherwise, and we know the game starts from player 1 turn
    int winner = GAME_CONTINUES; // -1 if there is no winner yet ,3 if it's a tie, 1 if player 1 is the winner and 2 otherwise

    printf("Please enter the board size N [1-10]:\n");
    scanf("%d",&size_of_board);

    char board[MAX_BOARD_SIZE + 1][MAX_BOARD_SIZE + 1]; // +1 because of the end-of-string character (\0)
   
    for (int i = 0; i < size_of_board; i++)
    {
        for (int j = 0; j < size_of_board; j++)
        {
            board[i][j] = '_';
        }
    }
    
    printf("Welcome to %dx%d Tic-Tac-Toe:\n",size_of_board,size_of_board);
    print_board(board,size_of_board);
    
    while(winner == GAME_CONTINUES) { // if there is no winner yet

        make_move(board, player_turn, size_of_board);
        print_board(board, size_of_board);
        winner = is_winner(board, player_turn, size_of_board);

        switch (winner)
        {
            case PLAYER1:
                printf("Player 1 is the winner!\n");
                break;
        
            case PLAYER2:
                printf("Player 2 is the winner!\n");
                break;

            case TIE:
                printf("There is a Tie!\n");
                break;
            
            default:

                if(player_turn == PLAYER1) 
                    player_turn = PLAYER2;
                else 
                    player_turn = PLAYER1; 

                
                break;
        }    
    }

    return 0;
}

void print_board(char board[][MAX_BOARD_SIZE + 1], int size_of_board) {

    for (int i = 0; i < size_of_board; i++)
    {
        for (int j = 0; j < size_of_board; j++)
        {
            if(j > 0)
                printf(" ");

            printf("%c",board[i][j]);
        }
        printf("\n");
    }
}

void make_move(char board[][MAX_BOARD_SIZE + 1],int player, int size) {

    int board_row = 0, board_column = 0;
    printf("Player %d, please insert your move:\n",player);
    scan_indices(board,&board_row, &board_column,size);

    if(player == PLAYER1) {
        board[board_row - 1][board_column - 1] = 'X';
    }

    else {
        board[board_row - 1][board_column - 1] = 'O';
    }
}

int is_winner(char board[][MAX_BOARD_SIZE + 1] ,int current_player,int size_of_board) {

    int who_is_the_winner = -1; // we initialize the value to 'game still continues

    who_is_the_winner = check_horizontal_line(board,current_player,size_of_board);
    if(who_is_the_winner != GAME_CONTINUES)
        return who_is_the_winner;

    who_is_the_winner = check_vertical_line(board,current_player,size_of_board);
    if(who_is_the_winner != GAME_CONTINUES)
        return who_is_the_winner;

    who_is_the_winner = check_diagonal_line(board,current_player,size_of_board);
    if(who_is_the_winner != GAME_CONTINUES)
        return who_is_the_winner;

    if(check_if_tie(board,size_of_board) == 1)
        return TIE;

    return GAME_CONTINUES; // no one wins and there is no tie, so the game still continutes
}

int check_horizontal_line(char board[][MAX_BOARD_SIZE + 1] ,int current_player,int size_of_board) {

    char current_player_char = '_';

    if (current_player == PLAYER1)
        current_player_char = 'X';

    else
        current_player_char = 'O';     
    
    for (int i = 0; i < size_of_board; i++)
    {
        int row_same_character = 1; // initialized to true, until we reach a place which is different 
        for (int j = 0; j < size_of_board; j++)
        {
            if(board[i][j] != current_player_char) {

                row_same_character = 0;
                break;
            }
        }
        if(row_same_character == 1)
            return current_player;
    }
    return GAME_CONTINUES; // no one won in a row.
}

int check_vertical_line(char board[][MAX_BOARD_SIZE + 1] ,int current_player,int size_of_board) {
    
    char current_player_char = '_';

    if (current_player == PLAYER1)
        current_player_char = 'X';

    else
        current_player_char = 'O';  

    for (int i = 0; i < size_of_board; i++)
    {
        int column_same_character = 1; // initialized to true, until we reach a place which is different 
        for (int j = 0; j < size_of_board; j++)
        {
            if(board[j][i] != current_player_char) {

                column_same_character = 0;
                break;
            }
        }
        if(column_same_character == 1)
            return current_player;
    }
    return GAME_CONTINUES; // no one won in a column.    
}

int check_diagonal_line(char board[][MAX_BOARD_SIZE + 1],int player_turn,int size_of_board) {

    char current_player_char = '_';

    if (player_turn == PLAYER1)
        current_player_char = 'X';

    else
        current_player_char = 'O'; 
    
    int diagonal_same_character = 1; // initialized to true, until we reach a place which is different     
    int reverse_diagonal_same_character = 1; 

    for (int i = 0; i < size_of_board; i++)
    {
        if (board[i][i] != current_player_char) {

            diagonal_same_character = 0;
            break;
        }
    }

    for (int i = 0; i < size_of_board; i++)
    {
        if(board[i][size_of_board - i - 1] != current_player_char) {

            reverse_diagonal_same_character = 0;
            break;
        }
    }

    if(diagonal_same_character == 1 || reverse_diagonal_same_character == 1)
        return player_turn;

    return GAME_CONTINUES;    
}

int check_if_tie(char board[][MAX_BOARD_SIZE + 1], int size_of_board) { // 1 if there is a tie and 0 otherwise

    int rows = 0, columns = 0, diagonals = 0;
    
    for (int i = 0; i < size_of_board; i++) // calculates how many rows has both X and O
    {
        char temp[MAX_BOARD_SIZE];
        for(int j = 0; j < size_of_board; j++) {
            temp[j] = board[i][j];
        }
        rows += has_both(temp, size_of_board);
    }

    for (int i = 0; i < size_of_board; i++) // calculates how many columns has both X and O
    {
        char temp[MAX_BOARD_SIZE];
        for(int j = 0; j < size_of_board; j++) {
            temp[j] = board[j][i];
        }
        columns += has_both(temp, size_of_board);
    }

    char temp[MAX_BOARD_SIZE];
    for (int i = 0; i < size_of_board; i++) // calculates if the main diagonal has both X and O
    {
        temp[i] = board[i][i];
    }
    diagonals += has_both(temp, size_of_board);

    for (int i = 0; i < size_of_board; i++) // calculates if the reverse diagonal has both X and O
    {
        temp[i] = board[i][size_of_board - i - 1];
    }
    diagonals += has_both(temp, size_of_board);

    if(rows == size_of_board && columns == size_of_board && diagonals == 2)
        return 1; 
    return 0;
}

int has_both(char sequence[],int size_of_board) {

    int has_x = 0;
    int has_o = 0;

    for(int i=0;i<size_of_board;i++)  {

        if (sequence[i] == 'X') has_x++;
        else if(sequence[i] == 'O') has_o++;
    }

    if(has_x > 0 && has_o > 0)
        return 1;
    return 0;    
}
void scan_indices(char board[][MAX_BOARD_SIZE + 1], int* board_row,  int* board_column, int size) {

    int valid = 0; // 1 if the indices are good to go
    
    while(valid == 0) {
        scanf("%d ,%d", board_row, board_column);
        
        if (*board_column < 1 ||  *board_column > size || *board_row < 1 || *board_row > size) 
            printf("Invalid indices (out of bounds), please choose your move again:\n");
        
        else if(board[*board_row - 1][*board_column - 1] != '_') 
            printf("Invalid indices (occupied cell), please choose your move again:\n");

        else 
            valid = 1;
    }
}