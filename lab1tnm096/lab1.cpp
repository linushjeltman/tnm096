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

struct State {
private:
	dint _state;

public:
    State(dint  arr) : _state(std::move(arr)) {};

	dint& getStateElem() {
		return _state;
	}

	void print() {
		for (int i{ 0 }; i < 9; i++) {
			std::cout << getStateElem().at(i) << " ";
		}
	}

};


//  tree nodes
struct Node
{
	typedef std::shared_ptr<Node> sNode;
private:
	//std::deque<int, dint> parent;
	// stores the parent node of the chosen successor
	State state;
	sNode parent;
	Node* parent1;
	int depth;
	// f(s)=c(s)+h(s)
	// number of misplaced tiles (hearistic)
	int h{};

	// from start to current node (cost)
	int f{};

public:
	string moves;

	Node(State  state, sNode Parent, int depth = 0)
		: state(std::move(state))
		, depth(depth)
	{
		parent = std::move(Parent);
		parent1 = nullptr;
		h = 0;
		f = 0;
	}

//    Node(State state1) : state(std::move(state1)) {
//	    parent1 = nullptr;
//	    depth = 0;
//	    h = 0;
//	    f = 0;
//	}

	Node(const Node& newNode) : state(newNode.state), parent(newNode.parent), parent1(nullptr), depth(newNode.depth), h(0), f(0) {}

	State& getState() { return state; }

	void incrementDepth() { depth++; }
	const int& getDepth() const { return depth; }

	void setParent(Node *rhs) {
		parent1 = rhs;
	}
	sNode* getParent() { return &parent; };
	Node* getParent1() { return parent1; };

	string getPath() const { return moves; };

	void swapZero(int index, int zero) {
		int temp = state.getStateElem().at(index);
		state.getStateElem().at(index) = state.getStateElem().at(zero);
		state.getStateElem().at(zero) = temp;
	}

	void incHeuristic() { setHeuristic(h + 1); }
	void setHeuristic(int value) { h = value; }
	int getHeuristic() const { return h; }

	void setF() { f = depth + h; /*cout << depth << " " <<h << endl;*/ }
	const int& getF() const { return f; }

	void printPuzzle();
	void printPath(int& counter);
	void addMove(char& direction);
	char getDirection();
};

int findZero(dint puzzle) {
	for (int i{ 0 }; i < 9; i++) {
		if (puzzle.at(i) == 0) return i;
	}
	return 0;
}

char Node::getDirection() {
	Node temp = *this;
	int childIndex{ findZero(temp.getState().getStateElem()) }, parentIndex{ findZero(temp.getParent1()->getState().getStateElem()) };
	cout << "Child index: " << childIndex << " Parent index: " << parentIndex << endl << "Diff: " << childIndex-parentIndex << endl;

	switch (childIndex - parentIndex) {
	case(-3):
		return 'U';
	case(-1):
		return 'L';
	case(1):
		return 'R';
	case(3):
		return 'D';
	default:
		return 'X';
	}
};

dint findSucc(Node& state, int zeroIndex) {
	// At most 4 successors
	dint succ{};
	switch (zeroIndex)
	{
	case 0:
		succ.push_back(state.getState().getStateElem().at(1));
		succ.push_back(state.getState().getStateElem().at(3));
		break;
	case 1:
		succ.push_back(state.getState().getStateElem().at(0));
		succ.push_back(state.getState().getStateElem().at(2));
		succ.push_back(state.getState().getStateElem().at(4));
		break;
	case 2:
		succ.push_back(state.getState().getStateElem().at(1));
		succ.push_back(state.getState().getStateElem().at(5));
		break;
	case 3:
		succ.push_back(state.getState().getStateElem().at(0));
		succ.push_back(state.getState().getStateElem().at(4));
		succ.push_back(state.getState().getStateElem().at(6));
		break;
	case 4:
		succ.push_back(state.getState().getStateElem().at(1));
		succ.push_back(state.getState().getStateElem().at(3));
		succ.push_back(state.getState().getStateElem().at(5));
		succ.push_back(state.getState().getStateElem().at(7));
		break;
	case 5:
		succ.push_back(state.getState().getStateElem().at(2));
		succ.push_back(state.getState().getStateElem().at(4));
		succ.push_back(state.getState().getStateElem().at(8));
		break;
	case 6:
		succ.push_back(state.getState().getStateElem().at(3));
		succ.push_back(state.getState().getStateElem().at(7));
		break;
	case 7:
		succ.push_back(state.getState().getStateElem().at(4));
		succ.push_back(state.getState().getStateElem().at(6));
		succ.push_back(state.getState().getStateElem().at(8));
		break;
	case 8:
		succ.push_back(state.getState().getStateElem().at(6));
		succ.push_back(state.getState().getStateElem().at(7));
		break;
	default:
		break;
	}
	return succ;
}
dint findSuccIndex(Node& state, int zeroIndex) {
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
		succ.push_back(6);
		succ.push_back(7);
		break;
	default:
		break;
	}
	return succ;
}

