#include "catch.h"
#include "CellTypes.h"
#include "GameView.h"

#include <stdexcept>
#include <iostream>

using namespace std;

#define SIZE 10

//Helper functions for testing
bool isBoardEqualGV(GameBoard a, GameBoard b){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(a[i][j].s == b[i][j].s) continue;
            return false;
        }
    }
    return true;
}

GameBoard initEmptyBoardGV(nat maxRow, nat maxCol){
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

//GameView tests
TEST_CASE("tests for GameView" , "[GameView]"){

    SECTION("Testing writing to file"){        
        //Setup for testing        
        GameView ui;    
        GameBoard a = initEmptyBoardGV(SIZE, SIZE);
        
        ui.writeBoard("test/GameViewTest.txt", a);
        GameBoard b = ui.readBoard("test/GameViewTest.txt");

        //Testing whether the outputted board is accurate
        REQUIRE(isBoardEqualGV(a, b));           
    } 

    SECTION("Testing reading from file"){    
        //Setup for testing        
        GameView ui;    
        GameBoard a = initEmptyBoardGV(SIZE, SIZE);

        ui.writeBoard("test/GameViewTest.txt", a);
        GameBoard b = ui.readBoard("test/GameViewTest.txt");

         //Testing errors when reading file that does not exist
        REQUIRE_THROWS_AS(ui.readBoard("rrrr.txt"), runtime_error);

        //Testing whether the read board is accurate
        REQUIRE(isBoardEqualGV(a, b));           
    }   

    SECTION("Testing printing to console"){    
        //Setup for testing        
        GameView ui;    
        GameBoard a = initEmptyBoardGV(SIZE, SIZE);

        cout << "\nPart of the testing from testGameView.cpp\n";
        cout << "-------------------------------------------\n";
        cout << "Output should be 10x10 matrix of all zeros (dead cells)\n";

        //Visually test if a 10 by 10 board of dead cells (0) is printed to console
        ui.printBoard(a);        
    }   
}