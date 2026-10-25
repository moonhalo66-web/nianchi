#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define WIDTH  40
#define HEIGHT 20
#define MAX_LEN (WIDTH * HEIGHT)

typedef struct {
    int x;
    int y;
} Point;

static Point snake[MAX_LEN];
static Point food;
static int len = 3;
static int score = 0;
static int dx = 1;
static int dy = 0;
static int speed = 150;
static int dead = 0;
static HANDLE hOut;

static void gotoxy(int x, int y)
{
    COORD pos;
    pos.X = (SHORT)x;
    pos.Y = (SHORT)y;
    SetConsoleCursorPosition(hOut, pos);
}

static void hideCursor(void)
{
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &info);
}

static int onSnake(int x, int y, int includeTail)
{
    int n = includeTail ? len : len - 1;
    for (int i = 0; i < n; i++) {
        if (snake[i].x == x && snake[i].y == y) {
            return 1;
        }
    }
    return 0;
}

static void spawnFood(void)
{
    do {
        food.x = rand() % WIDTH;
        food.y = rand() % HEIGHT;
    } while (onSnake(food.x, food.y, 1));
    gotoxy(food.x + 1, food.y + 1);
    putchar('@');
}

static void updateScore(void)
{
    gotoxy(7, HEIGHT + 2);
    printf("%d", score);
}

static void drawBorder(void)
{
    for (int x = 0; x < WIDTH + 2; x++) {
        gotoxy(x, 0);
        putchar('#');
        gotoxy(x, HEIGHT + 1);
        putchar('#');
    }
    for (int y = 0; y < HEIGHT + 2; y++) {
        gotoxy(0, y);
        putchar('#');
        gotoxy(WIDTH + 1, y);
        putchar('#');
    }
    gotoxy(0, HEIGHT + 2);
    fputs("Score: 0", stdout);
    gotoxy(WIDTH + 5, HEIGHT + 2);
    fputs("WASD/Arrows: move  Q: quit", stdout);
}

static void init(void)
{
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    hideCursor();
    system("cls");
    for (int i = 0; i < len; i++) {
        snake[i].x = WIDTH / 2 - i;
        snake[i].y = HEIGHT / 2;
    }
    drawBorder();
    for (int i = len - 1; i >= 0; i--) {
        gotoxy(snake[i].x + 1, snake[i].y + 1);
        putchar(i == 0 ? 'O' : 'o');
    }
    spawnFood();
}

static void readInput(void)
{
    while (_kbhit()) {
        int c = _getch();
        if (c == 0 || c == 224) {
            c = _getch();
            if (c == 72 && dy != 1) {
                dx = 0;
                dy = -1;
            } else if (c == 80 && dy != -1) {
                dx = 0;
                dy = 1;
            } else if (c == 75 && dx != 1) {
                dx = -1;
                dy = 0;
            } else if (c == 77 && dx != -1) {
                dx = 1;
                dy = 0;
            }
        } else {
            c = tolower(c);
            if (c == 'w' && dy != 1) {
                dx = 0;
                dy = -1;
            } else if (c == 's' && dy != -1) {
                dx = 0;
                dy = 1;
            } else if (c == 'a' && dx != 1) {
                dx = -1;
                dy = 0;
            } else if (c == 'd' && dx != -1) {
                dx = 1;
                dy = 0;
            } else if (c == 'q') {
                dead = 2;
            }
        }
    }
}

static void step(void)
{
    Point head;
    head.x = snake[0].x + dx;
    head.y = snake[0].y + dy;

    if (head.x < 0 || head.x >= WIDTH || head.y < 0 || head.y >= HEIGHT) {
        dead = 1;
        return;
    }
    if (onSnake(head.x, head.y, 0)) {
        dead = 1;
        return;
    }

    int ate = (head.x == food.x && head.y == food.y);
    Point oldTail = snake[len - 1];
    if (ate) {
        len++;
    }
    for (int i = len - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }
    snake[0] = head;

    if (!ate) {
        gotoxy(oldTail.x + 1, oldTail.y + 1);
        putchar(' ');
    }
    gotoxy(snake[0].x + 1, snake[0].y + 1);
    putchar('O');
    gotoxy(snake[1].x + 1, snake[1].y + 1);
    putchar('o');

    if (ate) {
        score += 10;
        updateScore();
        if (speed > 70) {
            speed -= 4;
        }
        spawnFood();
    }
}

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    srand((unsigned)time(NULL));
    init();

    while (!dead) {
        readInput();
        if (!dead) {
            step();
        }
        if (!dead) {
            Sleep((DWORD)speed);
        }
    }

    gotoxy(WIDTH / 2 - 4, HEIGHT / 2 - 1);
    if (dead == 1) {
        fputs("Game Over!", stdout);
    } else {
        fputs("Bye!", stdout);
    }
    gotoxy(WIDTH / 2 - 5, HEIGHT / 2 + 1);
    printf("Score: %d", score);
    gotoxy(0, HEIGHT + 3);
    fputs("Press any key to exit...", stdout);
    _getch();
    gotoxy(0, HEIGHT + 4);
    return 0;
}
