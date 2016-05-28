#include "inc/loc.h"

int main(int argc, char *argv[])
{
    g_mem = load_into_mem(-1, &qt_games);
    menu();
    return 0;
}
