#include "catch.h"
#include "CellTypes.h"
#include "GameModel.h"

#include <stdexcept>

using namespace std;

#define SIZE 10

//Helper functions for testing
bool isBoardEqualGM(GameBoard a, GameBoard b){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(a[i][j].s == b[i][j].s) continue;
            return false;
        }
    }
    return true;
}

GameBoard initEmptyBoardGM(nat maxRow, nat maxCol){
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

Cell getCellGM(nat row, nat col, GameBoard b){
    Cell temp;
    if(row < 0 || row > SIZE - 1) throw out_of_range("Not a valid cell");
    if(col < 0 || col > SIZE - 1) throw out_of_range("Not a valid cell");
    for(int i = 0; i < 1; i++){
        for(int j = 0; j < 1; j++){
            Cell temp = b[i][j];
            if(temp.row == row && temp.col == col) return b[i][j];
        }
    }
    return temp;
}

//GameModel tests
TEST_CASE("tests for GameModel" , "[GameModel]"){

    SECTION("Testing constructor"){    
        //Setup for testing        
        GameBoard badRows = initEmptyBoardGM(SIZE-1, SIZE);
        GameBoard badColumns = initEmptyBoardGM(SIZE, SIZE-1);
        GameBoard correct = initEmptyBoardGM(SIZE, SIZE);
        
        GameModel tmpModel(correct);

        //Testing whether the constructor initialized properly
        REQUIRE(isBoardEqualGM(correct, tmpModel.get_board()));        

        //Testing for errors when board is constructed with incorrect number of row
        REQUIRE_THROWS_AS(GameModel(badRows), invalid_argument);    

        //Testing for errors when board is constructed with incorrect number of columns
        REQUIRE_THROWS_AS(GameModel(badColumns), invalid_argument);     
    }    

    SECTION("Testing is_valid_pos"){
        //Setup for testing    
        GameBoard tmpBoard = initEmptyBoardGM(SIZE, SIZE);
        
        GameModel tmpModel(tmpBoard);
        
        //Testing a correct position
        REQUIRE(tmpModel.is_valid_pos(0, 9));    

        //Testing a incorrect position
        REQUIRE(!tmpModel.is_valid_pos(10, 0));   
        REQUIRE(!tmpModel.is_valid_pos(9, -1));   
        REQUIRE(!tmpModel.is_valid_pos(-1, 9));   
        REQUIRE(!tmpModel.is_valid_pos(0, 10)); 
    } 

    SECTION("Testing get_board"){
        //Setup for testing    
        GameBoard tmpBoard = initEmptyBoardGM(SIZE, SIZE);
        
        GameModel tmpModel(tmpBoard);
        
        //Testing if the get method returns the board accurately
        REQUIRE(isBoardEqualGM(tmpBoard, tmpModel.get_board())); 
    } 

    SECTION("Testing invert_cell_status"){
        //Setup for testing    
        GameBoard tmpBoard = initEmptyBoardGM(SIZE, SIZE);
        
        GameModel tmpModel(tmpBoard);
        
        tmpModel.invert_cell_status(0, 0);
        Cell updatedCell = getCellGM(0, 0, tmpModel.get_board());

        //Testing if the cell status was inverted accurately
        REQUIRE(updatedCell.s == Alive); 
    } 

    SECTION("Testing simulate normally"){
        //Setup for testing    
        GameBoard initBoard = initEmptyBoardGM(SIZE, SIZE);
        initBoard[0][1].s = static_cast<Status>(1);
        initBoard[1][1].s = static_cast<Status>(1);
        initBoard[2][1].s = static_cast<Status>(1);
        
        GameBoard updatedBoard = initEmptyBoardGM(SIZE, SIZE);
        updatedBoard[1][0].s = static_cast<Status>(1);
        updatedBoard[1][1].s = static_cast<Status>(1);
        updatedBoard[1][2].s = static_cast<Status>(1);
        
        GameModel tmpModel(initBoard);
        
        tmpModel.simulate(1);
        
        //Testing if cells were born and killed correctly
        REQUIRE(isBoardEqualGM(updatedBoard, tmpModel.get_board())); 

        tmpModel.simulate(1);

        //Testing if cells were born and killed correctly
        REQUIRE(isBoardEqualGM(initBoard, tmpModel.get_board()));

        tmpModel.simulate(2);

        //Testing if cells were born and killed correctly
        REQUIRE(isBoardEqualGM(initBoard, tmpModel.get_board()));
    } 

    SECTION("Testing simulate with edges"){
        //Setup for testing    
        GameBoard initBoard = initEmptyBoardGM(SIZE, SIZE);
        initBoard[0][0].s = static_cast<Status>(1);
        initBoard[1][0].s = static_cast<Status>(1);
        initBoard[2][0].s = static_cast<Status>(1);
        
        GameBoard updatedBoard = initEmptyBoardGM(SIZE, SIZE);
        updatedBoard[1][0].s = static_cast<Status>(1);
        updatedBoard[1][1].s = static_cast<Status>(1);
        
        GameModel tmpModelA(initBoard);
        GameModel tmpModelB(initBoard);
        
        tmpModelA.simulate(1);
        
        //Testing if cells were born and killed correctly
        REQUIRE(isBoardEqualGM(updatedBoard, tmpModelA.get_board())); 

        tmpModelA.simulate(1);
        updatedBoard = initEmptyBoardGM(SIZE, SIZE);

        //Testing if cells were born and killed correctly
        REQUIRE(isBoardEqualGM(updatedBoard, tmpModelA.get_board()));

        tmpModelB.simulate(2);
        
        //Testing if cells were born and killed correctly
        REQUIRE(isBoardEqualGM(updatedBoard, tmpModelB.get_board()));
    }
}