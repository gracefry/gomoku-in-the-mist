// name: Grace Fry
// unikey: gfry4533
// SID: 520351277

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char board[20][20];
char command[256];
int game_over = 0;
int turn = 0;

void makeBoard() {
    for (int i = 0; i <= 20; i++) {
        for (int j = 0; j <= 20; j++) {
            board[i][j] = '.';
        }
    }
}

int place(char c, int r, char player) {
    int num_c = c - 'A' + 1;

    // Check column and row validity
    if ((num_c < 1 || num_c > 19) || (r < 1 || r > 19)) {
        printf("Invalid coordinate\n");
        // printf("inval %d, %d", num_c, r);
        return 1;
    } 

    // Check occupancy
    if (board[num_c][r] != '.') {
        printf("Occupied coordinate\n");
        return 1;
    }
    
    // Place according to player
    if (player == 'B') {
        board[num_c][r] = '#';
        // printf("black %d, %d", num_c, r);
    } else {
        board[num_c][r] = 'o';
    }

    turn++;
    return 0;
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

int main(int argc, char* argv[]) {
    makeBoard();

    while (game_over == 0) {
        fgets(command, 256, stdin);
        char player = who(turn);

        // command switcher
        if (!strncmp(command, "term", 4)) {
            term();
        } else if (!strncmp(command, "who", 3)) {
            printf("%c\n", player);
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
