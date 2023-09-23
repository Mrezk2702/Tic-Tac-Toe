#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

typedef enum
{
    PLAYER1 = 1,
    PLAYER2 = 2
} ePlayerNum;
typedef struct
{
    int x;
    int y;
    ePlayerNum Num;
} Player;
COORD cord = {0, 0};
HANDLE hConsole = NULL;

void GoToXY(int x, int y);
void ClearLine(int lineNo);
void updateMatrix(void);
void setPlayerXY(ePlayerNum NUM);
void delay(int number_of_seconds);
char checkWinner();
/***
 *
 *  x|x|o
 *  -----
 *  o|x|o
 *  -----
 *  o|x|x
 *
 */

Player Player1 = {-1, -1, PLAYER1};
Player Player2 = {-1, -1, PLAYER2};

int arr[5][5] = {{' ', '|', ' ', '|', ' '},
                 {'-', '-', '-', '-', '-'},
                 {' ', '|', ' ', '|', ' '},
                 {'-', '-', '-', '-', '-'},
                 {
                     ' ',
                     '|',
                     ' ',
                     '|',
                     ' ',
                 }};

int counter = 0;
int main()
{
    int winner = 0;
    Player Player1;
    Player Player2;
    int mode = -1;
    // initialization
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("Player1: x\nPlayer2: o");
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    GoToXY(50, 0);
    printf("Tic-Tac-Toe");

    GoToXY(42, 1);
    printf("1:Play Against Bot  2: 1vs1");
    GoToXY(42, 2);
    printf("Select mode: ");
    scanf("%d", &mode);
    // CLEAR Line
    ClearLine(2);

    switch (mode)
    {
    case 1:
        GoToXY(48, 2);
        printf("Play Against Bot", mode);
        break;
    case 2:
        GoToXY(54, 2);
        printf("1vs1", mode);
    }

    if (mode == 2)
    {
        do
        {
            setPlayerXY(PLAYER1);
            updateMatrix();
            winner = checkWinner();
            GoToXY(0, 30);
            printf("Counter= %d\n", counter);
            printf("Winner= %d\n", winner);
            if (winner)
            {
                break;
            }
            if (counter == 9)
            {
                break;
            }
            setPlayerXY(PLAYER2);
            updateMatrix();
            GoToXY(0, 30);
            printf("Counter= %d\n", counter);
            printf("Winner= %d\n", winner);
            winner = checkWinner();
            GoToXY(0, 30);
            printf("Counter= %d\n", counter);
            printf("Winner= %d\n", winner);
            if (winner)
            {
                break;
            }
            GoToXY(0, 30);
            printf("Counter= %d\n", counter);
            printf("Winner= %d\n", winner);

        } while (TRUE);
    }
    switch (winner)
    {
    case 1:
        GoToXY(54, 7);
        printf("Player 1 Wins !!!!!!");
        break;
    case 2:
        GoToXY(54, 7);
        printf("Player 2 Wins !!!!!!");
        break;
    default:
        ClearLine(7);
        GoToXY(54, 7);
        printf("Draw!!!!!!");
    }

    while (1)
    {
    }
}

void GoToXY(int x, int y)
{
    cord.X = x;
    cord.Y = y;
    SetConsoleCursorPosition(hConsole, cord);
}

void ClearLine(int lineNo)
{
    for (int i = 0; i < 100; i++)
    {
        GoToXY(i, lineNo);
        printf(" ");
    }
}
void updateMatrix(void)
{
    for (int row = 0; row < 5; row++)
    {
        GoToXY(54, 10 + row);
        for (int col = 0; col < 5; col++)
        {
            printf("%c", arr[row][col]);
        }
    }
}

void setPlayerXY(ePlayerNum Num)
{
    counter++;

    char flag = 0;

    do
    {
        ClearLine(4);
        switch (Num)
        {
        case PLAYER1:
            GoToXY(42, 3);
            printf("Player 1:Enter x [0-2] and y[0-2] of your'X' ");
            GoToXY(45, 4);
            printf("x= ");
            scanf("%d", &(Player1.x));
            GoToXY(64, 4);
            printf("y= ");
            scanf("%d", &(Player1.y));
            if (arr[Player1.y * 2][Player1.x * 2] == ' ')
            {
                arr[Player1.y * 2][Player1.x * 2] = 'X';
                flag = 1;
            }
            else
            {
                GoToXY(45, 5);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                printf("Filled Position Try Again");
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                delay(1);
                ClearLine(5);
            }
            break;
        case PLAYER2:

            GoToXY(42, 3);
            printf("Player 2:Enter x [0-2] and y[0-2] of your'o' ");
            GoToXY(45, 4);
            printf("x= ");
            scanf("%d", &(Player2.x));
            GoToXY(64, 4);
            printf("y= ");
            scanf("%d", &(Player2.y));
            if (arr[Player2.y * 2][Player2.x * 2] == ' ')
            {
                arr[Player2.y * 2][Player2.x * 2] = 'o';
                flag = 1;
            }
            else
            {
                GoToXY(45, 5);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                printf("Filled Position Try Again");
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                delay(1);
                ClearLine(5);
            }
        }

    } while (flag == 0);
}

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

char checkWinner(void)
{
    int winner = 0;
    if (arr[0][0] == arr[2][2] && arr[2][2] == arr[4][4])
    {
        if (arr[0][0] == 'X')
        {
            winner = 1;
        }
        else if (arr[0][0] == 'o')
        {
            winner = 2;
        }
        else
        {
            winner = 0;
        }
    }
    else if (arr[0][4] == arr[2][2] && arr[2][2] == arr[4][0])
    {
        if (arr[2][2] == 'X')
        {
            winner = 1;
        }
        else if (arr[2][2] == 'o')
        {
            winner = 2;
        }
        else
        {
            winner = 0;
        }
    }
    else
    {
        // looping rows
        for (int rows = 0; rows < 5; rows += 2)
        {
            if (arr[rows][0] == arr[rows][2] && arr[rows][0] == arr[rows][4])
            {
                if (arr[rows][0] == 'X')
                {
                    winner = 1;
                    break;
                }
                else if (arr[rows][0] == 'o')
                {
                    winner = 2;
                    break;
                }
                else
                {
                    winner = 0;
                }
            }
        }
        // looping col
        for (int col = 0; col < 5; col += 2)
        {
            if (arr[0][col] == arr[2][col] && arr[2][col] == arr[4][col])
            {
                if (arr[0][col] == 'X')
                {
                    winner = 1;
                    break;
                }
                else if (arr[0][col] == 'o')
                {
                    winner = 2;
                    break;
                }
                else
                {
                    winner = 0;
                }
            }
        }
    }
    return winner;
}
