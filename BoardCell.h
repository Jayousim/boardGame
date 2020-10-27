#ifndef BOARD_CELL_H
#define BOARD_CELL_H 


#include "CellType.h"
#include "Direction.h"


template<CellType cltype  ,  Direction dir  ,int len >   
struct BoardCell {
	constexpr static CellType type = cltype  ;
	constexpr static Direction direction = dir ;
	constexpr static int length = len  ; 

};












#endif //BOARD_CELL_H 
