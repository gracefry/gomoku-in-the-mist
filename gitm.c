// name: Grace Fry
// unikey: gfry4533
// SID: 520351277

#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    char command[256];
    int game_over = 0;

    while (game_over == 0) {
        fgets(command, 256, stdin);

        // term command
        if (!strcmp(command, "term\n")) {
            return 1;
        }

        printf("%s", command);
        game_over = 1;
    }

    return 0;
}
