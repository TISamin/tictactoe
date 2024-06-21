#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 3

char board[SIZE][SIZE];
const char player = 'X';
const char computer = 'O';

void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

int main()
{
    char winner;
    char response;

    srand(time(0));

    do
    {
        winner = ' ';
        response = ' ';
        resetBoard();

        while (winner == ' ' && checkFreeSpaces() > 0)
        {
            printBoard();
            playerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpaces() == 0)
            {
                break;
            }
            computerMove();
            winner = checkWinner();
        }

        printBoard();
        printWinner(winner);

        printf("\nWould you like to play again? (Y/N): ");
        scanf(" %c", &response);
        response = toupper(response);

    } while (response == 'Y');

    printf("Thanks for playing.\n");

    return 0;
}

void resetBoard()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = ' ';
        }
    }
}

void printBoard()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1)
                printf("|");
        }
        printf("\n");
        if (i < SIZE - 1)
            printf("---|---|---\n");
    }
}

int checkFreeSpaces()
{
    int freeSpaces = SIZE * SIZE;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] != ' ')
            {
                freeSpaces--;
            }
        }
    }
    return freeSpaces;
}

void playerMove()
{
    int x, y;

    do
    {
        printf("Enter the row #(1-3): ");
        scanf("%d", &x);
        printf("Enter the column #(1-3): ");
        scanf("%d", &y);
        x--;
        y--;

        if (x >= 0 && x < SIZE && y >= 0 && y < SIZE && board[x][y] == ' ')
        {
            board[x][y] = player;
            break;
        }
        else
        {
            printf("Invalid move. Try again.\n");
        }
    } while (1);
}

void computerMove()
{
    int i, j;
    // Check for strategic moves
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = computer;
                if (checkWinner() == computer)
                {
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = player;
                if (checkWinner() == player)
                {
                    board[i][j] = computer;
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    // If no strategic move is found, make a random move
    int x, y;
    do
    {
        x = rand() % SIZE;
        y = rand() % SIZE;
    } while (board[x][y] != ' ');

    board[x][y] = computer;
}

char checkWinner()
{
    // Check rows and columns
    for (int i = 0; i < SIZE; i++)
    {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != ' ')
        {
            return board[i][0];
        }
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != ' ')
        {
            return board[0][i];
        }
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != ' ')
    {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != ' ')
    {
        return board[0][2];
    }

    return ' ';
}

void printWinner(char winner)
{
    if (winner == player)
    {
        printf("You Win!!!\n");
    }
    else if (winner == computer)
    {
        printf("You Lose :(\n");
    }
    else
    {
        printf("It's A Tie :)\n");
    }
}
