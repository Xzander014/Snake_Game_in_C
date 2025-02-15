#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>

struct termios old_prop;
#define WIDTH 50
#define LENGTH 20

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STOP,
    END
} dir;

int score = 0;
float speed = 1.0;
int fx, fy; // Food position
int sx, sy; // Snake head position
int tailX[100], tailY[100]; // Snake tail positions
int tailLength = 0; // Length of the snake's tail

void setter();
void resetter();
void printGame();
void clearScreen();
void setup();
void processInput();
int getInput();
int gameLoop();
int isFoodOnSnake(int x, int y);

int main()
{
    dir = STOP;
    setter();
    setup();
    sx = WIDTH / 2;
    sy = LENGTH / 2;

    while (1)
    {
        printGame();
        if (getInput())
            processInput();
        int result = gameLoop();
        usleep(speed * 100000); // Adjust speed
        if (result == 0)
        {
            printf("Game Over\n");
            break;
        }
    }
    resetter();
    return 0;
}

int gameLoop()
{
    // Move the tail
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = sx;
    tailY[0] = sy;
    for (int i = 1; i < tailLength; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Move the head
    switch (dir)
    {
    case UP:
        sy--;
        break;
    case DOWN:
        sy++;
        break;
    case RIGHT:
        sx++;
        break;
    case LEFT:
        sx--;
        break;
    case STOP:
        break;
    case END:
        return 0;
    }

    // Boundary checks
    if (sy < 0 || sy >= LENGTH || sx < 0 || sx >= WIDTH)
        return 0;

    // Check if snake collides with itself
    for (int i = 0; i < tailLength; i++)
    {
        if (tailX[i] == sx && tailY[i] == sy)
            return 0;
    }

    // Check if snake eats food
    if (sx == fx && sy == fy)
    {
        setup();
        score++;
        tailLength++;
        speed -= 0.05; // Adjust speed more gradually
    }

    return 1; // Game continues
}

int getInput()
{
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0;
}

void processInput()
{
    char m = getchar();
    switch (m)
    {
    case 'w':
        if (dir != DOWN) // Prevent reversing direction
            dir = UP;
        break;
    case 'a':
        if (dir != RIGHT)
            dir = LEFT;
        break;
    case 'd':
        if (dir != LEFT)
            dir = RIGHT;
        break;
    case 's':
        if (dir != UP)
            dir = DOWN;
        break;
    case 'x':
        dir = END;
        break;
    }
}

void printGame()
{
    clearScreen();
    printf("\n");
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    for (int i = 0; i < LENGTH; i++)
    {
        for (int j = 0; j < WIDTH + 2; j++)
        {
            if (j == 0 || j == WIDTH + 1)
            {
                printf("#");
            }
            else if (i == sy && j == sx + 1)
            {
                printf("O"); // Snake head
            }
            else if (i == fy && j == fx + 1)
            {
                printf("@"); // Food
            }
            else
            {
                int isTail = 0;
                for (int k = 0; k < tailLength; k++)
                {
                    if (tailX[k] + 1 == j && tailY[k] == i)
                    {
                        printf("o"); // Snake tail
                        isTail = 1;
                        break;
                    }
                }
                if (!isTail)
                    printf(" ");
            }
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\nCurrent score: %d\n", score);
}

void clearScreen()
{
    system("clear");
}

void setup()
{
    do
    {
        srand(time(NULL));
        fx = (rand() % WIDTH);
        fy = (rand() % LENGTH);
    } while (isFoodOnSnake(fx, fy)); // Ensure food doesn't spawn on the snake
}

int isFoodOnSnake(int x, int y)
{
    if (sx == x && sy == y)
        return 1;
    for (int i = 0; i < tailLength; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
            return 1;
    }
    return 0;
}

void setter()
{
    tcgetattr(STDIN_FILENO, &old_prop);
    atexit(resetter);
    struct termios new_prop = old_prop;
    new_prop.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_prop);
}

void resetter()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &old_prop);
}