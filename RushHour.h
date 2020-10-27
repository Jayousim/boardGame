#ifndef RUSH_HOUR_H
#define RUSH_HOUR_H 



#include "MoveVehicle.h"
template <int a>
struct INT{};

template < typename Board , int Row> 
struct FindRow{
	constexpr static int found = StartIndex< X ,0 ,typename Board::head>::index  ;
	constexpr static int index = ConditionalInteger<found>=0 , found , FindRow<typename Board::next ,Row+1>::index>::value ;
	constexpr static int row = ConditionalInteger< index>=0 , Row ,  FindRow<typename Board::next ,Row+1>::row>::value ; 
};
template <int Row> 
struct FindRow<List<>,Row>{
	constexpr static int index =-1 ; 
	constexpr static int row = -1; 
	
};
template<typename row , int index ,typename Max> 
struct EmptyWay{
	typedef typename GetAtIndex<index,row>::value cell ; 
	constexpr static bool result = (EmptyWay<row,index+1,Max>::result) && (cell::type ==EMPTY||cell::type ==X) ; 
};

template<typename row , int index > 
struct EmptyWay<row,index , INT<index+1>> {
	typedef typename GetAtIndex<index,row>::value cell ; 
	constexpr static bool result = (cell::type ==EMPTY||cell::type ==X) ; 
};

template < typename GameBoard > 
struct CheckWin{

constexpr static int rowIndex = FindRow<typename GameBoard::board , 0>::row ; 
constexpr static int index = FindRow<typename GameBoard::board  , 0>::index ;
typedef typename GetAtIndex<rowIndex ,typename GameBoard::board >::value row;
 
constexpr static bool result =  EmptyWay<row , index , INT<GameBoard::width>>::result  ;  	
	
};





#endif //RUSH_HOUR_H 
