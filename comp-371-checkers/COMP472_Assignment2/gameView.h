/**
 *======================================================================
 *  Student#1: Angelo Pulcini		Student ID: 3946703
 *  Student#2: Jonathan Evans		Student ID: 5201713
 *  Course: COMP 472                Section:  Lec F
 *  Instructor: Sabine Bergler
 *  Assignment #2
 *  
 *  Description:
 *  This is the header file for the gameView class.
 *  
 *======================================================================
 */
#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <string>
#include <iostream>
#include "gameLogic.h"

using namespace std;

struct location
{
	int row;
	int column;
	int position;
};

class gameView
{
private:
	static const int BIT_DEPTH = 64;
	gameView(const gameLogic& g);
	gameView& operator= (const gameLogic& g);
	static const int rows = 8; 
	string header;
	string posHeader;
	string footer;
	bitset<BIT_DEPTH> currentBoard;
	void processInput();
	void refreshScreen();
	void displayMoveList(ostream& outs, vector<location> moveList);
	bitset<gameView::BIT_DEPTH> getUserInput(vector<location> moveList);

public:
	gameView();
	gameView(int firstBlack, int firstWhite, int secondBlack, int secondWhite);
	~gameView();
	bitset<BIT_DEPTH> showPossibleMoves(ostream& outs, bitset<BIT_DEPTH> blackBoard, bitset<BIT_DEPTH> whiteBoard, int blackScore, int whiteScore, bitset<BIT_DEPTH> movesBoard);
	void displayBoard(ostream& outs, bitset<BIT_DEPTH> blackBoard, bitset<BIT_DEPTH> whiteBoard, int blackScore, int whiteScore);

};

#endif
