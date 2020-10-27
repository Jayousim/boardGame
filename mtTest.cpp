#include <iostream>
#include <typeinfo>
#include "RushHour.h"
#include "Printer.h"

namespace classesForTesting {

template <int x>
struct Int {
	static constexpr int value = x;
};

template <typename T1, typename T2>
struct cmp {
	static constexpr bool value = false;
};
template <typename T>
struct cmp<T,T> {
	static constexpr bool value = true;
};

};
using namespace classesForTesting;


static void listTest_Basic() {
	typedef List<Int<1>, Int<2>, Int<3>> list123;
	static_assert(cmp<list123::head, Int<1>>::value, "List::head Fail");
	static_assert(cmp<list123::next::head, Int<2>>::value, "List::next Fail");
	static_assert(list123::size == 3, "List::size Fail");

	typedef typename PrependList<Int<4>, list123>::list list4123;
	static_assert(list4123::size == 4, "List::PrependList Fail");
	static_assert(cmp<list4123::head,       Int<4>>::value, "List::PrependList Fail");
	static_assert(cmp<list4123::next::head, Int<1>>::value, "List::PrependList Fail");

	static_assert(cmp<GetAtIndex<0, list123>::value, Int<1>>::value, "List::GetAtIndex Fail");
	static_assert(cmp<GetAtIndex<1, list123>::value, Int<2>>::value, "List::GetAtIndex Fail");
	static_assert(cmp<GetAtIndex<2, list123>::value, Int<3>>::value, "List::GetAtIndex Fail");

	typedef typename SetAtIndex<0, Int<5>, list123>::list list523;
	static_assert(cmp<list523::head,             Int<5>>::value, "List::SetAtIndex Fail");
	static_assert(cmp<list523::next::head,       Int<2>>::value, "List::SetAtIndex Fail");
	static_assert(cmp<list523::next::next::head, Int<3>>::value, "List::SetAtIndex Fail");

	typedef typename SetAtIndex<2, Int<7>, list123>::list list127;
	static_assert(cmp<list127::head,             Int<1>>::value, "List::SetAtIndex Fail");
	static_assert(cmp<list127::next::head,       Int<2>>::value, "List::SetAtIndex Fail");
	static_assert(cmp<list127::next::next::head, Int<7>>::value, "List::SetAtIndex Fail");
}

static void listTest_Integration() {
	typedef List<> nil;
	typedef List<Int<5>> list5_expected;
	typedef List<Int<3>> list3_expected;
	typedef List<Int<5>, Int<3>> list53_expected;
	typedef List<Int<5>, Int<6>> list56_expected;
	typedef List<Int<7>, Int<5>, Int<3>> list753_expected;
	typedef List<Int<7>, Int<5>, Int<6>> list756_expected;
	typedef List<Int<7>, Int<7>, Int<6>> list776_expected;

	typedef PrependList<Int<5>, nil>::list list5;
	static_assert(cmp<list5, list5_expected>::value, "listTest_Integration Fail");
	static_assert(list5::size == 1, "listTest_Integration Fail");
	static_assert(cmp<list5::head, Int<5>>::value, "listTest_Integration Fail");
	static_assert(cmp<list5::next, nil>::value, "listTest_Integration Fail");

	typedef SetAtIndex<0, Int<3>, list5>::list list3;
	static_assert(cmp<list3, list3_expected>::value, "listTest_Integration Fail");
	static_assert(list3::size == 1, "listTest_Integration Fail");
	static_assert(cmp<list3::head, Int<3>>::value, "listTest_Integration Fail");
	static_assert(cmp<list3::next, nil>::value, "listTest_Integration Fail");

	typedef PrependList<Int<5>, list3>::list list53;
	static_assert(cmp<list53, list53_expected>::value, "listTest_Integration Fail");
	static_assert(list53::size == 2, "listTest_Integration Fail");
	static_assert(cmp<list53::head, Int<5>>::value, "listTest_Integration Fail");
	static_assert(cmp<list53::next, list3_expected>::value, "listTest_Integration Fail");
	static_assert(cmp<GetAtIndex<0, list53>::value, Int<5>>::value, "listTest_Integration Fail");
	static_assert(cmp<GetAtIndex<1, list53>::value, Int<3>>::value, "listTest_Integration Fail");

	typedef PrependList<Int<7>, list53>::list list753;
	static_assert(cmp<list753, list753_expected>::value, "listTest_Integration Fail");
	static_assert(list753::size == 3, "listTest_Integration Fail");
	static_assert(cmp<list753::head, Int<7>>::value, "listTest_Integration Fail");
	static_assert(cmp<list753::next, list53_expected>::value, "listTest_Integration Fail");
	static_assert(cmp<GetAtIndex<0, list753>::value, Int<7>>::value, "listTest_Integration Fail");
	static_assert(cmp<GetAtIndex<1, list753>::value, Int<5>>::value, "listTest_Integration Fail");
	static_assert(cmp<GetAtIndex<2, list753>::value, Int<3>>::value, "listTest_Integration Fail");

	typedef SetAtIndex<2, Int<6>, list753>::list list756;
	static_assert(cmp<list756, list756_expected>::value, "listTest_Integration Fail");
	static_assert(list756::size == 3, "listTest_Integration Fail");
	static_assert(cmp<list756::head, Int<7>>::value, "listTest_Integration Fail");
	static_assert(cmp<list756::next, list56_expected>::value, "listTest_Integration Fail");
	static_assert(cmp<GetAtIndex<0, list756>::value, Int<7>>::value, "listTest_Integration Fail");
	static_assert(cmp<GetAtIndex<1, list756>::value, Int<5>>::value, "listTest_Integration Fail");
	static_assert(cmp<GetAtIndex<2, list756>::value, Int<6>>::value, "listTest_Integration Fail");

	typedef SetAtIndex<1, Int<7>, list756>::list list776;
	static_assert(cmp<list776, list776_expected>::value, "listTest_Integration Fail");
	static_assert(list776::size == 3, "listTest_Integration Fail");
	static_assert(cmp<list776::head, Int<7>>::value, "listTest_Integration Fail");
	static_assert(list776::next::size == 2, "listTest_Integration Fail");
	static_assert(cmp<list776::next::head, Int<7>>::value, "listTest_Integration Fail");
	static_assert(list776::next::next::size == 1, "listTest_Integration Fail");
	static_assert(cmp<list776::next::next::head, Int<6>>::value, "listTest_Integration Fail");
	static_assert(list776::next::next::next::size == 0, "listTest_Integration Fail");
	static_assert(cmp<GetAtIndex<0, list776>::value, Int<7>>::value, "listTest_Integration Fail");
	static_assert(cmp<GetAtIndex<1, list776>::value, Int<7>>::value, "listTest_Integration Fail");
	static_assert(cmp<GetAtIndex<2, list776>::value, Int<6>>::value, "listTest_Integration Fail");
}

