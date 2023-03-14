// name: Grace Fry
// unikey: gfry4533
// SID: 520351277

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BOARD_SIZE  19
#define MAX_TURN 361 // 19 * 19
#define BUFFER_SIZE 256 // place S19
#define COORD_SIZE 4 // S19 + \0
#define TRUE 1
#define FALSE 0

char board[BOARD_SIZE + 2][BOARD_SIZE + 2];

char command[BUFFER_SIZE];
int game_over = FALSE;
int turn = 0;

char history[MAX_TURN][COORD_SIZE];
int hist_i = 0;

int mist_centre[2] = {10, 10}; // Starts in middle

void make_board() {
    for (int col = 1; col <= BOARD_SIZE; col++) {
        for (int row = 1; row <= BOARD_SIZE; row++) {
            board[col][row] = '.';
        }
    }
}

void print_history() {
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

    return (turn % 2 == 0) ? 'B' : 'W';;
}

int won(int num_c, int r, char player) {
    int count = 1;
    char moku = (player == 'W') ? 'o' : '#';

    // Check vertical increasing
    for (int row = (r + 1); 
        row < (r + 5) || row < BOARD_SIZE; row++) {
        // printf("Check vertical increasing\n");
        if (board[num_c][row] == moku) {
            count++;
        } else {
            break;
        }
    }

    // Check vertical decreasing
    for (int row = (r - 1); 
        row > (r - 5) && row >= 0; row--) {
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
    for (int col = (num_c + 1); 
        col < (num_c + 5) && col < BOARD_SIZE; col++) {
        if (board[col][r] == moku) {
            count++;
        } else {
            break;
        }
    }

    // Check horizontal decreasing
    for (int col = (num_c - 1); 
        col > (num_c - 5) && col >= 0; col--) {
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
    print_history();
    printf("Thank you for playing!\n");
    game_over = 1;
}

void resign() {
    turn++;
    char player = who(turn);
    victory(player);
}

void place(char c, int r, char player) {
    int num_c = command[6] - 'A' + 1;
    
    // Place according to player
    if (player == 'B') {
        board[num_c][r] = '#';
    } else {
        board[num_c][r] = 'o';
    }

    // Add to history
    char coord[4]; 
    sprintf(coord,"%c%d", c, r);
    strcpy(history[hist_i], coord);
    hist_i++;

    // Update mist centre
    int mist_col = 1 + (5 * (num_c * num_c) + 3 * num_c + 4) % 19;
    int mist_row = 1 + (4 * (r * r) + 2 * r - 4) % 19;
    mist_centre[0] = mist_col;
    mist_centre[1] = mist_row;

    // Check win
    if (!won(num_c, r, player)) {
        turn++;
    } else {
        victory(player);
    }
}

int check_validity(char* command) {
    char c = command[6];
    int num_c = c - 'A' + 1;
    int r = 0;

    if (command[6] == '\n' || command[6] == ' ') {
        return 1;
    }

    for (int i = 7; command[i] != '\n'; i++) {
        if (command[i] == ' ') {
            return 1;
        }
        if (command[i] <= '9' && command[i] >= '0') {
            r = r * 10 + command[i] - '0';
        } else {
            return 2;
        }
    }

    if (command[7] == '0') {
        return 2;
    }

    if ((num_c < 1 || num_c > BOARD_SIZE) || 
        (r < 1 || r > BOARD_SIZE)) {
        return 2;
    } 

    if (board[num_c][r] != '.') {
        return 3;
    }

    place(c, r, who(turn));

    return 0;
}

void view() {
    int mist_col = mist_centre[0];
    char c_mist_col = mist_col + 'A' - 1;
    int mist_row = mist_centre[1];
    printf("%c%d,", c_mist_col, mist_row);
    
    for (int row = mist_row + 3; row >= mist_row - 3; row--) {
        for (int col = mist_col - 3; col <= mist_col + 3; col++) {
            if (col < 1 || col > BOARD_SIZE ||
                row < 1 || row > BOARD_SIZE) {
                printf("x");
            } else {
                printf("%c", board[col][row]);
            }
        }
    }

    // for (int col = 1; col <= BOARD_SIZE; col++) {
    //     printf("%c ", col + 'A' - 1);
    // }
    // printf("\n");

    // for (int row = 1; row <= BOARD_SIZE; row++) {
    //     printf("%2d ", row);
    //     for (int col = 1; col <= BOARD_SIZE; col++) {
    //         printf("%c ", board[col][row]);
    //     }
    //     printf("\n");
    // }

    printf("\n");
}

int get_input() {
    int has_space = 0;
    while (fgets(command, BUFFER_SIZE, stdin) != NULL) {
        for (int i = 0; command[i] != '\0'; i++) {
            if (command[i] == ' ') {
                if (has_space) {
                    has_space = 0;
                    return 1;
                } else {
                    has_space = 1;
                }
            }

            if (command[i] == '\n') {
                return 0;
            }
        }
    }

    return 0;
}

int main(int argc, char* argv[]) {
    make_board();

    while (!game_over) {
        char player = who(turn);
        
        while (get_input()) {
            printf("Invalid!\n");
            get_input();
        }

        // tie
        if (turn == MAX_TURN) {
            printf("Wow, a tie!\n");
            print_history();
            printf("Thank you for playing!\n");
            exit(0);
        }

        // command switcher
        if (!strcmp(command, "term\n")) {
            term();
            continue;
        } else if (!strcmp(command, "who\n")) {
            printf("%c\n", player);
            continue;
        } else if (!strcmp(command, "history\n")) {
            print_history();
            continue;
        } else if (!strcmp(command, "view\n")) {
            view();
            continue;
        } else if (!strcmp(command, "resign\n")) {
            resign();
            continue;
        } else if (!strncmp(command, "place ", 6)) {
            switch (check_validity(command)) {
                case 1:
                    printf("Invalid!\n");
                    break;

                case 2:
                    printf("Invalid coordinate\n");
                    break;

                case 3:
                    printf("Occupied coordinate\n");
                    break;
                
                default:
                    break;
            }
        } else {
            printf("Invalid!\n");
        }
    }

    return 0;
}