#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>

int gameover, score;
int x, y, fruitx, fruity, flag;
int tailx[100], taily[100];
int nTail;

#define width 20
#define height 20

void setup() {
    gameover = 0;
    x = width / 2;
    y = height / 2;
    fruitx = rand() % width;
    fruity = rand() % height;
    score = 0;
    nTail = 0;
}

void draw() {
    system("cls");

    int i, j, k;

    for (i = 0; i < width + 2; i++)
        printf("#");
    printf("\n");

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (j == 0) printf("#");

            if (i == y && j == x)
                printf("O");
            else if (i == fruity && j == fruitx)
                printf("F");
            else {
                int print = 0;
                for (k = 0; k < nTail; k++) {
                    if (tailx[k] == j && taily[k] == i) {
                        printf("o");
                        print = 1;
                        break;
                    }
                }
                if (!print) printf(" ");
            }

            if (j == width - 1) printf("#");
        }
        printf("\n");
    }

    for (i = 0; i < width + 2; i++)
        printf("#");

    printf("\nScore: %d", score);
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': flag = 1; break;
            case 'd': flag = 2; break;
            case 'w': flag = 3; break;
            case 's': flag = 4; break;
            case 'x': gameover = 1; break;
        }
    }
}

void logic() {
    int i;
    int prevx = tailx[0];
    int prevy = taily[0];
    int prev2x, prev2y;

    tailx[0] = x;
    taily[0] = y;

    for (i = 1; i < nTail; i++) {
        prev2x = tailx[i];
        prev2y = taily[i];
        tailx[i] = prevx;
        taily[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }

    switch (flag) {
        case 1: x--; break;
        case 2: x++; break;
        case 3: y--; break;
        case 4: y++; break;
    }

    // Wall collision
    if (x >= width || x < 0 || y >= height || y < 0)
        gameover = 1;

    // Tail collision
    for (i = 0; i < nTail; i++) {
        if (tailx[i] == x && taily[i] == y)
            gameover = 1;
    }

    // Fruit eaten
    if (x == fruitx && y == fruity) {
        score += 10;
        fruitx = rand() % width;
        fruity = rand() % height;
        nTail++;
    }
}

int main() {
    setup();

    while (!gameover) {
        draw();
        input();
        logic();
        Sleep(100);
    }

    printf("\nGame Over! Final Score = %d\n", score);
    return 0;
}
