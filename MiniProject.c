#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char board[3][3];
int scoreX = 0, scoreO = 0;
int draws = 0, totalGames = 0;

char nameX[30], nameO[30];

void resetBoard()
{
    char num = '1';

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            board[i][j] = num++;
        }
    }
}

void displayBoard()
{
    printf("\n");
    printf("       +---+---+---+\n");

    for(int i = 0; i < 3; i++)
    {
        printf("       | %c | %c | %c |\n",
               board[i][0],
               board[i][1],
               board[i][2]);

        printf("       +---+---+---+\n");
    }
}

void displayScore()
{
    printf("\n========== SCOREBOARD ==========\n");
    printf("%s (X): %d\n", nameX, scoreX);
    printf("%s (O): %d\n", nameO, scoreO);
    printf("Draws: %d\n", draws);
    printf("Total Matches: %d\n", totalGames);
    printf("================================\n");
}

int checkWinner()
{
    for(int i = 0; i < 3; i++)
    {
        if(board[i][0] == board[i][1] &&
           board[i][1] == board[i][2])
            return 1;

        if(board[0][i] == board[1][i] &&
           board[1][i] == board[2][i])
            return 1;
    }

    if(board[0][0] == board[1][1] &&
       board[1][1] == board[2][2])
        return 1;

    if(board[0][2] == board[1][1] &&
       board[1][1] == board[2][0])
        return 1;

    return 0;
}

void playGame(int mode)
{
    int choice, row, col;
    char player = 'X';
    int moves = 0;

    resetBoard();

    while(moves < 9)
    {
        displayBoard();

        if(player == 'X')
            printf("\n%s's turn (X)\n", nameX);
        else
            printf("\n%s's turn (O)\n", nameO);

        if(mode == 2 && player == 'O')
        {
            do
            {
                choice = rand() % 9 + 1;
                row = (choice - 1) / 3;
                col = (choice - 1) % 3;
            }
            while(board[row][col] == 'X' ||
                  board[row][col] == 'O');

            printf("Computer chooses: %d\n", choice);
        }
        else
        {
            printf("Enter position (1-9): ");

            if(scanf("%d", &choice) != 1)
            {
                printf("Invalid input!\n");
                return;
            }

            if(choice < 1 || choice > 9)
            {
                printf("Invalid position!\n");
                continue;
            }

            row = (choice - 1) / 3;
            col = (choice - 1) % 3;

            if(board[row][col] == 'X' ||
               board[row][col] == 'O')
            {
                printf("Position occupied! Try again.\n");
                continue;
            }
        }

        board[row][col] = player;
        moves++;

        if(checkWinner())
        {
            displayBoard();

            if(player == 'X')
            {
                printf("\n*** %s WINS! ***\n", nameX);
                scoreX++;
            }
            else
            {
                printf("\n*** %s WINS! ***\n", nameO);
                scoreO++;
            }

            totalGames++;
            return;
        }

        if(player == 'X')
            player = 'O';
        else
            player = 'X';
    }

    displayBoard();

    printf("\n***** GAME DRAW! *****\n");
    draws++;
    totalGames++;
}

int main()
{
    int mode, again;

    srand(time(0));

    printf("\n");
    printf("====================================\n");
    printf("         TIC - TAC - TOE            \n");
    printf("          ULTIMATE EDITION          \n");
    printf("====================================\n");

    printf("\nEnter Player 1 name: ");
    scanf("%29s", nameX);

    printf("Enter Player 2 name (or Computer): ");
    scanf("%29s", nameO);

    do
    {
        printf("\n========== GAME MENU ==========\n");
        printf("1. Two Player Mode\n");
        printf("2. Play Against Computer\n");
        printf("3. View Scoreboard\n");
        printf("4. Exit Game\n");
        printf("===============================\n");

        printf("Choose option: ");
        if(scanf("%d", &mode) != 1)
            return 0;

        switch(mode)
        {
            case 1:
                playGame(1);
                displayScore();
                break;

            case 2:
                playGame(2);
                displayScore();
                break;

            case 3:
                displayScore();
                break;

            case 4:
                printf("\nThanks for playing!\n");
                break;

            default:
                printf("\nInvalid option!\n");
        }

        if(mode == 4)
            break;

        printf("\nReturn to menu? (1 = Yes, 0 = Exit): ");
        if(scanf("%d", &again) != 1)
            break;

    } while(again == 1);

    printf("\n================================\n");
    printf("          FINAL RESULTS          \n");
    displayScore();
    printf("       GAME OVER!                \n");
    printf("================================\n");

    return 0;
}