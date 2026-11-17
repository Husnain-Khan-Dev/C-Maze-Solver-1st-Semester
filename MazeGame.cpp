#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

// Colors
void setColor(int color) {
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE), color
    );
}

// Maze Design
char arr[7][7] = {
    {'P','.','#','.','.','.','#'},
    {'#','.','#','.','#','.','#'},
    {'#','.','.','.','#','.','#'},
    {'#','#','#','.','#','.','#'},
    {'#','.','.','.','.','.','#'},
    {'#','.','#','#','#','.','#'},
    {'#','.','.','.','.','.','E'}
};

// Display Function
void displayMaze() {

    for(int i=0; i<7; i++) {
        for(int j=0; j<7; j++) {

            if(arr[i][j] == 'P') {
                setColor(10);
                cout << "P ";
            }
            else if(arr[i][j] == '#') {
                setColor(9);
                cout << "# ";
            }
            else if(arr[i][j] == 'E') {
                setColor(14);
                cout << "E ";
            }
            else {
                setColor(11);
                cout << ". ";
            }
        }
        cout << endl;
    }

    setColor(7);
}

int main() {

    int playerRow = 0, playerCol = 0;
    int newRow, newCol;
    char move;

    // Display maze only once
    system("cls");
    displayMaze();

    cout << "\nW = Up | S = Down";
    cout << "\nA = Left | D = Right";
    cout << "\nQ = Quit";

    while(true) {

        // Take input without Enter
        COORD inputPos = {0, 10};
        SetConsoleCursorPosition(
            GetStdHandle(STD_OUTPUT_HANDLE), inputPos
        );

        move = _getch();

        newRow = playerRow;
        newCol = playerCol;

        // Movement
        if(move == 'w' || move == 'W')
            newRow--;

        else if(move == 's' || move == 'S')
            newRow++;

        else if(move == 'a' || move == 'A')
            newCol--;

        else if(move == 'd' || move == 'D')
            newCol++;

        else if(move == 'q' || move == 'Q')
            break;

        // Check Position
        if(newRow >= 0 && newRow < 7 &&
           newCol >= 0 && newCol < 7 &&
           arr[newRow][newCol] != '#') {

            // Check Exit
            if(arr[newRow][newCol] == 'E') {
                COORD winPos = {0, 12};
                SetConsoleCursorPosition(
                    GetStdHandle(STD_OUTPUT_HANDLE), winPos
                );

                setColor(10);
                cout << "Congratulations! You Win!";
                setColor(7);
                break;
            }

            // Remove old player
            COORD oldPos = {
                (SHORT)(playerCol * 2),
                (SHORT)playerRow
            };

            SetConsoleCursorPosition(
                GetStdHandle(STD_OUTPUT_HANDLE), oldPos
            );

            setColor(11);
            cout << ". ";

            // Update position
            playerRow = newRow;
            playerCol = newCol;

            // Display new player position
            COORD newPos = {
                (SHORT)(playerCol * 2),
                (SHORT)playerRow
            };

            SetConsoleCursorPosition(
                GetStdHandle(STD_OUTPUT_HANDLE), newPos
            );

            setColor(10);
            cout << "P ";
            setColor(7);
        }
    }

    return 0;
}