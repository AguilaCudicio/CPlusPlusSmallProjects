#include "drawboard.hpp"

#include <stdlib.h> 

#include <time.h>


bool isSpaceFree(int gameMatrix[3][3], int position) {
    int rowPos = (int)(position-1)/3;
    int colPos = (position-1) % 3;
    return (gameMatrix[rowPos][colPos] == 0);
}

int askUserInput(int gameMatrix[3][3]) {
    
    int x;
    cout << "Type cell number:";
    cin >> x;

    if (isSpaceFree(gameMatrix,x)) return x;
    else {
        cout << "Please type a valid, free cell number\n";
        return askUserInput(gameMatrix);
    }
}


void editMatrix(int gameMatrix[3][3], int input, int newvalue) {
    int rowPos = (int)(input-1)/3;
    int colPos = (input-1) % 3;
    gameMatrix[rowPos][colPos] = newvalue;
}

bool isMatrixFull(int gameMatrix[3][3]) {
    for (int i = 0; i < 3; i++ ){
        for (int j = 0; j < 3; j++ ){
            if (gameMatrix[i][j]==0) return false;
        }
    }
    return true;
}

// 0 game not finished yet
// 1 human won
// 2 computer won
// 3 tie
int getCurrentWinner(int gameMatrix[3][3]) {
    // check horizontal or vertical win
    for (int i = 0; i < 3; i++ ){
        bool cond1 = gameMatrix[0][i] == gameMatrix[1][i];
        bool cond2 = gameMatrix[0][i] == gameMatrix[2][i];
        if (cond1 && cond2) return gameMatrix[0][i];

        bool cond3 = gameMatrix[i][0] == gameMatrix[i][1];
        bool cond4 = gameMatrix[i][0] == gameMatrix[i][2];
        if (cond3 && cond4) return gameMatrix[i][0];
    }
    // check cross
    bool condCross1 = gameMatrix[0][0] == gameMatrix[1][1];
    bool condCross2 = gameMatrix[2][2] == gameMatrix[1][1];

    bool condCross3 = gameMatrix[0][2] == gameMatrix[1][1];
    bool condCross4 = gameMatrix[2][0] == gameMatrix[1][1];
    if ((condCross3 && condCross4)||(condCross1 && condCross2)) return gameMatrix[1][1];

    // if matrix complete, it's a tie
    if (isMatrixFull(gameMatrix)) 
        return 3;

    // if it returns 0, nobody has won yet
    return 0;
}

void printWinner(int currentWinner) {

    if (currentWinner == 1) 
        cout << "YOU won!\n";
    if (currentWinner == 2) 
        cout << "COMPUTER won!\n";
    if (currentWinner == 3) 
        cout << "It's a tie!\n";
}


int getComputerInputAccordingToValue(int gameMatrix[3][3], int value) {
    for (int i = 0; i < 3; i++ ){
        if((gameMatrix[0][i] == gameMatrix[1][i])&&(gameMatrix[0][i]==value)&&(gameMatrix[2][i]==0)) {
            return 7+i;
        }
        if((gameMatrix[0][i] == gameMatrix[2][i])&&(gameMatrix[0][i]==value)&&(gameMatrix[1][i]==0)) {
            return 4+i;
        }
        if((gameMatrix[1][i] == gameMatrix[2][i])&&(gameMatrix[1][i]==value)&&(gameMatrix[0][i]==0)) {
            return i+1;
        }
        if((gameMatrix[i][0] == gameMatrix[i][1])&&(gameMatrix[i][0]==value)&&(gameMatrix[i][2]==0)) {
            return i*3+3;
        }
        if((gameMatrix[i][0] == gameMatrix[i][2])&&(gameMatrix[i][0]==value)&&(gameMatrix[i][1]==0)) {
            return i*3+2;
        }
        if((gameMatrix[i][1] == gameMatrix[i][2])&&(gameMatrix[i][1]==value)&&(gameMatrix[i][0]==0)) {
            return i*3+1;
        }
    }

    if ((gameMatrix[0][0]==gameMatrix[1][1])&&(gameMatrix[0][0]==value)&&(gameMatrix[2][2]==0)) {
        return 9;
    }
    if ((gameMatrix[0][0]==gameMatrix[2][2])&&(gameMatrix[0][0]==value)&&(gameMatrix[1][1]==0)) {
        return 5;
    }
    if ((gameMatrix[1][1]==gameMatrix[2][2])&&(gameMatrix[1][1]==value)&&(gameMatrix[0][0]==0)) {
        return 1;
    }

    if ((gameMatrix[2][0]==gameMatrix[1][1])&&(gameMatrix[1][1]==value)&&(gameMatrix[0][2]==0)) {
        return 3;
    }
    if ((gameMatrix[2][0]==gameMatrix[0][2])&&(gameMatrix[2][0]==value)&&(gameMatrix[1][1]==0)) {
        return 5;
    }
    if ((gameMatrix[1][1]==gameMatrix[0][2])&&(gameMatrix[1][1]==value)&&(gameMatrix[2][0]==0)) {
        return 7;
    }

    return 0;
    
}

int decideComputerInput(int gameMatrix[3][3]) {
    // Can computer win?
    int compWins = getComputerInputAccordingToValue(gameMatrix, 2);
    if (compWins > 0) return compWins;
    // Can computer avoid human wining?
    int humanDoesntWin = getComputerInputAccordingToValue(gameMatrix, 1);
    if (humanDoesntWin > 0) return humanDoesntWin;
    
    // IF the middle is free, take it
    
    if (gameMatrix[1][1]==0) return 5;

    // In any other case, get a random free space
    bool taken = true;

    int random = 0;
    
    while (taken) {
        random = rand() % 9 + 1;
        taken = ! isSpaceFree(gameMatrix, random);
    }
    return random;
}

bool decideComputerStart() {
    srand (time(NULL));

    int random = rand() % 2 + 1;

    bool computerTurn = false;

    switch(random) {
        case 1: {
            cout << "YOU (X) start\n"; 
            return false;
        }
        default: { 
            cout << "COMPUTER (O) starts\n";
            return true;
        }
    }
}


int main() {

    bool computerTurn = decideComputerStart();

    int gameMatrix[3][3] = {{0,0,0},{0,0,0},{0,0,0}};

    drawBoard(gameMatrix);

    int currentWinner = getCurrentWinner(gameMatrix);
    while (currentWinner == 0) {
        if (computerTurn) {
            cout << "Computer moves, \n";
            int computerinput = decideComputerInput(gameMatrix);
            editMatrix(gameMatrix, computerinput, 2);
        }
        else {
            int input = askUserInput(gameMatrix);
            editMatrix(gameMatrix, input, 1);
        }

        drawBoard(gameMatrix);
        computerTurn = !computerTurn;
        currentWinner = getCurrentWinner(gameMatrix);
    }

    printWinner(currentWinner);

    return 0;
}
