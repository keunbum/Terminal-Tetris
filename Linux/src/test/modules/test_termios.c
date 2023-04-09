#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int test_termios(int argc, char* argv[])
{
    (void)argc;
    (void)argv;
    
    int c;
    static struct termios oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    cfmakeraw(&newt);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while ((c = getchar()) != 27) {
        putchar(c);
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return 0;
}