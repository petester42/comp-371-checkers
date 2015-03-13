/**
 *======================================================================
 *  Student#1: Angelo Pulcini		Student ID: 3946703
 *  Student#2: Jonathan Evans		Student ID: 5201713
 *  Course: COMP 472                Section:  Lec F
 *  Instructor: Sabine Bergler
 *  Assignment #2
 *  
 *  Description:
 *  This is the implementation file for the stateSpace class.
 *  
 *======================================================================
 */
#include <queue>
#include "stateSpace.h"


stateSpace::stateSpace()
{
	data.depth = 0;
	data.score = 0;
	data.parent = 0;
	currentNode = &data;
	root = &data;
	nodeCount = 0;
}


stateSpace::stateSpace(bitset<BIT_DEPTH> newBlack, bitset<BIT_DEPTH> newWhite)
{
	bitset<64> temp;
	data.black = newBlack;
	data.white = newWhite;
	data.depth = 0;
	data.score = 0;
	data.parent = 0;
	currentNode = &data;
	root = &data;
	nodeCount = data.depth + 1;

	if((currentNode->black != temp) && (currentNode->white != temp))
	{	
		nextPos.push(currentNode);
	}
}


stateSpace::stateSpace(const stateSpace& s)
{
	data.black = s.data.black;
	data.white = s.data.white;
	data.empty = s.data.empty;
	data.depth = s.data.depth;
	data.score = s.data.score;
	data.parent = s.data.parent;
	currentNode = s.currentNode;
	root = s.root;

	data.children.resize(s.data.children.size());
	for(vector<element*>::size_type counter = 0; counter != s.data.children.size(); ++counter)
		data.children.at(counter) = s.data.children.at(counter);
}


/*
We're destroying the entire structure in this function.  We need to destroy all of the children at all of the levels
in order to properly release memory.
*/
stateSpace::~stateSpace()
{
	data.parent = 0;
	
	for(vector<element*>::size_type counter = 0; counter != data.children.size(); ++counter)
	{
		if(data.children.at(counter) != 0)
			data.children.at(counter) = 0;
	}
}


stateSpace& stateSpace::operator= (const stateSpace& s)
{
	if(this != &s)
	{
		data.black = s.data.black;
		data.white = s.data.white;
		data.empty = s.data.empty;
		data.depth = s.data.depth;
		data.score = s.data.score;
		data.parent = s.data.parent;
		currentNode = s.currentNode;
		root = s.root;

		data.children.resize(s.data.children.size());
		for(vector<element*>::size_type counter = 0; counter != s.data.children.size(); ++counter)
			data.children.at(counter) = s.data.children.at(counter);
	}
	return *this;
}


bitset<stateSpace::BIT_DEPTH> stateSpace::getBlackBoard()
{
	bitset<BIT_DEPTH> temp;
	temp = currentNode->black;

	return temp;
}


bitset<stateSpace::BIT_DEPTH> stateSpace::getWhiteBoard()
{
	bitset<BIT_DEPTH> temp;
	temp = currentNode->white;

	return temp;
}


void stateSpace::setBlackBoard(bitset<BIT_DEPTH> Board)
{
	data.black = Board;
}


void stateSpace::setWhiteBoard(bitset<BIT_DEPTH> Board)
{
	data.white = Board;
}


void stateSpace::addChild(bitset<BIT_DEPTH> black, bitset<BIT_DEPTH> white)
{
	element* temp = new element();

	if((root->black == temp->empty) && (root->white == temp->empty))
	{
		currentNode->black = black;
		currentNode->white = white;
		currentNode->depth = 0;
		currentNode->score = 0;
		nodeCount = currentNode->depth + 1;
		nextPos.push(currentNode);	
	}
	else
	{
		temp->black = black;
		temp->white = white;
		temp->depth = currentNode->depth + 1;
		temp->score = 0;
		temp->parent = currentNode;
		nodeCount = temp->depth + 1;
		nextPos.push(temp);
		currentNode->children.push_back(temp);//data.children.push_back(tmpPointer); 
	}
}


