// name: Grace Fry
// unikey: gfry4533
// SID: 520351277

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int BOARD_SIZE = 20;
const int MAX_HISTORY = 50;
char board[20][20];
char command[256];
int game_over = 0;
int turn = 0;
char history[256][4];
int hist_i = 0;

void makeBoard() {
    for (int col = 0; col < BOARD_SIZE; col++) {
        for (int row = 0; row < BOARD_SIZE; row++) {
            board[col][row] = '.';
        }
    }
}

void printHistory() {
    for (int i = 0; i < hist_i; i++) {
        printf("%s", history[i]);
    }
    printf("\n");
}

void term() {
    /*
    * Function:  term
    * --------------------
    * Forces the controller to terminate with exit code 1. 
    * This command can be executed at any time. 
    * This command will suppress history moves messages and the exit message.
    */

    exit(1);
}

char who(int turn) {
    /*
    * Function:  who 
    * --------------------
    * Shows who is the current player. 
    * This command can be executed at any time.
    *
    *   turn: integer value of the current turn 
    *       turn increments by 1 for every valid place command
    *
    *   returns: 
    *       char 'B' for black, or
    *       char 'W' for white
    */
    char player;

    if (turn % 2 == 0) {
        player = 'B';
    } else {
        player = 'W';
    }

    return player;
}

int isWon(int num_c, int r, char player) {
    int count = 1;
    char moku = (player == 'W') ? 'o' : '#';

    // Check vertical increasing
    for (int row = (r + 1); row < (r + 5) || row < BOARD_SIZE; row++) {
        // printf("Check vertical increasing\n");
        if (board[num_c][row] == moku) {
            count++;
        } else {
            break;
        }
    }

    // Check vertical decreasing
    for (int row = (r - 1); row < (r - 5) || row < BOARD_SIZE; row--) {
        // printf("Check vertical decreasing\n");
        if (board[num_c][row] == moku) {
            count++;
        } else {
            break;
        }
    }

    if (count == 5) {
        return 1;
    } else {
        count = 1;
    }
    

    // Check horizontal increasing
    for (int col = (num_c + 1); col < (num_c + 5) || col < BOARD_SIZE; col++) {
        if (board[col][r] == moku) {
            count++;
        } else {
            break;
        }
    }

    // Check horizontal decreasing
    for (int col = (num_c - 1); col < (num_c - 5) || col >= 0; col--) {
        if (board[col][r] == moku) {
            count++;
        } else {
            break;
        }
    }

    if (count == 5) {
        return 1;
    } else {
        count = 1;
    }

    // Check diagonal SE
    for (int col = (num_c + 1), row = (r + 1); 
        col < (num_c) + 5 && col < BOARD_SIZE && row < BOARD_SIZE && row < (r + 5); 
        col++, row++) {
        if (board[col][row] == moku) {
            count++;
        } else {
            break;
        }
    }

    // Check diagonal NW
    for (int col = num_c - 1, row = (r - 1); 
        col > num_c - 5 && col >= 0 && row >= 0 && row > (r - 5); 
        col--, row--) {
        if (board[col][row] == moku) {
            count++;
        } else {
            break;
        }
    }

    if (count == 5) {
        return 1;
    } else {
        count = 1;
    }

    // Check diagonal SW
    for (int col = (num_c - 1), row = (r + 1); 
        col > (num_c - 5) && col >= 0 && row < BOARD_SIZE && row < (r + 5); 
        col--, row++) {
        if (board[col][row] == moku) {
            count++;
        } else {
            break;
        }
    }

    // Check diagonal NE
    for (int col = (num_c + 1), row = (r - 1); 
        col < (num_c + 5) && col < BOARD_SIZE && row > (r - 5) && row >= 0; 
        col++, row--) {
        if (board[col][row] == moku) {
            count++;
        } else {
            break;
        }
    }

    if (count == 5) {
        return 1;
    } else {
        return 0;
    }
}

void victory(char player) {
    char* name = (player == 'W') ? "White" : "Black";

    printf("%s wins!\n", name);
    printHistory();
    printf("Thank you for playing!\n");
    game_over = 1;
}

void resign() {
    turn++;
    char player = who(turn);
    victory(player);
}

void place(char c, int r, char player) {
    int num_c = c - 'A';

    // Check column and row validity
    if ((num_c < 0 || num_c >= BOARD_SIZE) || 
        (r < 0 || r >= BOARD_SIZE)) {
        printf("Invalid coordinate\n");
        // printf("inval %d, %d", num_c, r);
        return;
    } 

    // Check occupancy
    if (board[num_c][r] != '.') {
        printf("Occupied coordinate\n");
        return;
    }
    
    // Place according to player
    if (player == 'B') {
        board[num_c][r] = '#';
        // printf("black %d, %d", num_c, r);
    } else {
        board[num_c][r] = 'o';
    }

    // Add to history
    char coord[4]; 
    sprintf(coord,"%c%d", c, r);
    strcpy(history[hist_i], coord);
    hist_i++;

    // Check win
    if (!isWon(num_c, r, player)) {
        // printf("not win\n");
        turn++;
    } else {
        // printf("win\n");
        victory(player);
    }
}

int main(int argc, char* argv[]) {
    makeBoard();

    while (!game_over) {
        fgets(command, 256, stdin);
        char player = who(turn);

        // command switcher
        if (!strncmp(command, "term", 4)) {
            term();
        } else if (!strncmp(command, "who", 3)) {
            printf("%c\n", player);
        } else if (!strncmp(command, "history", 7)) {
            printHistory();
        } else if (!strncmp(command, "resign", 6)) {
            resign();
        } else if (!strncmp(command, "place", 5)) {
            char c = command[6];
            int r = 0;

            for (int i = 7; command[i] != '\0'; i++) {
                if (command[i] <= '9' && command[i] >= '0') {
                r = r * 10 + command[i] - '0';
                }
            }

            place(c, r, player);

        } else {
            printf("Invalid!\n");
        }
        // game_over = 1;
    }

    return 0;
}
