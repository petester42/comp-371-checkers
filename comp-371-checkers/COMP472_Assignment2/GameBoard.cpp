/**
 *======================================================================
 *  Student#1: Angelo Pulcini		Student ID: 3946703
 *  Student#2: Jonathan Evans		Student ID: 5201713
 *  Course: COMP 472                Section:  Lec F
 *  Instructor: Sabine Bergler
 *  Assignment #2
 *  
 *  Description:
 *  This is the implementation file for the GameBoard class.
 *  
 *======================================================================
 */
#include <SDL/SDL.h>
#include "GameBoard.h"
#include "BoardPosition.h"
//#include "FrameAnimation.h"
#include <iostream>
#include "ScoreBoard.h"
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include "TopMenu.h"
#include <vector>
#include <Windows.h>
#include <tchar.h>

using namespace std;


GameBoard::GameBoard(SDL_Surface* screen)
{
	STRPOSSIBLE = "Blue Jewel.bmp";
	STRREDPIECE = "Black Jewel.bmp";
	STRBLUEPIECE = "White Jewel.bmp";
	STRBOARDPIECE = "Board.bmp";
	STRBACK = "Casa.bmp";
	STRLEFTTOP = "Top.bmp";
	STRLEFTTOPH = "TopHighlight.bmp";
	STRBOTTOMLEFT = "bottomLeft.bmp";
	textcolor.r = 255;
	textcolor.g = 255;
	textcolor.b = 255;
	backcolor.r = 0;
	backcolor.g = 0;
	backcolor.b = 0;
	leftTop = 0;
	rightTop = 0;
	bottomLeft = 0;
	//animator = 0;

	if(screen != 0)
	{
		leftTopArea.x = 0;
		leftTopArea.y = 0;
		leftTopArea.h = 175;
		leftTopArea.w = 640;

		bottomLeftArea.x = 0;
		bottomLeftArea.y = 410;
		bottomLeftArea.h = 70;
		bottomLeftArea.w = 160;

		screenArea = screen;

		background = new BoardPosition(screenArea, firstx, firsty, SCREEN_WIDTH, SCREEN_WIDTH, 0, STRBACK);
//		menu = new TopMenu(screenArea, firstx, firsty, SCREEN_WIDTH, 175, 500, 10, 120, 35, 14, 10, 110, 35, STRLEFTTOP, "TopHighlight2.bmp", "TopNew2.bmp");
		stopLight = new TopMenu(screenArea, SCREEN_WIDTH - 160, SCREEN_HEIGHT - 70, 125, 50, 0, 0, 0, 0, 0, 0, 0, 0, "rightBlack.bmp", "rightWhite.bmp");
		loadImage(STRBOTTOMLEFT, bottomLeft, bottomLeftArea);
		minitron = new ScoreBoard(11, 424, 125, 50, "arial.ttf", STRBLUEPIECE, STRREDPIECE, screenArea, backcolor, textcolor, 14);
		setPositions();
		setGamePiece(1, 1);
		setGamePiece(3, 1);
		setGamePiece(5, 1);
		setGamePiece(7, 1);
		setGamePiece(8, 1);
		setGamePiece(10, 1);
		setGamePiece(12, 1);
		setGamePiece(14, 1);
		setGamePiece(17, 1);
		setGamePiece(19, 1);
		setGamePiece(21, 1);
		setGamePiece(23, 1);

		setGamePiece(40, 0);
		setGamePiece(42, 0);
		setGamePiece(44, 0);
		setGamePiece(46, 0);
		setGamePiece(49, 0);
		setGamePiece(51, 0);
		setGamePiece(53, 0);
		setGamePiece(55, 0);
		setGamePiece(56, 0);
		setGamePiece(58, 0);
		setGamePiece(60, 0);
		setGamePiece(62, 0);
		setScore(12, 12);
	}
}


