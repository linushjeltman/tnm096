#include <cstddef>
#include <iostream>     // std::cout
#include <algorithm>    // std::swap
#include <utility>
#include <vector>       // std::vector
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;
//#define N 3

typedef std::deque<int> dint;
typedef vector<int> vec;

//  tree nodes
struct Node
{
	typedef std::shared_ptr<Node> sNode;
private:
	//std::deque<int, dint> parent;
	// stores the parent node of the chosen successor
	vector<int> state;

	int f{}; // from start to current node (cost)
	int depth{}; // f(s)=c(s)+h(s)
	int h{}; // number of misplaced tiles (heuristic)

	Node* parent;

	void swapZero(int index, int zero);
public:

	Node(vec _state);
	Node(const Node& rhs);
	Node* generateChild(int index, int zero);

	void calculateHeuristic(const vec& goal);
	void calculatePath(const Node& parent);
	void setParent(Node* rhs);
	void calculateF();

	int getF() const;
	void printPuzzle();
	void printPath(int& counter);
	vec getState() const;

};

Node::Node(vec _state) {
	state = _state;
	parent = nullptr;
	depth = 0;
	h = 0;
}
Node::Node(const Node& rhs) {
	this->state = rhs.state;
	this->parent = rhs.parent;
	this->depth = 0;
	this->h = 0;
	this->f = 0;
}

Node* Node::generateChild(int index, int zero) {
	Node* newNode = new Node(*this);
	newNode->swapZero(index, zero);
	return newNode;
}

// Function to calculate the number of misplaced tiles
// ie. number of non-blank tiles not in their goal position
void Node::calculateHeuristic(const vec& goal)
{
	int temp{};
	for (size_t i{ 0 }; i < 9; i++)
	{
		if (this->getState()[i] != goal[i]) {
			temp++;
		}
	}
	this->h = temp;
}

void Node::calculatePath(const Node& parent)
{
	this->depth = parent.depth + 1;
}

void Node::setParent(Node* rhs) {
	this->parent = rhs;
}

void Node::calculateF() {
	this->f = this->depth + this->h;
}


int Node::getF() const {
	return this->f;
}

vec Node::getState() const { return this->state; }
int findZero(vec puzzle) {
	for (int i{ 0 }; i < 9; i++) {
		if (puzzle.at(i) == 0) return i;
	}
	return 0;
}

void Node::swapZero(int index, int zero) {
	std::swap(this->state[index], this->state[zero]);
	//int temp = vec.getStateElem().at(index);
	//state.getStateElem().at(index) = state.getStateElem().at(zero);
	//state.getStateElem().at(zero) = temp;
}

//char Node::getDirection() {
//	Node temp = *this;
//	int childIndex{ findZero(temp.getState().getStateElem()) }, parentIndex{ findZero(temp.getparent()->getState().getStateElem()) };
//	//cout << "Child index: " << childIndex << " Parent index: " << parentIndex << endl << "Diff: " << childIndex - parentIndex << endl;
//
//	switch (childIndex - parentIndex) {
//	case(-3):
//		return 'U';
//	case(-1):
//		return 'L';
//	case(1):
//		return 'R';
//	case(3):
//		return 'D';
//	default:
//		return 'X';
//	}
//};

//dint findSucc(Node& state, int zeroIndex) {
//	// At most 4 successors
//	dint succ{};
//	switch (zeroIndex)
//	{
//	case 0:
//		succ.push_back(state.getState().getStateElem().at(1));
//		succ.push_back(state.getState().getStateElem().at(3));
//		break;
//	case 1:
//		succ.push_back(state.getState().getStateElem().at(0));
//		succ.push_back(state.getState().getStateElem().at(2));
//		succ.push_back(state.getState().getStateElem().at(4));
//		break;
//	case 2:
//		succ.push_back(state.getState().getStateElem().at(1));
//		succ.push_back(state.getState().getStateElem().at(5));
//		break;
//	case 3:
//		succ.push_back(state.getState().getStateElem().at(0));
//		succ.push_back(state.getState().getStateElem().at(4));
//		succ.push_back(state.getState().getStateElem().at(6));
//		break;
//	case 4:
//		succ.push_back(state.getState().getStateElem().at(1));
//		succ.push_back(state.getState().getStateElem().at(3));
//		succ.push_back(state.getState().getStateElem().at(5));
//		succ.push_back(state.getState().getStateElem().at(7));
//		break;
//	case 5:
//		succ.push_back(state.getState().getStateElem().at(2));
//		succ.push_back(state.getState().getStateElem().at(4));
//		succ.push_back(state.getState().getStateElem().at(8));
//		break;
//	case 6:
//		succ.push_back(state.getState().getStateElem().at(3));
//		succ.push_back(state.getState().getStateElem().at(7));
//		break;
//	case 7:
//		succ.push_back(state.getState().getStateElem().at(4));
//		succ.push_back(state.getState().getStateElem().at(6));
//		succ.push_back(state.getState().getStateElem().at(8));
//		break;
//	case 8:
//		succ.push_back(state.getState().getStateElem().at(6));
//		succ.push_back(state.getState().getStateElem().at(7));
//		break;
//	default:
//		break;
//	}
//	return succ;
//}
dint findSuccIndex(int zeroIndex) {
	// At most 4 successors
	dint succ{};
	switch (zeroIndex)
	{
	case 0:
		succ.push_back(1);
		succ.push_back(3);
		break;
	case 1:
		succ.push_back(0);
		succ.push_back(2);
		succ.push_back(4);
		break;
	case 2:
		succ.push_back(1);
		succ.push_back(5);
		break;
	case 3:
		succ.push_back(0);
		succ.push_back(4);
		succ.push_back(6);
		break;
	case 4:
		succ.push_back(1);
		succ.push_back(3);
		succ.push_back(5);
		succ.push_back(7);
		break;
	case 5:
		succ.push_back(2);
		succ.push_back(4);
		succ.push_back(8);
		break;
	case 6:
		succ.push_back(3);
		succ.push_back(7);
		break;
	case 7:
		succ.push_back(4);
		succ.push_back(6);
		succ.push_back(8);
		break;
	case 8:
		succ.push_back(5);
		succ.push_back(7);
		break;
	default:
		break;
	}
	return succ;
}

