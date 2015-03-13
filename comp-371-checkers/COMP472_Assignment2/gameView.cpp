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

#include "gameView.h"
#include <process.h>
#include <iomanip>
#include <vector>
#include <string>


gameView::gameView()
{
	header = "===================";
	footer = "===================";
	posHeader = "   7 6 5 4 3 2 1 0\n-------------------";

	currentBoard.set(1);
	currentBoard.set(3);
	currentBoard.set(5);
	currentBoard.set(7);
	currentBoard.set(8);
	currentBoard.set(10);
	currentBoard.set(12);
	currentBoard.set(14);
	currentBoard.set(17);
	currentBoard.set(19);
	currentBoard.set(21);
	currentBoard.set(23);

	currentBoard.set(40);
	currentBoard.set(42);
	currentBoard.set(44);
	currentBoard.set(46);
	currentBoard.set(49);
	currentBoard.set(51);
	currentBoard.set(53);
	currentBoard.set(55);
	currentBoard.set(56);
	currentBoard.set(58);
	currentBoard.set(60);
	currentBoard.set(62);
}


gameView::gameView(int firstBlack, int firstWhite, int secondBlack, int secondWhite)
{
	header = "===================";
	footer = "===================";
	posHeader = "   7 6 5 4 3 2 1 0\n-------------------";

	currentBoard.set(35);
	currentBoard.set(36);
	currentBoard.set(28);
	currentBoard.set(27);
	

/*	currentBoard.set(38);
	currentBoard.set(45);
	currentBoard.set(37);
	currentBoard.set(52);
	currentBoard.set(43);
	currentBoard.set(35);
	currentBoard.set(34);
	currentBoard.set(44);
	currentBoard.set(36);
	currentBoard.set(28);
	currentBoard.set(29);
	currentBoard.set(27);*/


/*	currentBoard.set(62);
	currentBoard.set(61);
	currentBoard.set(60);
	currentBoard.set(59);
	currentBoard.set(58);
	currentBoard.set(53);
	currentBoard.set(52);
	currentBoard.set(48);
	currentBoard.set(47);
	currentBoard.set(45);
	currentBoard.set(43);
	currentBoard.set(41);
	currentBoard.set(40);
	currentBoard.set(39);
	currentBoard.set(37);
	currentBoard.set(36);
	currentBoard.set(33);
	currentBoard.set(32);
	currentBoard.set(31);
	currentBoard.set(28);
	currentBoard.set(25);
	currentBoard.set(24);
	currentBoard.set(23);
	currentBoard.set(16);
	currentBoard.set(10);
	currentBoard.set(9);
	currentBoard.set(8);
	currentBoard.set(7);
	currentBoard.set(6);
	currentBoard.set(5);
	currentBoard.set(4);
	currentBoard.set(3);
	currentBoard.set(2);
	currentBoard.set(0);
	
	currentBoard.set(54);
	currentBoard.set(51);
	currentBoard.set(50);
	currentBoard.set(46);
	currentBoard.set(44);
	currentBoard.set(42);
	currentBoard.set(38);
	currentBoard.set(35);
	currentBoard.set(34);
	currentBoard.set(30);
	currentBoard.set(29);
	currentBoard.set(27);
	currentBoard.set(26);
	currentBoard.set(22);
	currentBoard.set(21);
	currentBoard.set(20);
	currentBoard.set(19);
	currentBoard.set(18);
	currentBoard.set(17);
	currentBoard.set(15);
	currentBoard.set(14);
	currentBoard.set(13);
	currentBoard.set(12);
	currentBoard.set(11);
*/


}


gameView::~gameView()
{

}


gameView::gameView(const gameLogic& g)
{
	
}


gameView& gameView::operator= (const gameLogic& g)
{
	return *this;
}


bitset<gameView::BIT_DEPTH> gameView::showPossibleMoves(ostream& outs, bitset<BIT_DEPTH> blackBoard, bitset<BIT_DEPTH> whiteBoard, int blackScore, int whiteScore, bitset<BIT_DEPTH> movesBoard)
{
	int outputRow = 1;
	vector<location> moveList;

//	refreshScreen();
	outs << endl << header << endl;
	outs << "Possible Moves: ";
	outs << endl << header << endl;
	outs << posHeader << endl;

	for(int counter = BIT_DEPTH - 1; counter != -1; --counter)
	{
		if(counter % rows == rows - 1)
			outs << outputRow << "|"; 

		if (whiteBoard[counter] == 1)
			outs << setw(2) << 'W';
		else if(blackBoard[counter] == 1)
			outs << setw(2) << 'B';
		else if(movesBoard[counter] == 1)
		{
			location temp;
			temp.column = (counter % rows);
			temp.row = outputRow;
			temp.position = counter;
			moveList.push_back(temp);
			outs << setw(2) << 'P';
		}
		else
			outs << setw(2) << '0';
		
		if(counter % rows == 0)
		{
			outs << endl;
			outputRow += 1;
		}
	}

	outs << footer << endl << "Score:" << setw(5) << " B:" << setw(2) << blackScore 
		<< " W:" << setw(2) << whiteScore << endl << footer << endl << endl;

	displayMoveList(outs, moveList);

	return getUserInput(moveList);
}


void gameView::displayBoard(ostream& outs, bitset<BIT_DEPTH> blackBoard, bitset<BIT_DEPTH> whiteBoard, int blackScore, int whiteScore)
{
	int outputRow = 1;

//	refreshScreen();
	outs << endl << header << endl;
	outs << "Current Board: ";
	outs << endl << header << endl;
	outs << posHeader << endl;

	for(int counter = BIT_DEPTH - 1; counter != -1; --counter)
	{
		if(counter % rows == rows - 1)
			outs << outputRow << "|"; 

		if (whiteBoard[counter] == 1)
			outs << setw(2) << 'W';
		else if(blackBoard[counter] == 1)
			outs << setw(2) << 'B';
		else
			outs << setw(2) << '0';
		
		if(counter % rows == 0)
		{
			outs << endl;
			outputRow += 1;
		}
	}

	outs << footer << endl << "Score:" << setw(5) << " B:" << setw(2) << blackScore 
		<< " W:" << setw(2) << whiteScore << endl << footer << endl << endl; 
}


bitset<gameView::BIT_DEPTH> gameView::getUserInput(vector<location> moveList)
{
	int selection;

	cin >> selection; 
	selection -= 1;
	
	bitset<BIT_DEPTH> result;
	result.set(moveList.at(selection).position);

	return result;
}


void gameView::processInput()
{

}


void gameView::refreshScreen()
{
	system ("cls");	
}


void gameView::displayMoveList(ostream& outs, vector<location> moveList)
{
	outs << "Please make a selection:\n" << endl;

	for(vector<location>::size_type counter = 0; counter != moveList.size(); ++counter)
		outs << counter + 1 << ". Move to column " << moveList.at(counter).column << ", row " 
		<< moveList.at(counter).row << "." << endl;
}

