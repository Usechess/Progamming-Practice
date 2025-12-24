// Pong.c - simple console Pong for Windows (uses conio.h, windows.h)
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define WIDTH 80
#define HEIGHT 24
#define PADDLE_SIZE 4
#define WIN_SCORE 10

void cls() { system("cls"); }
void sleep_ms(int ms) { Sleep(ms); }

int main(void) {
    int leftY = HEIGHT/2 - PADDLE_SIZE/2;
    int rightY = HEIGHT/2 - PADDLE_SIZE/2;
    int ballX = WIDTH/2, ballY = HEIGHT/2;
    int dx = (rand()%2)?1:-1, dy = (rand()%2)?1:-1;
    int scoreL = 0, scoreR = 0;
    int ch;
    srand((unsigned)time(NULL));

    while (1) {
        // input
        if (_kbhit()) {
            ch = _getch();
            if (ch == 0 || ch == 224) { // special keys
                ch = _getch();
                if (ch == 72 && rightY > 1) rightY--;    // up arrow
                if (ch == 80 && rightY + PADDLE_SIZE < HEIGHT-1) rightY++; // down arrow
            } else {
                if (ch == 'w' || ch == 'W') if (leftY > 1) leftY--;
                if (ch == 's' || ch == 'S') if (leftY + PADDLE_SIZE < HEIGHT-1) leftY++;
                if (ch == 'q' || ch == 'Q') break;
            }
        }

        // move ball
        ballX += dx; ballY += dy;

        // top/bottom collision
        if (ballY <= 1) { ballY = 1; dy = -dy; }
        if (ballY >= HEIGHT-2) { ballY = HEIGHT-2; dy = -dy; }

        // left paddle collision
        if (ballX == 2) {
            if (ballY >= leftY && ballY < leftY + PADDLE_SIZE) {
                dx = -dx;
                // tweak dy by hit position
                int hit = ballY - leftY - PADDLE_SIZE/2;
                if (hit < 0) dy = -1; else if (hit > 0) dy = 1; else if (dy==0) dy = (rand()%2)?1:-1;
            }
        }

        // right paddle collision
        if (ballX == WIDTH-3) {
            if (ballY >= rightY && ballY < rightY + PADDLE_SIZE) {
                dx = -dx;
                int hit = ballY - rightY - PADDLE_SIZE/2;
                if (hit < 0) dy = -1; else if (hit > 0) dy = 1; else if (dy==0) dy = (rand()%2)?1:-1;
            }
        }

        // score
        if (ballX <= 0) {
            scoreR++;
            ballX = WIDTH/2; ballY = HEIGHT/2;
            dx = 1; dy = (rand()%2)?1:-1;
        }
        if (ballX >= WIDTH-1) {
            scoreL++;
            ballX = WIDTH/2; ballY = HEIGHT/2;
            dx = -1; dy = (rand()%2)?1:-1;
        }

        // render
        cls();
        // top border
        for (int x=0;x<WIDTH;x++) putchar('-');
        putchar('\n');

        for (int y=1; y<HEIGHT-1; y++) {
            for (int x=0; x<WIDTH; x++) {
                if (x==0 || x==WIDTH-1) putchar('|');
                else if (x==ballX && y==ballY) putchar('O');
                else if (x==1 && y>=leftY && y<leftY+PADDLE_SIZE) putchar('#');
                else if (x==WIDTH-2 && y>=rightY && y<rightY+PADDLE_SIZE) putchar('#');
                else putchar(' ');
            }
            putchar('\n');
        }

        // bottom border
        for (int x=0;x<WIDTH;x++) putchar('-');
        putchar('\n');

        // score and instructions
        printf("Left: %d    Right: %d    Controls: W/S for left, Up/Down for right, Q to quit\n", scoreL, scoreR);

        if (scoreL >= WIN_SCORE || scoreR >= WIN_SCORE) {
            printf("Game Over! Winner: %s\n", scoreL>scoreR ? "Left" : "Right");
            break;
        }

        sleep_ms(50);
    }

    return 0;
}