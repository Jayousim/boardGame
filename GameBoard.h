#ifndef GAME_BOARD_H
#define GAME_BOARD_H 

#include "BoardCell.h"
#include "List.h"

template <typename list>
struct GameBoard{
	typedef  list board ; 
	constexpr static int  length =  board::size   ; 
	constexpr static int  width =  board::head::size   ; 
	
};
















#endif //GAME_BOARD_H 
