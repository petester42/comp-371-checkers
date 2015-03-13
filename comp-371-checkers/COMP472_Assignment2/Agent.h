/**
 *======================================================================
 *  Student#1: Angelo Pulcini		Student ID: 3946703
 *  Student#2: Jonathan Evans		Student ID: 5201713
 *  Course: COMP 472                Section:  Lec F
 *  Instructor: Sabine Bergler
 *  Assignment #2
 *  
 *  Description:
 *  This is the header file for the Agent class.
 *  
 *======================================================================
 */

#ifndef AGENT_H
#define AGENT_H

#include <vector>
#include "stateSpace.h"
#include "gameLogic.h"  //Needed to use the gameLogic
#include <bitset>

enum Algorithm { GREEDY, MINMAX };
enum Heuristic { VERYEASY, EASY, MEDIUM };


using namespace std;

class Agent
{
private:
	vector<element*> currentSet;
	vector<vector<element*>> nodeSet;
	int _colour;
	int _skill;
	Algorithm _algorithm; 
	Heuristic _heuristic;
	stateSpace* _stateSpace;
	gameLogic* _gameRules;
	element _currentBoard;
	int desiredSkill;

	void assignScore();
	bitset<64> determineMove();
	void output(ostream& outs, bitset<64> temp);

public:
	Agent(int colour, int skill, Algorithm algorithm, Heuristic heuristic);
	bitset<64> getMove(element currentBoard);
};

#endif