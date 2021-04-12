// lab1tnm096.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Puzzles to test
/*
##### initial_matrix =
[[4, 1, 3], [7, 2, 6], [0, 5, 8]]
##### easy with 6 moves initial_matrix =
[[7, 2, 4], [5, 0, 6], [8, 3, 1]]
##### medium 20 moves initial_matrix =
[[6, 4, 7], [8, 5, 0], [3, 2, 1]]
##### difficult 31 moves  This one will also be solved with 31 moves (most difficult):
[[8, 6, 7], [2, 5, 4], [3, 0, 1]]
*/

#include <iostream>
#include <deque>
#include <iterator>
#include <algorithm>
#include <cassert>
#include <set>

//class State {
//public:
//	/*Puzzle();
//	void print();
//	void loopcheck(std::deque<int>& successor, std::deque<int>& close);
//	int calcF();
//	//std::deque<int> getSuccessors(std::deque<int> puzzle);
//	int random[3][3]{ {0, 8, 4},
//					  {6, 5, 1},
//					  {2, 3, 7} };
//
//	int goal[3][3]{ {1, 2, 3},
//					{4, 5, 6},
//					{7, 8, 0} };*/
//	// positioner på tiles
//	// chilren?
//
//	int state[3][3]{};
//	int path_cost;
//	State* parent;
//
//	State();//constructor
//};
//
//State::State()
//{
//	//initialize the state
//	int state[3][3]{ {0, 8, 4},
//					  {6, 5, 1},
//					  {2, 3, 7}};
//	//initialize the path cost
//	path_cost = 0;
//	//initialize the parent
//	parent = NULL;
//}

class Node {
public:
	// Puzzle
	//Node() : path(0), open(0), close(0), cost(0), heuristic(0) {};
	//Node* parent;

	int mat[3][3]{};
	struct Zero {
		int x{}, y{};
	};

	// Path
	std::deque<int> path;

	//open: add, remove 
	//std::set<int, Node> open;     // deque gives: Random access - constant O(1), this should also be sorted at all times.
	std::deque<int> close;    // Insertion or removal of elements at the end or beginning - constant O(1)

	int cost; // f(s) = c(s) + h(s)
	int heuristic;
};



//Puzzle::Puzzle()
//{
//}
//
//void Puzzle::print()
//{
//	// Print open list
//	std::cout << "Successors: ";
//	std::copy(open.begin(),
//		open.end(),
//		std::ostream_iterator<int>(std::cout, " "));
//	std::cout << std::endl;
//}
//
//template <size_t rows, size_t cols>
//void printMatrix(int(&puzzle)[rows][cols])
//{
//	std::cout << "\n";
//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 3; j++) {
//			std::cout << puzzle[i][j] << " ";
//		}
//		std::cout << "\n";
//	}
//	std::cout << "----------" << "\n";
//}
//
//void Puzzle::loopcheck(std::deque<int>& successor, std::deque<int>& close)
//{
//	for (int const& i : successor) {
//		for (int const& j : close) {
//			if (successor.at(i) != close.at(j)) {
//				close.push_front(successor.at(i));
//				break;
//			}
//		}
//	}
//}
//
//int Puzzle::calcF()
//{
//	// c(s)
//	std::cout << "c(s) = " << cost << std::endl;
//	// h(s), h1 = misplaced tiles
//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 3; j++) {
//			if (random[i][j] != goal[i][j] && random[i][j] != 0) {
//				heuristic++;
//			}
//		}
//	}
//	std::cout << "h(s) = " << heuristic << std::endl;
//	std::cout << "f(s) = " << cost + heuristic << std::endl;
//	return cost + heuristic;
//}
//

template <size_t rows, size_t cols>
std::deque<int> getSuccessors(int(&puzzle)[rows][cols])
{
	std::deque<int> result{};
	int row{}, col{};

	for (int i{ 0 }; i < 3; i++) {
		for (int j{ 0 }; j < 3; j++) {
			if (puzzle[i][j] == 0) {
				row = i;
				col = j;
			}
		}
	}

	struct {
		int dx;
		int dy;
	} directions[] = { {-1,0,},{0,-1},{0,1},{1,0} }; // left, bottom, right, 

	for (int i = 0; i < sizeof(directions); i++) {
		if (row + directions[i].dx >= 0 && row + directions[i].dx <= 3 && col + directions[i].dy >= 0 && col + directions[i].dy <= 3)
			result.push_front(puzzle[row + directions[i].dx][col + directions[i].dy]);
	}
	return result;
}

template <size_t rows, size_t cols>
void printMatrix(int(&puzzle)[rows][cols])
{
	std::cout << "\n";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << puzzle[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "----------" << "\n";
}

int main()
{
	std::cout << "Lab 1: 8-puzzle\n";

	int random[3][3]{	{4, 1, 3},
						{7, 2, 6},
						{0, 5, 8} };

	int goal[3][3]{ {1, 2, 3},
					{4, 5, 6},
					{7, 8, 0} };

	printMatrix(random);

	std::deque<int> succ = getSuccessors(random);

	//Node* start{ new Node };
	std::cout << "Hej";
	//Test

	//std::set<int> s = { 7,5,1,3,5,9 }; // <f(s), state> 

	//for (auto it{ s.begin() }; it != s.end(); ++it) {
	//	auto&& element{ *it };
	//	std::cout << element << std::endl;
	//}

	/*while (true) {
		p1.open = getSuccessors(p1.random);
		p1.cost++;
		p1.print();
		p1.calcF();
		printMatrix(p1.random);

		break;
	}*/

	//getSuccessors(p1.puzzle);

	// Loop-checker using close-list, check if successor is in closed list!

	// Calculate f(s)

}


/*
1. Pussel
2. Var är start-noden
3. Successors
4. Kolla så att de inte finns i closed
5. Räkna ut f(s)
6. Lägg till i open-list i storleksordning beroende på f
7. Flytta start till closed
8. Ta minsta f från open och expandera nod, steg 3

*/