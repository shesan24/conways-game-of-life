/**
 * \file CellTypes.h
 * \author Shesan Bala
 * \brief Library exporting cell types.
 */
#ifndef A4_CELL_TYPES_H_
#define A4_CELL_TYPES_H_

/**
 * \brief Describes a natural number.
 */
typedef unsigned int nat;

/**
 * \brief Prefixed size of the board.
 */
#define SIZE 10

/**
 * \brief Represents status of a cell, dead or alive.
 */
enum Status
{    
    Dead,   //0 for dead
    Alive   //1 for alive
};

/**
 * \brief Represents a cell.
 */
struct Cell
{
    nat row;
    nat col;
    Status s;
};

#endif