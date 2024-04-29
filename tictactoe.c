#include <stdio.h>

// Function to print the Tic Tac Toe board
void print_board(char board[3][3]) {
    printf("  0 1 2\n");
    for (int i = 0; i < 3; i++) {
        printf("%d ", i);
        for (int j = 0; j < 3; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

// Function to check if the game is won
int check_win(char board[3][3]) {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            return 1;
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
            return 1;
        }
    }
    // Check diagonals
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')) {
        return 1;
    }
    return 0;
}

// Function to check if the game is a draw
int check_draw(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return 0; // Game not draw
            }
        }
    }
    return 1; // Game is draw
}

int main() {
    int row, col;
    // Initialize empty board
    // multi dimentional array 3 rows and 3 column
    char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}}; 
    // Player X starts
    char player = 'X'; 

    printf("Welcome to Tic Tac Toe!\n");
    printf("Player X starts.\n");

    // endless looping until one of the player win the game
    while (1) {
        printf("\n");
        print_board(board);

        // Get player's move
        printf("Player %c's turn. Enter row and column (0-2): ", player);
        scanf("%d %d", &row, &col);

        // Check if the move is valid
        if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
            printf("Invalid move! Try again.\n");
            continue;
        }

        // Place player's mark on the board
        board[row][col] = player;

        // Check for win
        if (check_win(board)) {
            printf("\nPlayer %c wins!\n", player);
            break;
        }

        // Check for draw
        if (check_draw(board)) {
            printf("\nThe game is a draw!\n");
            break;
        }

        // Switch player
        player = (player == 'X') ? 'O' : 'X';
    }

    printf("\nFinal board:\n");
    print_board(board);

    return 0;
}