GameBoard::GameBoard(SDL_Surface* screen, int firstBlack, int firstWhite, int secondBlack, int secondWhite)
{
	STRPOSSIBLE = "Blue Jewel.bmp";
	STRREDPIECE = "Black Jewel.bmp";
	STRBLUEPIECE = "White Jewel.bmp";
	STRBOARDPIECE = "Board.bmp";
	STRBACK = "Casa.bmp";
	STRLEFTTOP = "Top.bmp";
	STRLEFTTOPH = "TopHighlight.bmp";
	STRBOTTOMLEFT = "bottomLeft.bmp";
	textcolor.r = 255;
	textcolor.g = 255;
	textcolor.b = 255;
	backcolor.r = 0;
	backcolor.g = 0;
	backcolor.b = 0;
	leftTop = 0;
	rightTop = 0;
	bottomLeft = 0;
	//animator = 0;

	if(screen != 0)
	{
		leftTopArea.x = 0;
		leftTopArea.y = 0;
		leftTopArea.h = 175;
		leftTopArea.w = 640;

		bottomLeftArea.x = 0;
		bottomLeftArea.y = 410;
		bottomLeftArea.h = 70;
		bottomLeftArea.w = 160;

		screenArea = screen;

		background = new BoardPosition(screenArea, firstx, firsty, SCREEN_WIDTH, SCREEN_WIDTH, 0, STRBACK);
//		menu = new TopMenu(screenArea, firstx, firsty, SCREEN_WIDTH, 175, 500, 10, 120, 35, 14, 10, 110, 35, STRLEFTTOP, "TopHighlight2.bmp", "TopNew2.bmp");
		stopLight = new TopMenu(screenArea, SCREEN_WIDTH - 160, SCREEN_HEIGHT - 70, 125, 50, 0, 0, 0, 0, 0, 0, 0, 0, "rightBlack.bmp", "rightWhite.bmp");
		loadImage(STRBOTTOMLEFT, bottomLeft, bottomLeftArea);
		minitron = new ScoreBoard(11, 424, 125, 50, "arial.ttf", STRBLUEPIECE, STRREDPIECE, screenArea, backcolor, textcolor, 14);
		setPositions();

		setGamePiece(35, 1);
		setGamePiece(28, 1);
		setGamePiece(36, 0);
		setGamePiece(27, 0);
		

/*		setGamePiece(38, 1);
		setGamePiece(45, 1);
		setGamePiece(44, 0);
		setGamePiece(36, 0);
		setGamePiece(37, 1);
		setGamePiece(52, 1);
		setGamePiece(28, 0);
		setGamePiece(29, 0);
		setGamePiece(43, 1);
		setGamePiece(35, 1);
		setGamePiece(27, 0);
		setGamePiece(34, 1);*/
/*
	setGamePiece(62, 0);
	setGamePiece(61, 0);
	setGamePiece(60, 0);
	setGamePiece(59, 0);
	setGamePiece(58, 0);
	setGamePiece(53, 0);
	setGamePiece(52, 0);
	setGamePiece(48, 0);
	setGamePiece(47, 0);
	setGamePiece(45, 0);
	setGamePiece(43, 0);
	setGamePiece(41, 0);
	setGamePiece(40, 0);
	setGamePiece(39, 0);
	setGamePiece(37, 0);
	setGamePiece(36, 0);
	setGamePiece(33, 0);
	setGamePiece(32, 0);
	setGamePiece(31, 0);
	setGamePiece(28, 0);
	setGamePiece(25, 0);
	setGamePiece(24, 0);
	setGamePiece(23, 0);
	setGamePiece(16, 0);
	setGamePiece(10, 0);
	setGamePiece(9, 0);
	setGamePiece(8, 0);
	setGamePiece(7, 0);
	setGamePiece(6, 0);
	setGamePiece(5, 0);
	setGamePiece(4, 0);
	setGamePiece(3, 0);
	setGamePiece(2, 0);
	setGamePiece(0, 0);
	
	setGamePiece(54, 1);
	setGamePiece(51, 1);
	setGamePiece(50, 1);
	setGamePiece(46, 1);
	setGamePiece(44, 1);
	setGamePiece(42, 1);
	setGamePiece(38, 1);
	setGamePiece(35, 1);
	setGamePiece(34, 1);
	setGamePiece(30, 1);
	setGamePiece(29, 1);
	setGamePiece(27, 1);
	setGamePiece(26, 1);
	setGamePiece(22, 1);
	setGamePiece(21, 1);
	setGamePiece(20, 1);
	setGamePiece(19, 1);
	setGamePiece(18, 1);
	setGamePiece(17, 1);
	setGamePiece(15, 1);
	setGamePiece(14, 1);
	setGamePiece(13, 1);
	setGamePiece(12, 1);
	setGamePiece(11, 1);
*/
	setScore(2, 2);
	}
}


GameBoard::GameBoard(const GameBoard &g)
{

}


GameBoard& GameBoard::operator= (const GameBoard& g)
{
	return *this;
}

GameBoard::~GameBoard()
{
//	if(animator != 0)
//		delete animator;

	if(background != 0)
		delete background;

//	if(minitron != 0)
//		delete minitron;

//	if(menu != 0)
//		delete menu;

//	if(stopLight != 0)
//		delete stopLight;

//	if(leftTop != 0)
//		SDL_FreeSurface(leftTop);

//	if(rightTop != 0)
//		SDL_FreeSurface(rightTop);

//	if(bottomLeft != 0)
//		SDL_FreeSurface(bottomLeft);

	for(int i = 0; i != positions.size(); ++i)
		delete positions.at(i);
}


