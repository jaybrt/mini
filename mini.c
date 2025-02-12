//
// Created by jaybrd on 8/1/24.
//

/*** includes ***/

#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>

/*** data ***/

struct termios orig_termios;

/*** terminal ***/

void die(const char *s) {
    perror(s);
    exit(1);
}

void disable_raw_mode(){
    if(tcsetattr(STDERR_FILENO, TCSAFLUSH, &orig_termios) == -1) die("tcsetattr");
}

void enable_raw_mode() {
    if(tcgetattr(STDERR_FILENO, &orig_termios) == -1) die("tcgetattr");
    atexit(disable_raw_mode);

    struct termios raw = orig_termios;

    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
    raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);

    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

/*** init ***/

int main(){
    enable_raw_mode();

    while(1){
        char c = 0;
        if(read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) die("read");

        if(iscntrl(c)){
            printf("%d\r\n", c);
        }
        else{
            printf("%d (%c)\r\n", c, c);
        }
        if(c == 'q') break;
    }

    return 0;
}

