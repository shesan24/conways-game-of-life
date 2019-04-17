#include "GameView.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <string>
#include <iterator>
#include <sys/stat.h>

GameBoard GameView::readBoard(string filename) {

    struct stat fileInfo;
    if(!(stat(filename.c_str(), &fileInfo) == 0))  throw runtime_error("File not found!");
    
    ifstream input( filename );   
    
    GameBoard board;    

    nat row = 0;
    for(string line; getline( input, line);) {
        SeqCell tmpRow;
        
        istringstream iss(line);
        vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};
        
        nat col = 0;
        for(string s : tokens){            
            Cell tmpCell = { row, col, static_cast<Status>(stoi(s)) };
            tmpRow.push_back(tmpCell);
            col++;
        }
        
        board.push_back(tmpRow);
        row++;
    }

    return board;
}

void GameView::writeBoard(string filename, GameBoard b) {
    string tmp = "";    
    
    for(int i = 0; i < SIZE - 1; i++){
        for(int j = 0; j < SIZE - 1; j++){
            if(b[i][j].s) tmp.append("1 ");
            else tmp.append("0 ");
        }
        if(b[i][SIZE - 1].s) tmp.append("1");
        else tmp.append("0");
        tmp.append("\n");
    }
    for(int k = 0; k < SIZE - 1; k++){
        if(b[SIZE - 1][k].s) tmp.append("1 ");
        else tmp.append("0 ");
    }
    if(b[SIZE - 1][SIZE - 1].s) tmp.append("1");
    else tmp.append("0");

    ofstream out(filename);
    out << tmp;
    out.close();
}

void GameView::printBoard(GameBoard b){
    cout << " \n";
    for(SeqCell row : b){
        for(Cell c : row){
            cout << c.s << " ";
        }
        cout << " \n";
    }
    cout << " \n";
}