/**
 *======================================================================
 *  Student#1: Angelo Pulcini		Student ID: 3946703
 *  Student#2: Jonathan Evans		Student ID: 5201713
 *  Course: COMP 472                Section:  Lec F
 *  Instructor: Sabine Bergler
 *  Assignment #2
 *  
 *  Description:
 *  This is the header file for the gameAgent class.
 *  
 *======================================================================
 */

#ifndef GAMEAGENT_H
#define GAMEAGENT_H

#include <vector>
#include "stateSpace.h"
#include "gameLogic.h"  //Needed to use the gameLogic
#include <bitset>

using namespace std;

class gameAgent
{
private:
	enum Algorithm { GREEDY, MINMAX };
	enum Heuristic { VERYEASY, EASY, MEDIUM };
	vector<element> currentSet;
	int colour;
	int skill;
	Algorithm algorithm; 
	Heuristic heuristic;
	stateSpace* storage;
	gameLogic* gameRules;
//	void calculateCost();
//	bitset<64> determineMove(vector<element> nodes);

public:
	gameAgent(int newColour, int newSkill, Algorithm newAlgorithm, Heuristic newHeuristic);
	bitset<64> generateMoves(element currentBoard);
};

#endif