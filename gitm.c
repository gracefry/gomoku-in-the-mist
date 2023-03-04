// name: Grace Fry
// unikey: gfry4533
// SID: 520351277

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void term() {
    exit(1);
}

char who(int turn) {
    char player;

    if (turn % 2 == 0) {
        player = 'B';
    } else {
        player = 'W';
    }

    printf("%c\n", player);
    return player;
}

int main(int argc, char* argv[]) {
    char command[256];
    int game_over = 0;
    int turn = 0;

    while (game_over == 0) {
        fgets(command, 256, stdin);

        // command switcher
        if (!strcmp(command, "term\n")) {
            term();
        } else if (!strcmp(command, "who\n")) {
            who(turn);
        } else {
            printf("Invalid!\n");
        }

        // printf("%s", command);
        // game_over = 1;
    }

    return 0;
}
