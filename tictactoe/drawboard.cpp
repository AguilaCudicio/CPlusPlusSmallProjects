#include "drawboard.hpp"

string repeatString(string s, int n) {

    string result;

    for(int i = 0; i < n; i++)
        result += s;
    
    return result;
}

string getHorizontalLine(int widthScreen) {
    string linesuperior(widthScreen, '-');
    return linesuperior;
}

string calculateStringPosition(int position, int gameMatrix[3][3]) {
    int rowPos = (int)(position-1)/3;
    int colPos = (position-1) % 3;
    int value = gameMatrix[rowPos][colPos];

    switch(value) {
        case 1: return "X";
        case 2: return "O";
        default:
                return to_string(position);
    }
}

string drawRow(int widthScreen, int startingNumber, int gameMatrix[3][3]) {
    string column = "| " ;
    int spacee = (widthScreen-9)/3;
    string spaceS(spacee,' ');
    string repeatedRow = "";
    for (int i = startingNumber; i < startingNumber + 3; i++ ){
        repeatedRow += column + calculateStringPosition(i, gameMatrix) + spaceS;
    }
    string row = repeatedRow + column;
    return row;
    
}

void drawBoard(int gameMatrix[3][3]) {
    int widthScreen = 33; // use multiples of 3 here
    
    string linesuperior = getHorizontalLine(widthScreen);

    string table = "";

    for(int i = 1; i < 9; i = i+3) {
        string row = drawRow(widthScreen, i, gameMatrix);
        table += linesuperior + "\n" + row  + "\n";

    }

    std::cout << table << linesuperior << + "\n";
}