size_t hashing(const vec& puzzles) {
	string result;
	for (auto&& i : puzzles) {
		string tmp = to_string(i);
		result += tmp;
	}
	return hash<string>{}(result);
}

struct Comparator {
	bool operator()(Node* lhs, Node* rhs) {
		return lhs->getF() > rhs->getF();
	}
};

void Node::printPuzzle() {
	for (int i{ 0 }; i < 9; i += 3) {
		std::cout << state[i] << " " << state[i + 1] << " " << state[i + 2] << " \n";
	}
}

void Node::printPath(int& counter)
{
	if (this->parent == nullptr) {
		this->printPuzzle();
		std::cout << std::endl;
		return;
	}
	counter++;
	this->parent->printPath(counter);
	this->printPuzzle();
	std::cout << std::endl;
}

int main()
{
	// Initial configuration, 0 is for empty tile.
	//State initial(dint{ 4, 1, 3, 7, 2, 6, 0, 5, 8 }); // Own test 
	//State initial(dint{ 4, 1, 3, 7, 2, 6, 0, 5, 8 }); // easy
	vec initial{ 7, 2, 4, 5, 0, 6, 8, 3, 1 }; // medium
	//State initial(dint{ 6, 4, 7, 8, 5, 0, 3, 2, 1 }); // hard 
	//State initial(dint{ 8, 6, 7, 2, 5, 4, 3, 0, 1 }); // expert

	// Solvable Final puzzle
	const vec goal{ 1, 2, 3, 4, 5, 6, 7, 8, 0 };

	//Node* start{new Node(initial, nullptr, 0)};
	Node* start = new Node(initial);

	priority_queue<Node*, std::vector<Node*>, Comparator> openList; // Open list
	unordered_map<size_t, vec> closedList; // Closed list

	start->calculateHeuristic(goal);
	start->calculateF();
	openList.push(start);

	while (!openList.empty())
	{
		Node* min = openList.top(); // priority queue with comparator so .top() gives element with lowest f
		openList.pop(); // remove min from open list

		size_t id{ hashing(min->getState()) }; // give min an id by hashing it
		closedList[id] = min->getState(); // put min in closed list

		int zero = findZero(min->getState()); // find index for movable

		dint succIndex = findSuccIndex(zero); // get possible moves
							  
		if (min->getState() == goal) {	//Check if solved
			int counter{};
			std::cout << "Puzzle is solved! \n";
			min->printPath(counter);
			std::cout << "Solved in: " << counter << " steps! :)\n";
			return 0;
		};

		for (size_t states{ 0 }; states < succIndex.size(); states++) {
			//Node* child{new Node(min->getState(), nullptr, min->getDepth())}; // Create child, copy of min.
			Node* child = min->generateChild(succIndex.at(states), zero);

			//child->setparent(min); // set min as parent
			child->setParent(min);
			child->calculateHeuristic(goal); // calc heuristic score
			child->calculatePath(*min);
			child->calculateF();

			size_t childId{ hashing(child->getState()) };
			if (closedList.find(childId) == closedList.end()) {	// insert to open list if it doesn't exist in closed list
				openList.push(child); // add child to open list
				closedList[childId] = child->getState(); // add child to closedList aswell.
			}
		}
	}

}

/*
1. Pussel
2. Var �r start-noden
3. Successors
4. Kolla s� att de inte finns i closed
5. R�kna ut f(s)
6. L�gg till i open-list i storleksordning beroende p� f
7. Flytta start till closed
8. Ta minsta f fr�n open och expandera nod, steg 3

*/

//initial_matrix = [[4, 1, 3], [7, 2, 6], [0, 5, 8]] ##### easy with 6 moves {4, 1, 3, 7, 2, 6, 0, 5, 8}
//initial_matrix = [[7, 2, 4], [5, 0, 6], [8, 3, 1]] ##### medium 20 moves {7, 2, 4, 5, 0, 6, 8, 3, 1}
//initial_matrix = [[6, 4, 7], [8, 5, 0], [3, 2, 1]] ##### difficult 31 moves {6, 4, 7, 8, 5, 0, 3, 2, 1}
//This one will also be solved with 31 moves(most difficult) :  [[8, 6, 7], [2, 5, 4], [3, 0, 1]] {8, 6, 7, 2, 5, 4, 3, 0, 1}

