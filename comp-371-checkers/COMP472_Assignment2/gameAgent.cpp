/**
 *======================================================================
 *  Student#1: Angelo Pulcini		Student ID: 3946703
 *  Student#2: Jonathan Evans		Student ID: 5201713
 *  Course: COMP 472                Section:  Lec F
 *  Instructor: Sabine Bergler
 *  Assignment #2
 *  
 *  Description:
 *  This is the implementation file for the gameAgent class.
 *  
 *======================================================================
 */
#include "gameAgent.h"
#include "stateSpace.h"  //Needed to use the stateSpace and to use the element data type
#include "gameLogic.h"  //Needed to use the gameLogic
#include <iostream> //for debugging purposes
#include <bitset>

using namespace std;

gameAgent::gameAgent(int newColour, int newSkill, Algorithm newAlgorithm, Heuristic newHeuristic)
{
	colour = colour;
	skill = ((skill - 1) * 2) + 1;	// this assumes that skill is put in as 1,2,3, etc and has not been adjusted to work with depth
	algorithm = algorithm;
	heuristic = heuristic;

	storage = new stateSpace();
	gameRules = new gameLogic();
}


bitset<64> gameAgent::generateMoves(element currentBoard)
{
	//currentSet.push_back(currentBoard);			// add the currentBoard to the agents vector.  Actually, for the generateChildren function to work properly the vector should be empty.

	// generate all nodes for move search
	do
	{
//		gameRules->generateChildren(skill, currentBoard.black, currentBoard.white, currentSet);	// generate the children of the board
		//calculateCost();						//Score the boards before adding them to the stateSpace
//		storage->addChildren(currentSet);		// add those children to the stateSpace
		currentSet.clear();						// clear the set for the next iteration
		
		storage->nextNode();					// advance to next element
	}while(storage->getDepth() < skill);

	vector<element> targetNodes;
	storage->getNodes(skill, targetNodes);

	//return determineMove(targetNodes);	// bitset that is all 0's except a single 1 indicating the move

	bitset<64> temp;
	return temp;
}	

/*
void gameAgent::calculateScore()
{
	int blackPieces;
	int whitePieces;
	int edgeBonus = 0;

	switch(heuristic)
	{
	case VERYEASY:	// checks board for player colour minus opponent colour
		blackPieces = _stateSpace.getBlackBoard().count();
		whitePieces = _stateSpace.getWhiteBoard().count();
		// _stateSpace.getDepth() % 2 is 1 when looking at player moves and 0 when looking at opponent moves
		if ((_colour == 0 && _stateSpace.getDepth() % 2 == 1) || (_colour == 1 && _stateSpace.getDepth() % 2 == 0))
			_stateSpace.setScore((float)(blackPieces - whitePieces));
		else
			_stateSpace.setScore((float)(whitePieces - blackPieces));
		break;

	case EASY:		// player pieces divided by opponent pieces
		blackPieces = _stateSpace.getBlackBoard().count();
		whitePieces = _stateSpace.getWhiteBoard().count();
		if ((_colour == 0 && _stateSpace.getDepth() % 2 == 1) || (_colour == 1 && _stateSpace.getDepth() % 2 == 0))
			_stateSpace.setScore((float)(blackPieces / whitePieces));
		else
			_stateSpace.setScore((float)(whitePieces / blackPieces));
		break;

	case MEDIUM:	// player pieces divided by opponent pieces plus points for having edge pieces
		blackPieces = _stateSpace.getBlackBoard().count();
		whitePieces = _stateSpace.getWhiteBoard().count();
		if ((_colour == 0 && _stateSpace.getDepth() % 2 == 1) || (_colour == 1 && _stateSpace.getDepth() % 2 == 0))
		{
			for (int i = 0; i < 64; ++i)
				if ((i <= 7 || i >= 56 || i % 8 == 0 || (i + 1) % 8 == 0) && (_stateSpace.getBlackBoard()[i] == 1))
					edgeBonus++;
			_stateSpace.setScore((float)(blackPieces / whitePieces + edgeBonus));
		}
		else
		{
			for (int i = 0; i < 64; ++i)
				if ((i <= 7 || i >= 56 || i % 8 == 0 || (i + 1) % 8 == 0) && (_stateSpace.getWhiteBoard()[i] == 1))
					edgeBonus++;
			_stateSpace.setScore((float)(whitePieces / blackPieces + edgeBonus));
		}
		break;

	default:	// same as VERYEASY
		blackPieces = _stateSpace.getBlackBoard().count();
		whitePieces = _stateSpace.getWhiteBoard().count();
		// _stateSpace.getDepth() % 2 is 1 when looking at player moves and 0 when looking at opponent moves
		if ((_colour == 0 && _stateSpace.getDepth() % 2 == 1) || (_colour == 1 && _stateSpace.getDepth() % 2 == 0))
			_stateSpace.setScore((float)(blackPieces - whitePieces));
		else
			_stateSpace.setScore((float)(whitePieces - blackPieces));
		break;
	}
}


bitset<64> determineMove(vector<element> nodes)
{
//	element* bestElement;
	bitset<64> bestMove;
	/*float bestScore = 0.0f;

	switch(_algorithm)
	{
	case MINMAX:
		// I'm looking for the vector containing all the elements I've generated here
		for(vector<element *>::iterator it = _stateList.start(); it != _stateList.end(); ++it)	
		{
			// find elements with depth == skill - 1 -> these are the parents of the last row
			// take the children of that element and select the one with the lowest score
			// if that score is higher than bestScore
				// set bestElement to that element and bestScore to the score
			// once this has been done with all elements, bestElement will be the parent with the highest low score amongst its children
			// trace this back until the element being examined has depth == 1
			// set bestElement to this value
		}
		break;
	case GREEDY:
		for(vector<element *>::iterator it = _stateList.start(); it != _stateList.end(); ++it)	
		{
			// find elements with depth == skill -> these are the last row
			// find the element amongst these with the highest score
			// trace this back until the element being examined has depth == 1
			// set bestElement to this value
		}
		break;
	}

	// take bestElement and create the move bitset from its data
	// get this bitset with (parent.getBlackBoard || parent.getWhiteBoard) ^ (move.getBlackBoard || move.getWhiteBoard)
	// set bestMove to this bitSet<64>

	return bestMove;
}
*/