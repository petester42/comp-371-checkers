#include "Agent.h"
#include "stateSpace.h" //Needed to use the stateSpace and to use the element data type
#include "gameLogic.h"  //Needed to use the gameLogic


Agent::Agent(int colour, int skill, Algorithm algorithm, Heuristic heuristic)
{
	_colour = colour;
	_skill = (skill * 2);	// this assumes that skill is put in as 1,2,3, etc and has not been adjusted to work with depth
	_algorithm = algorithm;
	_heuristic = heuristic;

	if (_algorithm == GREEDY)
		_skill--;
}


bitset<64> Agent::getMove(element currentBoard)
{
	_currentBoard = currentBoard;
	_stateSpace = new stateSpace();
	_gameRules = new gameLogic();

	// generate all nodes for move search
	do
	{
		_gameRules->generateChildren(_colour, currentBoard.black, currentBoard.white, currentSet);	// generate the children of the board
		
												// if the set of children is not empty and it's parent's depth is one less than _skill
		if (!currentSet.empty())				// && _stateSpace->getDepth() == (_skill - 1))
			assignScore();						// Score the boards before adding them to the stateSpace
		
		_stateSpace->addChildren(currentSet);	// Add those children to the stateSpace
	
		currentSet.clear();						// Clear the set for the next iteration
		
		_stateSpace->nextNode();				// Advance to next element
			
	}while((_stateSpace->getDepth() < _skill) && (_stateSpace->hasNext()));
	
	desiredSkill = _stateSpace->getDepth();
	
	// determine move based on algorithm
	
	return determineMove();	// bitset that is all 0's except a single 1 indicating the move
}	


void Agent::assignScore()
{
	for (vector<element>::size_type i = 0; i < currentSet.size(); ++i)
	{
		float blackPieces;
		float whitePieces;
		float edgeBonus = 0.0f;

		switch(_heuristic)
		{
		case VERYEASY:	// checks board for player colour minus opponent colour
			
			blackPieces = float(currentSet.at(i)->black.count());
			whitePieces = float(currentSet.at(i)->white.count());
			
			if (_colour == 0)
				currentSet.at(i)->score = blackPieces - whitePieces;
			else
				currentSet.at(i)->score = whitePieces - blackPieces;
			break;

		case EASY:		// player pieces divided by opponent pieces
			blackPieces = float(currentSet[i]->black.count());
			whitePieces = float(currentSet[i]->white.count());
			if (_colour == 0)
				currentSet[i]->score = blackPieces / whitePieces;
			else
				currentSet[i]->score = whitePieces / blackPieces;
			break;

		case MEDIUM:	// player pieces divided by opponent pieces plus points for having edge pieces
			blackPieces = float(currentSet[i]->black.count());
			whitePieces = float(currentSet[i]->white.count());
			if (_colour == 0)
			{
				for (int j = 0; j < 64; ++j)
					if ((j <= 7 | j >= 56 | j % 8 == 0 | (j + 1) % 8 == 0) && (currentSet[i]->black[j] == 1))
						edgeBonus++;
				currentSet[i]->score = blackPieces - whitePieces + edgeBonus;
			}
			else
			{
				for (int j = 0; j < 64; ++j)
					if ((j <= 7 | j >= 56 | j % 8 == 0 | (j + 1) % 8 == 0) && (currentSet[i]->white[j] == 1))
						edgeBonus++;
				currentSet[i]->score = whitePieces - blackPieces + edgeBonus;
			}
			break;

		default:	// same as VERYEASY
			blackPieces = currentSet[i]->black.count();
			whitePieces = currentSet[i]->white.count();
			// _stateSpace.getDepth() % 2 is 1 when looking at player moves and 0 when looking at opponent moves
			if (_colour == 0)
				currentSet[i]->score = blackPieces - whitePieces;
			else
				currentSet[i]->score = whitePieces - blackPieces;
			break;
		}
	}
}


bitset<64> Agent::determineMove()
{
	element* worstSiblingElement;
	element* bestElement;
	element finalElement;
	element resultElement;
	bitset<64> bestMove;
	int bestScore = -65;
	int worstSiblingScore = 0;
	int firCount = 0;
	int secCount = 0;
	
	_stateSpace->getNodes(desiredSkill, nodeSet);
	
	switch(_algorithm)
	{
	case MINMAX:
		for (vector<element>::size_type i = 0; i < nodeSet.size(); ++i)
		{
			worstSiblingScore = 0;	// reset score for next set of children
			for (vector<element>::size_type j = 0; j < nodeSet.at(i).size(); ++j)
			{
				if (j == 0)	// if it is the first child in a set
				{
					firCount = i;
					secCount = j;
					worstSiblingScore = nodeSet.at(i).at(j)->score;	// the worst score will automatically be that of the first child in a set
					worstSiblingElement = nodeSet.at(i).at(j);	// ditto for the element
				}
				else
				{
					if (nodeSet.at(i).at(j)->score < worstSiblingScore)	// check if the currently examined sibling has the worst score so far
					{
						firCount = i;
						secCount = j;
						worstSiblingScore = nodeSet.at(i).at(j)->score;
						worstSiblingElement = nodeSet.at(i).at(j); 
					}
				}
			}
			if (worstSiblingScore > bestScore)	// check if the worst sibling in the completed set is better than any other worst sibling in a set
			{
				bestScore = worstSiblingScore;
				bestElement = worstSiblingElement;
			}
		}

		finalElement.black = bestElement->black;
		finalElement.white = bestElement->white;
		finalElement.score = bestElement->score;
		finalElement.depth = bestElement->depth;
		break;

	case GREEDY:
		for (vector<element>::size_type i = 0; i < nodeSet.size(); ++i)
		{
			for (vector<element>::size_type j = 0; j < nodeSet.at(i).size(); ++j)
			{
				if (nodeSet.at(i).at(j)->score > bestScore)
				{
					firCount = i;
					secCount = j;
					bestScore = nodeSet.at(i).at(j)->score;
					finalElement.black = nodeSet.at(i).at(j)->black;
					finalElement.white = nodeSet.at(i).at(j)->white;
					finalElement.score = nodeSet.at(i).at(j)->score;
					finalElement.depth = nodeSet.at(i).at(j)->depth;
				}
			}
		}
		break;
	}
	
	resultElement = _stateSpace->locateParent(desiredSkill, finalElement, firCount, secCount);
	
	bestMove = (_currentBoard.black | _currentBoard.white) ^ (resultElement.black | resultElement.white);
	
	nodeSet.clear();
	delete _stateSpace;
	delete _gameRules;
	return bestMove;
}


void Agent::output(ostream& outs, bitset<64> board)
{
	for(int counter = 64 - 1; counter != -1; --counter)
	{
		outs << board[counter];
		if(counter % 8 == 0)
			outs << endl;
	}
}
