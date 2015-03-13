/**
 *======================================================================
 *  Student#1: Angelo Pulcini		Student ID: 3946703
 *  Student#2: Jonathan Evans		Student ID: 5201713
 *  Course: COMP 472                Section:  Lec F
 *  Instructor: Sabine Bergler
 *  Assignment #2
 *  
 *  Description:
 *  This is the header file for the gameLogic class.
 *  
 *======================================================================
 */
#pragma once
#include <bitset>
#include <iostream>
#include <vector>
#include "stateSpace.h"

using namespace std;

class gameLogic
{
private:
	static const int BIT_DEPTH = 64;
	bitset<BIT_DEPTH> emptyBoard;
	bitset<BIT_DEPTH> downMask;
	bitset<BIT_DEPTH> upMask;
	bitset<BIT_DEPTH> rightMask;
	bitset<BIT_DEPTH> leftMask;
	bitset<BIT_DEPTH> leftTopMask;
	bitset<BIT_DEPTH> leftDownMask;
	bitset<BIT_DEPTH> rightTopMask;
	bitset<BIT_DEPTH> rightDownMask;
	bitset<BIT_DEPTH> blackPieces;
	bitset<BIT_DEPTH> whitePieces;
	bitset<BIT_DEPTH> whiteQueens;
	bitset<BIT_DEPTH> blackQueens;
	bitset<BIT_DEPTH> blackQueenMask;
	bitset<BIT_DEPTH> whiteQueenMask;
	int blackScore;
	int whiteScore;
	bool turn;
	void calculateCurrentScore();
	void output(ostream& outs, bitset<64> board);
	void initializeValues();
	void initializeValues(int firstBlack, int firstWhite, int secondBlack, int secondWhite);
	int convertIndex(int index);
	bitset<gameLogic::BIT_DEPTH> gameLogic::convertBitset(bitset<BIT_DEPTH> input);
	int gameLogic::retrieveIndex(bitset<BIT_DEPTH> input);


public:
	gameLogic();
	gameLogic(int firstBlack, int firstWhite, int secondBlack, int secondWhite);
	gameLogic(const gameLogic& g);
	~gameLogic();
	gameLogic& operator= (const gameLogic& g);
	bitset<BIT_DEPTH> generateAcceptedMoves(int player, int index);
	bitset<BIT_DEPTH> generateAcceptedMoves(int player, bitset<BIT_DEPTH> black, bitset<BIT_DEPTH> white);
	void generateChildren(int player, bitset<BIT_DEPTH> black, bitset<BIT_DEPTH> white, vector<element*>& children);
	void performMove(int player, bitset<BIT_DEPTH> intendedMove, bitset<BIT_DEPTH> originalPosition);
	void performMove(int player, bitset<BIT_DEPTH> intendedMove, bitset<BIT_DEPTH>& black, bitset<BIT_DEPTH>& white);
	bool verifyMove(int player, bitset<BIT_DEPTH> intendedMove);
	int getBlackScore();
	int getWhiteScore();
	bitset<BIT_DEPTH> getWhiteBoard();
	bitset<BIT_DEPTH> getBlackBoard();
	bool getTurn();
	void switchTurn();
	int checkWinner();
	bool gameCanStillPlay();
	bool boardHasSpaces();
	bool blackHasMoves();
	bool whiteHasMoves();
	bool isBlack(int index);
	bool isWhite(int index);
	bitset<BIT_DEPTH> calculateDown(bitset<BIT_DEPTH> currentPlayer, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> mask);
	bitset<BIT_DEPTH> calculateUp(bitset<BIT_DEPTH> currentPlayer, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> mask);
	bitset<BIT_DEPTH> calculateLeft(bitset<BIT_DEPTH> currentPlayer, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> mask);
	bitset<BIT_DEPTH> calculateRight(bitset<BIT_DEPTH> currentPlayer, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> mask);
	bitset<BIT_DEPTH> calculateLeftTop(bitset<BIT_DEPTH> targetPiece, bitset<BIT_DEPTH> currentPlayer, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> mask);
	bitset<BIT_DEPTH> calculateLeftDown(bitset<BIT_DEPTH> targetPiece, bitset<BIT_DEPTH> currentPlayer, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> mask);
	bitset<BIT_DEPTH> calculateRightUp(bitset<BIT_DEPTH> targetPiece, bitset<BIT_DEPTH> currentPlayer, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> mask);
	bitset<BIT_DEPTH> calculateRightDown(bitset<BIT_DEPTH> targetPiece, bitset<BIT_DEPTH> currentPlayer, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> mask);
	bitset<BIT_DEPTH> captureUp(bitset<BIT_DEPTH> intendedMove, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> firstPlayer, bitset<BIT_DEPTH> mask);
	bitset<BIT_DEPTH> captureDown(bitset<BIT_DEPTH> intendedMove, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> firstPlayer, bitset<BIT_DEPTH> mask);
	bitset<BIT_DEPTH> captureLeft(bitset<BIT_DEPTH> intendedMove, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> firstPlayer, bitset<BIT_DEPTH> mask);
	bitset<BIT_DEPTH> captureRight(bitset<BIT_DEPTH> intendedMove, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> firstPlayer, bitset<BIT_DEPTH> mask);
	bitset<BIT_DEPTH> captureLeftTop(bitset<BIT_DEPTH> intendedMove, bitset<BIT_DEPTH> previousPosition, bitset<BIT_DEPTH> firstPlayer, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> mask);
	bitset<BIT_DEPTH> captureLeftDown(bitset<BIT_DEPTH> intendedMove, bitset<BIT_DEPTH> previousPosition, bitset<BIT_DEPTH> firstPlayer, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> mask);
	bitset<BIT_DEPTH> captureRightTop(bitset<BIT_DEPTH> intendedMove, bitset<BIT_DEPTH> previousPosition, bitset<BIT_DEPTH> firstPlayer, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> mask);
	bitset<BIT_DEPTH> captureRightDown(bitset<BIT_DEPTH> intendedMove, bitset<BIT_DEPTH> previousPosition, bitset<BIT_DEPTH> firstPlayer, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> mask);
	friend ostream& operator << (ostream& outs, gameLogic& g);
};
