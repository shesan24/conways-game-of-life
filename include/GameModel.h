/**
 * \file GameModel.h
 * \author Shesan Bala
 * \brief Template module to represent the state of the game.
 */
#ifndef A4_GAME_MODEL_H_
#define A4_GAME_MODEL_H_

#include "CellTypes.h"

#include <vector>

using namespace std;

/**
 * \brief Describes a list of rows of cells (the game board).
 */
typedef vector<vector<Cell>> GameBoard;

/**
 * \brief Describes a list of cells.
 */
typedef vector<Cell> SeqCell;

/**
 *  \brief Class representing the state of the game.
 *  \details GameModel template that allows for instantiations of the different game states.
 */
class GameModel {  
    private:
      /// Gameboard
      GameBoard B;
      /// Sequence of cells
      SeqCell I;

      /**
        *  \brief Count the number of neighbouring cells that are alive.
        *  \param c Current cell.
        *  \exception Throws out_of_range error if the given cell is not a valid position. 
        *  \return nat Number of neighbouring cells that are alive.
        */    
      nat cnt_neighbours_alive(Cell c); 

    public:
      /**
        *  \brief Default constructor. 
        */    
      GameModel();

      /**
        *  \brief Constructs a gameboard.
        *  \param s 2D vector of cells.
        *  \exception Throws invalid_argument error if the board does not have the correct number of rows. 
        *  \exception Throws invalid_argument error if the board does not have the correct number of columns.
        */
      GameModel(GameBoard s);

      /**
        *  \brief Gets the game board.
        *  \return GameBoard 2D vector of cells.
        */     
      GameBoard get_board();

      /**
        *  \brief Checks if the given position is a valid position in the board.
        *  \param row Index of the row.
        *  \param col Index of the column.
        *  \return bool True or False based on whether the position is valid.
        */  
      bool is_valid_pos(nat row, nat col); 

      /**
        *  \brief Invert the status of cell at a given position.
        *  \param row Index of the row.
        *  \param col Index of the column.
        *  \exception Throws out_of_range error if the given cell is not a valid position. 
        */
      void invert_cell_status(nat row, nat col);

      /**
        *  \brief Simulates the game for given number of iterations.
        *  \param n Number of iterations the game should be simulated to.
        */
      void simulate(nat n);
};

#endif