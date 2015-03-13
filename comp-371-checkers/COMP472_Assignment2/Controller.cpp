/**
 *======================================================================
 *  Student#1: Angelo Pulcini		Student ID: 3946703
 *  Student#2: Jonathan Evans		Student ID: 5201713
 *  Course: COMP 472                Section:  Lec F
 *  Instructor: Sabine Bergler
 *  Assignment #2
 *  
 *  Description:
 *  This is the implementation file for the Controller.
 *  
 *======================================================================
 */
#include <bitset>
#include <fstream>
#include <iostream>
#include <fstream>
#include <vector>
#include "gameLogic.h"
#include "gameView.h"
#include "stateSpace.h"
#include "BoardPosition.h"
#include "GameBoard.h"
#include <SDL/SDL.h>
#include <process.h>
#include "Agent.h"
#include <tchar.h>
#include <Windows.h>


using namespace std;

void output(ostream& outs, bitset<64> board)
{
	for(int counter = 64 - 1; counter != -1; --counter)
	{
		outs << board[counter]; 
		if(counter % 8 == 0)
			outs << endl;
	}
}


int showMenu1()
{
	int firstSelection;

	do
	{
		system("cls");
		cout << "Reversi Startup:" << endl;
		cout << "================" << endl;
		cout << "1. Player versus player." << endl;
		cout << "2. Player versus AI." << endl;
		cout << "3. AI versus AI." << endl;
		cout << "0. Exit application." << endl;
		cin >> firstSelection;
	}while(!((firstSelection == 1) || (firstSelection == 2) || (firstSelection == 3) || (firstSelection == 0)));

	return firstSelection;
}


int showMenu2(string playerNumber)
{
	int secondSelection;

	do
	{
		system("cls");
		cout << "Algorithm selection for player " << playerNumber << ":" << endl;
		cout << "=================================" << endl;
		cout << "1. Greedy." << endl;
		cout << "2. Minmax." << endl;
		cout << "0. Exit application." << endl;
		cin >> secondSelection;
	}while(!((secondSelection == 1) || (secondSelection == 2) || (secondSelection == 0)));

	if(secondSelection != 0)
		return secondSelection - 1;
	else
		exit(0);
}


int showMenu3(string playerNumber)
{
	int secondSelection;

	do
	{
		system("cls");
		cout << "Difficulty selection for player " << playerNumber << ":" << endl;
		cout << "==================================" << endl;
		cout << "1. Very Easy." << endl;
		cout << "2. Easy." << endl;
		cout << "3. Medium." << endl;
		cout << "0. Exit application." << endl;
		cin >> secondSelection;
	}while(!((secondSelection == 1) || (secondSelection == 2) || (secondSelection == 3) || (secondSelection == 0)));

	if(secondSelection != 0)
		return secondSelection - 1;
	else
		exit(0);
}


bool init(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const int SCREEN_BPP, SDL_Surface* &screen)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_DOUBLEBUF|SDL_HWSURFACE);

	if(screen == 0)
	{
		return false;
	}

	SDL_WM_SetCaption("Honeycomb", 0);

	return true;
}


void startGame(gameLogic*& model, GameBoard*& view, gameView*& consoleView, SDL_Surface* screen)
{
	model = new gameLogic();
	view = new GameBoard(screen);
	consoleView = new gameView();
}