// Function to calculate the number of misplaced tiles
// ie. number of non-blank tiles not in their goal position
void calculateCost(Node& d)
{
	d.setHeuristic(0);
	int temp{};
	for (size_t i{ 0 }; i < 9; i++)
	{
		if (i != 0 && i + 1 != d.getState().getStateElem().at(i)) {
			//d.incHeuristic();
			temp++;
		}
	}
	d.setHeuristic(temp);
	d.setF();
}

size_t hashing(const dint& puzzles) {
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
		cout << state.getStateElem().at(i) << " " << state.getStateElem().at(i + 1) << " " << state.getStateElem().at(i + 2) << " \n";
	}
}

void Node::printPath(int& counter)
{
	counter++;
	if (this->parent1 == nullptr) {
		this->printPuzzle();
		std::cout << std::endl;
		return;
	}
	this->parent1->printPath(counter);
	this->printPuzzle();
	std::cout << std::endl;
}

void Node::addMove(char& direction)
{
	string temp{ direction };
	this->moves += temp;
}

int main()
{
	// Initial configuration, 0 is for empty tile.
	//State initial(dint{ 4, 1, 3, 7, 2, 6, 0, 5, 8 }); // Own test 
	//State initial(dint{ 4, 1, 3, 7, 2, 6, 0, 5, 8 }); // easy
	State initial(dint{ 7, 2, 4, 5, 0, 6, 8, 3, 1 }); // medium
	//State initial(dint{ 6, 4, 7, 8, 5, 0, 3, 2, 1 }); // hard 
	//State initial(dint{ 8, 6, 7, 2, 5, 4, 3, 0, 1 }); // expert

	// Solvable Final puzzle
	State goal(dint{ 1, 2, 3, 4, 5, 6, 7, 8, 0 });

	Node* start{new Node(initial, 0, 0)};
//	Node* start{new Node(initial)};

	unsigned pathTracer{ 0 };
	string Path{};

	priority_queue<Node*, std::vector<Node*>, Comparator> openList; // Open list
	unordered_map<size_t, dint> closedList; // Closed list

	calculateCost(*start);
	openList.push(start);

	while (!openList.empty())
	{
		Node* min{ openList.top() }; // priority queue with comparator so .top() gives element with lowest f
		openList.pop(); // remove min from open list

		size_t id{ hashing(min->getState().getStateElem()) }; // give min an id by hashing it
		closedList[id] = min->getState().getStateElem(); // put min in closed list

		//Check if solved
		if (min->getState().getStateElem() == goal.getStateElem()) {
			int counter{};
			cout << "Puzzle is solved! \n";
			//min->printPath(counter);
			cout << "Solved in: " << counter-1 << " steps! :)\n";
			return 0;
		};

		// find start node
		int zero = findZero(min->getState().getStateElem()); // find index for movable

		// successors
		dint succIndex = findSuccIndex(*min, zero); // get possible moves

		// move zero and create new state
		State tempState = min->getState().getStateElem(); // save current state

		shared_ptr<Node> minPointer{ min };

		int lowest = 10000;
		int counter{};

		for (size_t states{ 0 }; states < succIndex.size(); states++) {
			Node* child{new Node(min->getState(), nullptr, min->getDepth()+1)}; // Create child, copy of min.
			child->swapZero(succIndex.at(states), zero);  // Move zero to possible move
			child->incrementDepth(); // inrcrease the depth since this is a child node
			calculateCost(*child); // calc heuristic score

			size_t childId{ hashing(child->getState().getStateElem()) };
			if (closedList.find(childId) == closedList.end()) {	// insert to open list if it doesn't exist in closed list
                child->setParent(min); // set min as parent
				openList.push(child); // add child to open list
				//closedList[childId] = child->getState().getStateElem(); // add child to closedList aswell.
			}
			counter++;
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

