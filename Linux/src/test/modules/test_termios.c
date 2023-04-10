#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int test_termios(int argc, char* argv[])
{
    (void)argc;
    (void)argv;
    
    int c;
    static struct termios old_termios, new_termios;

    tcgetattr(STDIN_FILENO, &old_termios);
    new_termios = old_termios;
    cfmakeraw(&new_termios);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    while ((c = getchar()) != 27) {
        putchar(c);
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);

    return 0;
}