/*
	This isn't the final version of the main controller.  This is a quick modification to allow us to test the
	game logic and communication between the gameLogic and gameView.  I will add the rest of the command 
	processor code back in once everything is ready.  With this code the game is almost ready to play a 2 player
	game.  I just need to make a few small modifications to allow a 2 player game.  This will allow us to test the
	game logic.
*/
int main(int argc, char* args[])
{
	int selectionResult1;
	bool quit = false, update = false;
	gameLogic* model;
	gameView* consoleView;
	bitset<64> black;
	bitset<64> white;
	SDL_Event event;
	SDL_Surface* screen = 0;
	GameBoard* view;
	Agent* AIPlayer1 = 0;
	Agent* AIPlayer2 = 0;
	bitset<64> intendedMove;
	bitset<64> emptyBoard;
	int algorithm;
	int difficulty;

	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	const int SCREEN_BPP = 32;

	selectionResult1 = showMenu1();

	switch(selectionResult1)
	{
	case 0:
		return 0;
		break;
	case 2:
		algorithm = showMenu2("2");
		difficulty = showMenu3("2");
		AIPlayer2 = new Agent(1, 2, (Algorithm)algorithm, (Heuristic)difficulty);
		break;
	case 3:
		algorithm = showMenu2("1");
		difficulty = showMenu3("1");
		AIPlayer1 = new Agent(0, 2, (Algorithm)algorithm, (Heuristic)difficulty);
		algorithm = showMenu2("2");
		difficulty = showMenu3("2");
		AIPlayer2 = new Agent(1, 2, (Algorithm)algorithm, (Heuristic)difficulty);
		break;
	default:
		break;
	}

	ofstream outfile("results.out", ios::out);
	if(!outfile)
	{
		cout << "ERROR: Unable to open output file results.out" << endl;
		return -1;
	}	

	_putenv("SDL_VIDEO_CENTERED=1");

	init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, screen);
	startGame(model, view, consoleView, screen);

	bitset<64> possibleMoves;

	consoleView->displayBoard(cout, model->getBlackBoard(), model->getWhiteBoard(), model->getBlackScore(), model->getWhiteScore());
	//possibleMoves = model->generateAcceptedMoves(model->getTurn(), );
	//view->showPossibleMoves(possibleMoves);

	while(!quit)
	{
		if((!model->getTurn()) && (AIPlayer1 != 0) && (!update))
		{
			element agentInput;
			bitset<64> agentResult;

			agentInput.black = model->getBlackBoard();
			agentInput.white = model->getWhiteBoard();

			intendedMove = AIPlayer1->getMove(agentInput);
			update = true;
		}

		if((model->getTurn()) && (AIPlayer2 != 0) && (!update))
		{
			element agentInput;
			bitset<64> agentResult;

			agentInput.black = model->getBlackBoard();
			agentInput.white = model->getWhiteBoard();

			intendedMove = AIPlayer2->getMove(agentInput);
			update = true;
		}

		if(update)
		{
			model->performMove(model->getTurn(), intendedMove);
			view->clearHighlights(possibleMoves);
			view->displayBoard(model->getBlackBoard(), model->getWhiteBoard(), model->getBlackScore(), model->getWhiteScore());
			view->nextTurn(!model->getTurn());
			consoleView->displayBoard(outfile, model->getBlackBoard(), model->getWhiteBoard(), model->getBlackScore(), model->getWhiteScore());
			consoleView->displayBoard(cout, model->getBlackBoard(), model->getWhiteBoard(), model->getBlackScore(), model->getWhiteScore());
			possibleMoves = model->generateAcceptedMoves(model->getTurn(),1);//here is where the index needs to be
			view->showPossibleMoves(possibleMoves);
			if((AIPlayer2 != 0) || (AIPlayer1 != 0))
				SDL_Delay(1500);
			if(!model->gameCanStillPlay())
			{
				model->switchTurn();
				if(model->gameCanStillPlay())
				{
					view->nextTurn(model->getTurn());
					possibleMoves = model->generateAcceptedMoves(model->getTurn(),1);//here is where the index needs to be
					view->showPossibleMoves(possibleMoves);
					update = false;
					intendedMove = emptyBoard;			
				}
				else
				{
					if(model->getBlackScore() > model->getWhiteScore())
						MessageBox(GetActiveWindow(), _T("Black Wins"), _T("Reversi"), 0);
					else if(model->getBlackScore() < model->getWhiteScore())
						MessageBox(GetActiveWindow(), _T("White Wins"), _T("Reversi"), 0);
					else if(model->getBlackScore() == model->getWhiteScore())
						MessageBox(GetActiveWindow(), _T("Tie Game"), _T("Reversi"), 0);
					
					quit = !quit;
				}
			}
			else
			{
				update = false;
				intendedMove = emptyBoard;
			}
		}

		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_MOUSEBUTTONDOWN:
				if(event.button.button == SDL_BUTTON_LEFT)
				{
					if((!model->getTurn()) && (AIPlayer1 == 0) && (!update))
					{
						int w = event.button.x;
						int z = event.button.y;
						int result = view->checkEvents(w, z, possibleMoves);
						if(result != -1)
						{
							intendedMove.set(result);			
							update = true;
						}
					}
					
					if((model->getTurn()) && (AIPlayer2 == 0) && (!update))
					{
						int w = event.button.x;
						int z = event.button.y;
						int result = view->checkEvents(w, z, possibleMoves);
						if(result != -1)
						{
							intendedMove.set(result);			
							update = true;
						}
					}
				}
				break;
			case SDL_QUIT:
				quit = true;
				break;
			}
		}
	}
	
	delete model;
	delete consoleView;
	delete view;
	outfile.close();

	if(screen != 0)
		SDL_FreeSurface(screen);

	SDL_Quit();
	return 0;
}