static void conditionalTest() {
	static_assert(ConditionalInteger<(0 != 1), 0, 1>::value == 0, "ConditionalInteger Fail");
	static_assert(ConditionalInteger<(0 == 1), 0, 1>::value == 1, "ConditionalInteger Fail");
	static_assert(cmp<Conditional<(0 != 1), Int<0>, Int<1>>::value, Int<0>>::value, "Conditional Fail");
	static_assert(cmp<Conditional<(0 == 1), Int<0>, Int<1>>::value, Int<1>>::value, "Conditional Fail");
}


static void providedExample() {
	typedef GameBoard< List<
	        List < BoardCell< EMPTY , RIGHT , 1>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< O , DOWN , 3>,      BoardCell< EMPTY , RIGHT , 0> >,
	        List < BoardCell< EMPTY , RIGHT , 2>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< A , RIGHT , 2>,     BoardCell< A , LEFT , 2>,      BoardCell< O , DOWN , 3>,      BoardCell< EMPTY , RIGHT , 0> >,
	        List < BoardCell< EMPTY , RIGHT , 3>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< X , RIGHT , 2>,     BoardCell< X , LEFT , 2>,      BoardCell< O , UP , 3>,        BoardCell< EMPTY , RIGHT , 0> >,
	        List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0> >,
	        List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< B , DOWN , 2>,      BoardCell< P , RIGHT , 3>,     BoardCell< P , RIGHT , 3>,     BoardCell< P , LEFT , 3> >,
	        List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< B , UP , 2>,        BoardCell< EMPTY , RIGHT , 0>, BoardCell< C , RIGHT , 2>,     BoardCell< C , LEFT , 2> >
	> > gameBoard;

	typedef List<
	        Move < B, UP, 1 > , Move < C, LEFT, 4 > , Move < A, LEFT, 2 > , Move < X, LEFT, 2 > , Move < B, UP, 3 > , Move < P, LEFT, 3 > , Move < O, DOWN, 3 >
	> moves;

	static_assert(List<BoardCell< EMPTY , RIGHT , 0>,BoardCell< EMPTY , RIGHT , 0>,BoardCell< EMPTY , RIGHT , 0>>::size == 3, "Fail");
    static_assert(List<>::size == 0, "Fail");

    MoveVehicle<gameBoard, 2, 3, LEFT, 2>::board b1; (void)b1; // Valid move (cast to void to suppress 'unused' warnings)

    //static_assert(CheckSolution<gameBoard, moves>::result, "Fail"); // Game should be solved
}