void stateSpace::addChild(element node)
{
	element* temp = new element();

	if((root->black == temp->empty) && (root->white == temp->empty))
	{
		currentNode->black = node.black;
		currentNode->white = node.white;
		currentNode->depth = 0;
		currentNode->score = node.score;
		nodeCount = currentNode->depth + 1; 
		nextPos.push(currentNode);	
	}
	else
	{
		temp->black = node.black;
		temp->white = node.white;
		temp->depth = currentNode->depth + 1;
		temp->score = node.score;
		temp->parent = currentNode;
		nodeCount = temp->depth + 1;
		nextPos.push(temp);
		currentNode->children.push_back(temp);//tmpPointer);
	}
}


void stateSpace::addChildren(vector<element*> nodes)
{
	for(vector<element>::size_type counter = 0; counter != nodes.size(); ++counter)
	{
		element temp;
		temp.black = nodes.at(counter)->black;
		temp.white = nodes.at(counter)->white;
		temp.score = nodes.at(counter)->score;

		addChild(temp);
	}
}


element stateSpace::getChild(int n)
{
	element temp;
	temp.black = currentNode->children.at(n)->black;
	temp.white = currentNode->children.at(n)->white;
	temp.depth = currentNode->children.at(n)->depth;
	temp.score = currentNode->children.at(n)->score;
	temp.parent = 0;//data.children.at(n)->parent;

	return temp;
}


void stateSpace::getChildren(vector<element>& nodes)
{
	for(vector<element*>::size_type counter = 0; counter != currentNode->children.size(); ++counter)
	{
		element temp;
		temp.black = currentNode->children.at(counter)->black;
		temp.white = currentNode->children.at(counter)->white;
		temp.depth = 0;
		temp.score = currentNode->children.at(counter)->score;
		temp.parent = 0;

		nodes.push_back(temp);
	}
}


bool stateSpace::hasChildren()
{
	if(currentNode->children.size() == 0)
		return false;
	else
		return true;
}


bool stateSpace::hasNext()
{
	return (!nextPos.empty());
}


int stateSpace::getchildCount()
{
	return currentNode->children.size();
}


void stateSpace::nextNode()
{
	currentNode = nextPos.front();
	nextPos.pop();
}


void stateSpace::outputCurrentNode(ostream& outs)
{
	element temp;

	temp.black = currentNode->black;
	temp.white = currentNode->white;
	temp.depth = currentNode->depth;
	temp.score = currentNode->score;
	temp.parent = currentNode->parent;
	
	writeNode(outs, temp);
}


element stateSpace::getCurrentChild()
{
	element temp;

	temp.black = currentNode->black;
	temp.white = currentNode->white;
	temp.depth = currentNode->depth;
	temp.score = currentNode->score;
	temp.parent = 0;

	return temp;
}


int stateSpace::getDepth()
{
	return currentNode->depth;
}


int stateSpace::getScore()
{
	return currentNode->score;
}


void stateSpace::setScore(int newScore)
{
	currentNode->score = newScore;
}


void stateSpace::getNodes(int level, vector<element>& nodes)
{
	queue<element*> toBeProcessed;
	element* current;

	current = &data;
	toBeProcessed.push(current);
	
	while(!toBeProcessed.empty())
	{
		element* temp1 = toBeProcessed.front(); //Pop off queue
		toBeProcessed.pop();
		
		if(temp1->depth == level)
		{
			element temp;

			temp.black = temp1->black; //Process boards
			temp.white = temp1->white;
			temp.depth = temp1->depth;
			temp.score = temp1->score;
			temp.parent = 0;
		
			nodes.push_back(temp);
		}

		for(vector<element*>::size_type count = 0; count != temp1->children.size(); ++count) //Place children on queue
		{
			element* temp2;
			temp2 = temp1->children.at(count);
			
			toBeProcessed.push(temp2);
		} 
	}
}


