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

string drawRow(int widthScreen, int startingNumber) {
    string column = "| " ;
    int spacee = (widthScreen-9)/3;
    string spaceS(spacee,' ');
    string repeatedRow = "";
    for (int i = startingNumber; i < startingNumber + 3; i++ ){
        repeatedRow += column + to_string(i) + spaceS;
    }
    string row = repeatedRow + column;
    return row;
    
}

void drawBoard() {
    int widthScreen = 33; // use multiples here
    
    string linesuperior = getHorizontalLine(widthScreen);

    string table = "";

    for(int i = 1; i < 9; i = i+3) {
        string row = drawRow(widthScreen, i);
        table += linesuperior + "\n" + row  + "\n";

    }

    std::cout << table << linesuperior << + "\n";
}