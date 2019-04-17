#include "catch.h"
#include "CellTypes.h"
#include "GameModel.h"
#include "GameView.h"

#include <stdexcept>
#include <iostream>

using namespace std;

#define SIZE 10

//Helper functions for testing
bool isBoardEqualGOL(GameBoard a, GameBoard b){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(a[i][j].s == b[i][j].s) continue;
            return false;
        }
    }
    return true;
}

GameBoard initEmptyBoardGOL(nat maxRow, nat maxCol){
    GameBoard board;
    for(nat i = 0; i < maxRow; i++){
        SeqCell tmpRow;
        for(nat j = 0; j < maxCol; j++){
            Cell tmpCell = { i, j, static_cast<Status>(0) };
            tmpRow.push_back(tmpCell);
        }
        board.push_back(tmpRow);
    }
    return board;
}

//GameOFLife tests
TEST_CASE("tests for GameOfLife" , "[GameOfLife]"){

    SECTION("Testing glider pattern"){
        //Setup for testing    
        GameView ui;
        GameBoard initBoard = ui.readBoard("test/GliderPatternInput.txt");        
        GameModel tmpModel(initBoard);

        cout << "\nPart of the testing from GameOfLife.cpp\n";
        cout << "-------------------------------------------\n";
        cout << "Glider Pattern\n";
        
        ui.printBoard(tmpModel.get_board());

        tmpModel.simulate(1);

        ui.printBoard(tmpModel.get_board());

        tmpModel.simulate(1);

        ui.printBoard(tmpModel.get_board());

        tmpModel.simulate(1);

        ui.printBoard(tmpModel.get_board());  

        tmpModel.simulate(1);

        ui.printBoard(tmpModel.get_board()); 

        ui.writeBoard("test/GliderPatternOutput.txt", tmpModel.get_board());       
    }
}