static void boardCellFieldsTest() {
	static_assert(BoardCell<EMPTY, DOWN, 3>::type == EMPTY, "BoardCell Fail");
	static_assert(BoardCell<EMPTY, DOWN, 3>::direction == DOWN, "BoardCell Fail");
	static_assert(BoardCell<EMPTY, DOWN, 3>::length == 3, "BoardCell Fail");

	static_assert(BoardCell<X, LEFT, 50>::type == X, "BoardCell Fail");
	static_assert(BoardCell<X, LEFT, 50>::direction == LEFT, "BoardCell Fail");
	static_assert(BoardCell<X, LEFT, 50>::length == 50, "BoardCell Fail");

}

static void gameBoardFieldsTest() {
	typedef List<
			List< BoardCell<EMPTY, UP, 0> >
		> list1x1;
	typedef GameBoard<list1x1> board1x1;
	static_assert(board1x1::width == 1, "GameBoard Fail");
	static_assert(board1x1::length == 1, "GameBoard Fail");
	static_assert(cmp<list1x1, board1x1::board>::value, "GameBoard Fail");

	typedef List<
	
			List< BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>,
			List< BoardCell<X, RIGHT, 1>,  BoardCell<A, UP, 1>>,
			List< BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>
		> list2x3;
	typedef GameBoard<list2x3> board2x3;
	static_assert(board2x3::width == 2, "GameBoard Fail");
	static_assert(board2x3::length == 3, "GameBoard Fail");
	static_assert(cmp<list2x3, board2x3::board>::value, "GameBoard Fail");
}

static void moveFieldsTest() {
	static_assert(Move<A, DOWN, 3>::type == A, "Move Fail");
	static_assert(Move<A, DOWN, 3>::direction == DOWN, "Move Fail");
	static_assert(Move<A, DOWN, 3>::amount == 3, "Move Fail");

	static_assert(Move<X, RIGHT, 25>::type == X, "Move Fail");
	static_assert(Move<X, RIGHT, 25>::direction == RIGHT, "Move Fail");
	static_assert(Move<X, RIGHT, 25>::amount == 25, "Move Fail");
}


static void checkWin_board_1x1_Test() {
	typedef GameBoard< List<
	        List < BoardCell< X , RIGHT , 1> >
	> > gameBoard;
	static_assert(CheckWin<gameBoard>::result, "Fail");
}

static void checkWin_board_3x3_Test() {
	typedef GameBoard< List<
	        List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0> >,
	        List < BoardCell< A , RIGHT , 2>,     BoardCell< A , LEFT , 2>,      BoardCell< EMPTY , RIGHT , 0> >,
	        List < BoardCell< X , RIGHT , 2>,     BoardCell< X , LEFT , 2>,      BoardCell< EMPTY , RIGHT , 0> >
	> > gameBoard;
	static_assert(CheckWin<gameBoard>::result, "Fail");
}

static void checkWin_noWin_board_3x3_Test() {
	typedef GameBoard< List<
	        List < BoardCell< X , RIGHT , 2>,     BoardCell< X , LEFT , 2>,      BoardCell<  A , DOWN , 2> >,
	        List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell<  A , DOWN , 2> >,
	        List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0> >
	> > gameBoard;
	static_assert(not CheckWin<gameBoard>::result, "Fail");
}

static void checkWin_noWin_board_1x6_Test() {
	typedef GameBoard< List<
	        List < BoardCell< X , RIGHT , 2>, BoardCell< X , LEFT , 2>, BoardCell< EMPTY , UP , 1000>, BoardCell< EMPTY , DOWN , 42>, BoardCell< EMPTY , LEFT , 333>, BoardCell<A , DOWN , 1> >
	> > gameBoard;
	static_assert(not CheckWin<gameBoard>::result, "Fail");
}

int main(){
	providedExample();
	listTest_Basic();
	listTest_Integration();
	conditionalTest();
	boardCellFieldsTest();
	gameBoardFieldsTest();
	moveFieldsTest();
	checkWin_board_1x1_Test();
	checkWin_board_3x3_Test();
	checkWin_noWin_board_3x3_Test();
	checkWin_noWin_board_1x6_Test();
	/*moveVehicle_game_Test();
	checkSolution_game_Test();

#ifdef TEST_COMPILATION_ERRORS
	moveCannotBeEmptyTest();
	moveVehicleErrorsTest();
#endif

#ifdef COME_TO_THE_LEV_SIDE
	getCoordinatesTest();
	gameBoardAtTest();
	takeDropListTest();
	sublistTest();
	concatTest();
	reverseTest();
	moveForwardBackwardTest();
	providedExampleStepByStep();
#endif
*/
    return 0;
}