void GameBoard::setScore(int p1, int p2)
{
	minitron->setP1Score(p1);
	minitron->setP2Score(p2);
}



void GameBoard::setGamePiece(int index, int player)
{
	if(player == 0)
		positions[index]->setGamePiece(STRBLUEPIECE);
	else if(player == 1)
		positions[index]->setGamePiece(STRREDPIECE);
	else
		positions[index]->setGamePiece(STRPOSSIBLE);

	SDL_Flip(screenArea);
}


void GameBoard::highlight(int index, bool colorStatus, bool status)
{
	if(status)
		positions[index]->highlight(colorStatus);
	else
		positions[index]->clean();
}


void GameBoard::loadImage(string filename, SDL_Surface* surface, SDL_Rect area)
{
	int intSrcStatus;
	struct _stat buf;
	const char* srcfile = filename.c_str();
	
	if ((intSrcStatus = _stat(srcfile, &buf)) != 0)
	{
		cerr << "The source image " << filename << " does not exist.";
		exit(-1);
	}

	SDL_Surface* loadedImage = 0;

	loadedImage = SDL_LoadBMP(filename.c_str());

	if(loadedImage != 0)
	{
		if(surface != 0)
			SDL_FreeSurface(surface);
	
		surface = SDL_DisplayFormat(loadedImage);

		SDL_FreeSurface(loadedImage);
	}

	if(surface != 0)
	{
		Uint32 colorkey = SDL_MapRGB(surface->format, whiteRGB, whiteRGB, whiteRGB);
		SDL_SetColorKey(surface, SDL_SRCCOLORKEY, colorkey);
	}

	SDL_BlitSurface(surface, 0, screenArea, &area);
	SDL_Flip(screenArea);
}


void GameBoard::setPositions()
{
	positions.resize(BIT_DEPTH);
	int counter2 = BIT_DEPTH - 1;
	int temp0 = startx, temp1 = starty;

	for(int counter = BIT_DEPTH - 1; counter != -1; --counter)
	{
		positions.at(counter2) = new BoardPosition(screenArea, temp0, temp1, sizew, sizeh, 8, STRBOARDPIECE);
		temp0 += sizew;
		counter2 -= 1;
		
		if(counter % 8 == 0)
		{
			temp0 = startx;
			temp1 += sizeh;
		}
	}
}


void GameBoard::checkLink(int pos, int& x, int& y)
{
	bool result = false;
	for(x = 0; x < maxrows; ++x)
	{
		for(y = 0; y < maxcols; ++y)
		{
			result = posLink.at(x).at(y) == pos;
			if(result)
				break;
		}
		if(result)
			break;
	}
}


void GameBoard::refresh()
{
	for(int i = 0; i != maxPositions; ++i)
		if(positions[i] != 0)
			positions[i]->refresh();
}


int GameBoard::checkEvents(int x, int y, bitset<BIT_DEPTH> possibleMoves)
{
	for(int i = BIT_DEPTH - 1; i != -1; --i)
	{
		if (positions[i] != 0 && positions.at(i)->checkPosition(x, y) && possibleMoves[i] == 1)
		{
			return i;
		}
	}
	return -1;
}


int GameBoard::checkOverEvents(int x, int y)
{
//	return menu->checkPosition(x, y);
	return 1;
}


void GameBoard::clearHighlights(bitset<BIT_DEPTH> possibleMoves)
{
	for(int i = 0; i != BIT_DEPTH; ++i)
		if(positions[i] != 0 && possibleMoves[i] == 1)
			positions[i]->removePiece();
}


void GameBoard::removePiece(int x, int y)
{
	(*positions[posLink.at(x).at(y)]).removePiece();
}


void GameBoard::nextTurn(bool player)
{
	stopLight->highlight(player);
}


void GameBoard::showPossibleMoves(bitset<BIT_DEPTH> movesBoard)
{
	for(int counter = BIT_DEPTH - 1; counter != -1; --counter)
	{
		if(movesBoard[counter] == 1)
			setGamePiece(counter, 2);
	}
}


void GameBoard::displayBoard(bitset<BIT_DEPTH> blackBoard, bitset<BIT_DEPTH> whiteBoard, int blackScore, int whiteScore)
{
	for(int counter = BIT_DEPTH - 1; counter != -1; --counter)
	{;
		if (whiteBoard[counter] == 1)
			setGamePiece(counter, 0);
		else if(blackBoard[counter] == 1)
			setGamePiece(counter, 1);
	}
	setScore(blackScore, whiteScore);
}

