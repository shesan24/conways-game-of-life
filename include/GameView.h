/**
 * \file GameView.h
 * \author Shesan Bala
 * \brief Library of functions for the view portion of the game.
 */
#ifndef A4_GAME_VIEW_H_
#define A4_GAME_VIEW_H_

#include "CellTypes.h"

#include <vector>
#include <string>

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
 *  \brief Class implementing the interface of the game.
 *  \details Provides different functionalities to view and interact with the game.
 */
class GameView { 
    public:
      /**
        *  \brief Reads and creates a 2D vector of cells (game board) from an input file.
        *  \param filename String of the input file name.
        *  \exception Throws runtime_error if the given input file is not found. 
        *  \return GameBoard 2D vector of cells.
        */  
      GameBoard readBoard(string filename);

      /**
        *  \brief Writes a 2D vector of cells to an output file.
        *  \param filename String of the input file name.
        *  \param b 2D vector of cells.
        */  
      void writeBoard(string filename, GameBoard b);

      /**
        *  \brief Writes a 2D vector of cells to the console.
        *  \param b 2D vector of cells.
        */  
      void printBoard(GameBoard b);
};

#endif