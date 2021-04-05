// lab1tnm096.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <deque>
#include <iterator>
#include <algorithm>
#include <cassert>

class Puzzle {
public:
	Puzzle();
	void print();
	bool loopcheck(std::deque<int> successor, std::deque<int> close);
	//std::deque<int> getSuccessors(std::deque<int> puzzle);

	std::deque<int> puzzle[2][2]{}; // random puzzle
	int random[3][3]{ {0, 8, 4},
						{6, 5, 1},
						{2, 3, 7} };

	std::deque<int> goal{ 1, 2, 3,
							4, 5, 6,
							7, 8, 0 }; // solution

	//open: add, remove 

	std::deque<int> open{};     // deque gives: Random access - constant O(1), this should also be sorted at all times.
	std::deque<int> close{};    // Insertion or removal of elements at the end or beginning - constant O(1)
};

Puzzle::Puzzle()
{
}

void Puzzle::print()
{
	// Print open list
	std::copy(open.begin(),
		open.end(),
		std::ostream_iterator<int>(std::cout, " "));
}

bool Puzzle::loopcheck(std::deque<int> successor, std::deque<int> close)
{
	while (!successor.empty()) {

	}
	return false;
}

template <size_t rows, size_t cols>
std::deque<int> getSuccessors(int(&puzzle)[rows][cols])
{
	std::deque<int> result{};
	//std::deque<int>::iterator where = std::find(puzzle.begin(), puzzle.end(), 0);
	int row{}, col{};

	for (int i{ 0 }; i < 3; i++) {
		for (int j{ 0 }; j < 3; j++) {
			if (puzzle[i][j] == 0) {
				row =  i;
				col = j;
			}
		}
	}

	struct {
		int dx;
		int dy;
	} directions[] = { {-1,0,},{0,-1},{0,1},{1,0} }; // left, bottom, right, 

	for (int i = 0; i < sizeof(directions); i++) {
		if( row+directions[i].dx >= 0 && row + directions[i].dx <= 3 && col + directions[i].dy >= 0 && col + directions[i].dy <= 3)
			result.push_front(puzzle[row+directions[i].dx][col + directions[i].dy]);
	}
	return result;
}

int main()
{
	std::cout << "Lab 1: 8-puzzle\n";
	Puzzle p1;

	int random[3][3]{ {0, 8, 4},
					  {6, 5, 1},
					  {2, 3, 7} };

	p1.open = getSuccessors(random);

	p1.print();
	

	//getSuccessors(p1.puzzle);

	// Loop-checker using close-list, check if successor is in closed list!

	// Calculate f(s)

}