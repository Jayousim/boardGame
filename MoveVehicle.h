#ifndef MOVE_VEHICLE_H
#define MOVE_VEHICLE_H 




#include "GameBoard.h" 
#include "Utilities.h"
#include "TransposeList.h" 



template<CellType cellType , Direction dir , int a> 
struct Move{
	constexpr static CellType type = cellType ; 
	constexpr static Direction direction = dir  ; 
	constexpr static int amount =a ;
};

template<CellType type ,  int steps ,typename List> 
struct StartIndex{
	typedef typename List::head cell ; 
	constexpr static int index = ConditionalInteger<type == (cell::type) , steps , StartIndex<type ,steps+1 , typename List::next>::index >::value  ; 
};


template<CellType type ,  int steps > 
struct StartIndex<type , steps , List<>> {
	constexpr static int index = -1 ;
};

// move vehicle cells recursive 
template<int start , int carLength , typename List> 
struct MoveVehicleAstepRightCells{
	typedef typename  GetAtIndex<start + carLength-1 , List >::value cell ;
	typedef typename  SetAtIndex<start + carLength ,cell , List>::list list_tt ; 
	typedef  BoardCell<EMPTY , UP , 0 > emptyCell ; 
	typedef typename  SetAtIndex<start + carLength-1 ,emptyCell ,list_tt>::list list_t ; 
	typedef typename  MoveVehicleAstepRightCells< start-1, carLength-1,list_t>::list list ; 
};

template<int start , typename List > 
struct MoveVehicleAstepRightCells< start,1  , List >{
	typedef typename GetAtIndex<start , List >::value cell ;
	typedef typename  SetAtIndex<start + 1 ,cell , List>::list list_tt ; 
	typedef   BoardCell<EMPTY , UP , 0 > emptyCell ; 
	typedef typename  SetAtIndex<start  ,emptyCell ,list_tt>::list list_t ; 
	typedef  list_t list ;  
};


template<  int start , typename List > 
struct MoveVehicleAstepRight{
	typedef typename GetAtIndex<start , List >::value cell ;
	typedef typename  GetAtIndex<start + cell::length -1 , List >::value nextCell ;
	static_assert(nextCell::type == EMPTY  , "cant move here!");
	typedef typename  MoveVehicleAstepRightCells<start , cell::length , List>::list  list  ; 
};


// move car to right 
template <int start , int a ,typename List >
struct MoveVehicleOneDimensionRight{
	
	typedef typename MoveVehicleOneDimensionRight<start+1 , a-1 ,typename MoveVehicleAstepRight<start , List >::list >::moved moved ; 
	
	
};
template < int start, typename List  >
struct MoveVehicleOneDimensionRight<start  ,0 ,List >{
	typedef List moved ; 
	
};
// car right 


// move car to Left  



// move vehicle cells recursive 
template<int start , int carLength, typename List > 
struct MoveVehicleAstepLeftCells{
	typedef typename  GetAtIndex<start , List>::value cell ;
	typedef typename  SetAtIndex<start-1 ,cell , List>::list list_tt ; 
	typedef   BoardCell<EMPTY , UP , 0 > emptyCell ; 
	typedef typename  SetAtIndex<start ,emptyCell ,list_tt>::list list_t ; 
	typedef typename  MoveVehicleAstepLeftCells<start +1 , carLength-1 , list_t>::list list ; 
};

template<  int start , typename List> 
struct MoveVehicleAstepLeftCells<start ,  1 , List>{
	typedef typename GetAtIndex<start , List>::value cell ;
	typedef typename  SetAtIndex<start -1  ,cell , List>::list list_tt ; 
	typedef BoardCell<EMPTY , UP , 0 > emptyCell ; 
	typedef typename  SetAtIndex<start,emptyCell ,list_tt>::list list_t ; 
	typedef  list_t list ;  
};



// move vehicle  takes start index
template<int start , typename List > 
struct MoveVehicleAstepLeft{
	typedef typename GetAtIndex<start , List>::value cell ;
	typedef typename  GetAtIndex<start -1 , List>::value nextCell ;
	static_assert(nextCell::type == EMPTY  , "cant move here!");
	typedef typename  MoveVehicleAstepLeftCells<start , cell::length , List>::list  list  ; 
};



template <int start , int a  , typename List >
struct MoveVehicleOneDimensionLeft{
	
	typedef typename MoveVehicleOneDimensionLeft<start-1 , a-1 ,typename MoveVehicleAstepLeft<start , List>::list>::moved moved ; 
	
	
};
template < int start ,typename List>
struct MoveVehicleOneDimensionLeft<start,0,List >{
	typedef List moved ; 
	
};


// move vehicle 
template <int  startIndex , int a , Direction d , typename List> 
struct MoveVehicleOneDimension{
	typedef typename MoveVehicleOneDimensionRight<startIndex , a , List>::moved moved ; 
};
template <int  startIndex , int a  , typename List> 
struct MoveVehicleOneDimension<startIndex ,a , UP , List>{
	typedef typename MoveVehicleOneDimensionRight<startIndex , a , List>::moved moved ; 
}; 
template <int  startIndex , int a  , typename List> 
struct MoveVehicleOneDimension<startIndex ,a , DOWN , List>{
	typedef typename MoveVehicleOneDimensionLeft<startIndex , a , List>::moved moved ; 
}; 
template <int  startIndex , int a  , typename List> 
struct MoveVehicleOneDimension<startIndex ,a , LEFT , List>{
	typedef typename MoveVehicleOneDimensionLeft<startIndex , a , List>::moved moved ; 
}; 


template<typename Board ,int r , int c , Direction d  ,int a> 
struct MoveVehicle{
constexpr static int rr = r ; 
constexpr static int cc = c  ; 	
constexpr static Direction dd = d ;
static_assert( (rr < ( Board::length)) && rr>=0  , "row index is out of range ");

static_assert((cc<(Board::width)) && cc>=0  , "column index is out of range ");

typedef typename GetAtIndex<rr , typename Board::board>::value row ; 
  
typedef typename GetAtIndex<cc , row >::value cell ;
 
static_assert(cell::type != EMPTY  , "cell is empty!");
static_assert(((cell::direction == RIGHT || cell::direction == LEFT)&&(dd==RIGHT || d==LEFT) ) ||   ((cell::direction == UP || cell::direction == DOWN)&&(dd==UP || dd==DOWN) )  , "cant move in this direction!");


typedef typename Conditional<(dd == UP || dd==DOWN) , typename Transpose<typename Board::board>::matrix  ,  typename  Board::board >::value list ;  
constexpr static int horz =  ConditionalInteger<dd == UP || dd==DOWN , cc  , rr>::value ; 
typedef typename GetAtIndex<horz , list >::value queue  ; 
constexpr static int startIndex =  StartIndex< cell::type ,0 ,queue>::index  ; 
typedef typename   MoveVehicleOneDimension<startIndex , a , d, queue>::moved   board; 
};

#endif //MOVE_VEHICLE_H 
