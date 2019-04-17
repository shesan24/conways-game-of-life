#include "GameModel.h"

#include <stdexcept>

GameModel::GameModel() {}

GameModel::GameModel(GameBoard b) {    
    if(b.size() != 10) throw invalid_argument("Board must have 10 rows");
    
    for(SeqCell row : b){
        if(row.size() != 10) throw invalid_argument("All rows must have 10 columns");
    }

    this->B = b;
    this->I = SeqCell();
}

GameBoard GameModel::get_board() {
    return this->B;
}

bool GameModel::is_valid_pos(nat row, nat col) {
    if(row < 0 || row > SIZE - 1) return false;
    if(col < 0 || col > SIZE - 1) return false;
    return true;
}

void GameModel::invert_cell_status(nat row, nat col) {
    if(!is_valid_pos(row, col)) throw out_of_range("Not a valid cell");
    
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            Cell temp = this->B[i][j];
            if(temp.row == row && temp.col == col){
                if(temp.s == Alive){
                    this->B[i][j].s = static_cast<Status>(0);
                }
                else{
                   this->B[i][j].s = static_cast<Status>(1); 
                }
            }        
        }
    }
}

void GameModel::simulate(nat n) {
    for(nat i = 0; i < n; i++){

        //Collect cells that requires modification
        for(SeqCell row : this->B){
            for(Cell c : row){
                nat count = cnt_neighbours_alive(c);
                if(c.s == Alive && !(count == 2 || count == 3)) this->I.push_back(c);
                else if(c.s == Dead && count == 3) this->I.push_back(c);
            }
        }

        //Modify the collected cells
        for(Cell c : this->I){
            invert_cell_status(c.row, c.col);    
        }
        this->I.clear();
    }    
}



//Private Methods

nat GameModel::cnt_neighbours_alive(Cell c) {
    nat count = 0;
    
    //Only accessing valid neighbouring cells, then counting all neighbouring cells alive
    if(is_valid_pos(c.row - 1, c.col - 1) && this->B[c.row - 1][c.col - 1].s) count ++;
    if(is_valid_pos(c.row - 1, c.col) && this->B[c.row - 1][c.col].s) count ++;
    if(is_valid_pos(c.row - 1, c.col + 1) && this->B[c.row - 1][c.col + 1].s) count ++;
    if(is_valid_pos(c.row, c.col - 1) && this->B[c.row][c.col - 1].s) count ++;
    if(is_valid_pos(c.row, c.col + 1) && this->B[c.row][c.col + 1].s) count ++;
    if(is_valid_pos(c.row + 1, c.col - 1) && this->B[c.row + 1][c.col - 1].s) count ++;
    if(is_valid_pos(c.row + 1, c.col) && this->B[c.row + 1][c.col].s) count ++;
    if(is_valid_pos(c.row + 1, c.col + 1) && this->B[c.row + 1][c.col + 1].s) count ++;
    
    return count;
}