void stateSpace::getNodes(int level, vector<vector<element*>> &nodes)
{
	queue<element*> toBeProcessed;
	element* current;
	element* tracker;
	vector<element*> tempVec;

	current = root;
	tracker = current;
	toBeProcessed.push(current);
	
	while(!toBeProcessed.empty())
	{
		element* temp1 = toBeProcessed.front(); //Pop off queue
		toBeProcessed.pop();
		
		if(temp1->depth == level)
		{
			if(temp1->parent != tracker)
			{
				if(!tempVec.empty())
					nodes.push_back(tempVec);
				
				tempVec.clear();
				tracker = temp1->parent;
			}

			element temp;
			element* tmpPtr = new element();

			tmpPtr->black = temp1->black; //Process boards
			tmpPtr->white = temp1->white;
			tmpPtr->depth = temp1->depth;
			tmpPtr->score = temp1->score;
			tmpPtr->parent = 0;
			
			tempVec.push_back(tmpPtr);
			
			if(level == 0)
				nodes.push_back(tempVec);
		}

		for(vector<element*>::size_type count = 0; count != temp1->children.size(); ++count) //Place children on queue
		{
			element* temp2;
			temp2 = temp1->children.at(count);
			
			toBeProcessed.push(temp2);
		} 
	}
}


void stateSpace::getNodesWithParent(int level, vector<vector<element*>>& nodes)
{
	queue<element*> toBeProcessed;
	element* current;
	element* tracker;
	vector<element*> tempVec;

	current = root;
	tracker = current;
	toBeProcessed.push(current);
	
	while(!toBeProcessed.empty())
	{
		element* temp1 = toBeProcessed.front(); //Pop off queue
		toBeProcessed.pop();
		
		if(temp1->depth == level)
		{
			if(temp1->parent != tracker)
			{
				if(!tempVec.empty())
					nodes.push_back(tempVec);
				
				tempVec.clear();
				tracker = temp1->parent;
			}

			element temp;
			element* tmpPtr = new element();

			tmpPtr->black = temp1->black; //Process boards
			tmpPtr->white = temp1->white;
			tmpPtr->depth = temp1->depth;
			tmpPtr->score = temp1->score;
			tmpPtr->parent = temp1->parent;
			
			tempVec.push_back(tmpPtr);

			if(level == 0)
				nodes.push_back(tempVec);
		}

		for(vector<element*>::size_type count = 0; count != temp1->children.size(); ++count) //Place children on queue
		{
			element* temp2;
			temp2 = temp1->children.at(count);
			
			toBeProcessed.push(temp2);
		} 
	}
}


element stateSpace::locateParent(int level, element node, int first, int second)
{
	element* backTracker;

	if(level != 0)
	{
		vector<vector<element*>> result;
		vector<element>::size_type counter;
		vector<element>::size_type innerCount;

		getNodesWithParent(level, result);
		
		backTracker = result.at(first).at(second);

		while(backTracker->depth != 1)
		{
			backTracker = backTracker->parent;
		}
	}
	else
	{
		backTracker = root;
	}

	element temp;
	temp.black = backTracker->black;
	temp.white = backTracker->white;
	temp.score = backTracker->score;
	temp.depth = backTracker->depth;
	temp.parent = 0;
	return temp;
}


ostream& operator<< (ostream& outs, stateSpace& s)
{

	queue<element*> toBeProcessed;
	element* current;

	current = &s.data;
	toBeProcessed.push(current);
	
	while(!toBeProcessed.empty())
	{
		element* temp1 = toBeProcessed.front(); //Pop off queue
		toBeProcessed.pop();
		element temp;

		temp.black = temp1->black; //Process boards
		temp.white = temp1->white;
		temp.depth = temp1->depth;
		temp.score = temp1->score;
		temp.parent = temp1->parent;
		s.writeNode(outs, temp);

		for(vector<element*>::size_type count = 0; count != temp1->children.size(); ++count) //Place children on queue
		{
			element* temp2;
			temp2 = temp1->children.at(count);
			
			toBeProcessed.push(temp2);
		} 
	}
	
	return outs;
}


void stateSpace::writeNode(ostream& outs, element node)
{
	outs << "Black board: " << endl;
	output(outs, node.black);
	outs << "White board: " << endl;
	output(outs, node.white);
	outs << "Number of Children: " << node.children.size() << endl;
	outs << "Depth: " << node.depth << endl;
	outs << "Score: " << node.score << endl;
	outs << "Parent: " << node.parent << endl;
}


void stateSpace::output(ostream& outs, bitset<64> board)
{
	for(int counter = BIT_DEPTH - 1; counter != -1; --counter)
	{
		outs << board[counter];
		if(counter % 8 == 0)
			outs << endl;
	}
}
