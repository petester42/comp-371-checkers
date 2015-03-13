#pragma once
#include <bitset>
#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

struct element
{
	bitset<64> black;
	bitset<64> white;
	bitset<64> empty;
	int depth;
	int score;
	element* parent; 
	vector<element*> children;
};


class stateSpace
{
private:
	static const int BIT_DEPTH = 64;
	int nodeCount;
	element data;
	element* currentNode;
	element* root;
	queue<element*> nextPos;
	void writeNode(ostream& outs, element node);
	void output(ostream& outs, bitset<64> board);
	void getNodesWithParent(int level, vector<vector<element*>> &nodes);


public:
	stateSpace();
	stateSpace(bitset<BIT_DEPTH> newBlack, bitset<BIT_DEPTH> newWhite);
	stateSpace(const stateSpace& s);
	~stateSpace();
	stateSpace& operator= (const stateSpace& g);
	bitset<BIT_DEPTH> getBlackBoard();
	bitset<BIT_DEPTH> getWhiteBoard();
	void setBlackBoard(bitset<BIT_DEPTH> Board);
	void setWhiteBoard(bitset<BIT_DEPTH> Board);
	void addChild(bitset<BIT_DEPTH> black, bitset<BIT_DEPTH> white);
	void addChild(element node);
	void addChildren(vector<element*> nodes);
	element getChild(int n);
	void getChildren(vector<element>& nodes);
	bool hasChildren();
	int getchildCount();
	bool hasNext();
	void nextNode();
	void outputCurrentNode(ostream& outs);
	 //New functions 
	element getCurrentChild();
	int getDepth();
	int getScore();
	void setScore(int newScore);
	//End
	void getNodes(int level, vector<element>& nodes);
	void getNodes(int level, vector<vector<element*>> &nodes);
	element locateParent(int level, element node, int first, int second);
	friend ostream& operator << (ostream& outs, stateSpace& s);

};