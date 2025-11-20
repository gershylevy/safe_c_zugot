/*------------------------------------------------------
* Filename: 8_queens.c
* Description: Find a solution to the 8 queens puzzle.
* Author: Gershon Levy and Dolev Dilmoney
-------------------------------------------------------*/

// x=j, y=i

#include <stdio.h>

#define CHESS_BOARD_LENGTH (8)
#define CHESS_BOARD_WIDTH (8)
#define NUMBER_OF_QUEENS (8)

#define EMPTY 0
#define QUEEN 1
#define THREATEN 2

#define SUCCESS 1
#define FAILURE 0

int solution_counter = 0;

/*------------------------------------------------------
* Function Name - print_board
*
* Function Purpose - To print a chess board
*
* Parameters –  [IN - board: The board to print]
*
* Return Values - None
*
* Author - Gershon Levy and Dolev Dilmoney
-------------------------------------------------------*/

void print_board(int board[CHESS_BOARD_LENGTH][CHESS_BOARD_WIDTH])
{
    int i = 0;
    int j = 0;

    for (i = 0; i < CHESS_BOARD_LENGTH; ++i)
    {
        for (j = 0; j < CHESS_BOARD_WIDTH; ++j)
        {
            if (board[i][j] == EMPTY || board[i][j] == THREATEN)
            {
                printf("- ");
            }
            else
            {
                printf("Q ");
            }
        }
        printf("\n");
    }
}

/*------------------------------------------------------
* Function Name - all_threats
*
* Function Purpose - Find all the threatened places on the board.
*
* Parameters –  [IN - board: The board]
*
* Return Values - None
*
* Author - Gershon Levy and Dolev Dilmoney
-------------------------------------------------------*/

void all_threats(int board[CHESS_BOARD_LENGTH][CHESS_BOARD_WIDTH])
{
    int i, j, k, row, col;
    int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    // clear all threats
    for (i = 0; i < CHESS_BOARD_LENGTH; ++i)
    {
        for (j = 0; j < CHESS_BOARD_WIDTH; ++j)
        {
            if (board[i][j] == THREATEN)
            {
                board[i][j] = EMPTY;
            }
        }
    }

    for (i = 0; i < CHESS_BOARD_LENGTH; i++)
    {
        for (j = 0; j < CHESS_BOARD_WIDTH; j++)
        {
            // if we found a queen
            if (board[i][j] == QUEEN)
            {
                // for loop to mark threats in all 8 directions
                for (k = 0; k < 8; k++)
                {
                    row = i + directions[k][0];
                    col = j + directions[k][1];
                    // go until we reach the end
                    while (row >= 0 && row < CHESS_BOARD_LENGTH && col >= 0 && col < CHESS_BOARD_WIDTH)
                    {
                        if (board[row][col] != QUEEN)
                        {
                            board[row][col] = THREATEN;
                        }
                        row += directions[k][0];
                        col += directions[k][1];
                    }
                }
            }
        }
    }
}

/*------------------------------------------------------
* Function Name - place_queens
*
* Function Purpose - Solve the puzzle.
*
* Parameters –  [IN - board: The board]
*               [IN - row: Our current row (for recursion)]
*
* Return Values - 0: Fail
*                 1: Success
*
* Author - Gershon Levy and Dolev Dilmoney
-------------------------------------------------------*/

int place_queens(int board[CHESS_BOARD_LENGTH][CHESS_BOARD_WIDTH], int row)
{
    int col = 0;
    if (row >= CHESS_BOARD_WIDTH)
    {
        solution_counter++;
        return FAILURE; /* we let the program "fail" until it find all of the soluations, then it just finish running and we can print the number of the solutions*/
    }

    for (col = 0; col < CHESS_BOARD_LENGTH; ++col)
    {
        if (board[row][col] == EMPTY)
        {
            board[row][col] = QUEEN;
            all_threats(board);

            if (place_queens(board, row + 1) == 1) /* recursive, if the program succeed we return success and if the fail then it try to locate the queens again*/
            {
                return SUCCESS;
            }

            board[row][col] = EMPTY;
            all_threats(board);
        }
    }
    return FAILURE;
}

int main()
{
    int board[CHESS_BOARD_LENGTH][CHESS_BOARD_WIDTH] = {EMPTY}; // 0- normal, 1-queen, 2- threatened
    int i = 0;
    int j = 0;

    place_queens(board, 0);
    printf("Number of solutions: %d", solution_counter);
}