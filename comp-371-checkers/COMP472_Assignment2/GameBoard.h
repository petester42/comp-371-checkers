#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <SDL/SDL.h>
#include "BoardPosition.h"
#include "ScoreBoard.h"
#include <string>
#include "TopMenu.h"
#include <vector>
#include <bitset>

using namespace std;

class GameBoard
{
private:
	static const int BIT_DEPTH = 64; 
	GameBoard(const GameBoard& g);
	GameBoard& operator= (const GameBoard& g);
	vector <vector<int> > posLink;
	vector<BoardPosition*> positions;
	BoardPosition* background;
	ScoreBoard* minitron;
	TopMenu* stopLight;
	SDL_Surface* leftTop;
	SDL_Surface* rightTop;
	SDL_Surface* bottomLeft;
	SDL_Rect leftTopArea;
	SDL_Rect rightTopArea;
	SDL_Rect bottomLeftArea;
	SDL_Surface* screenArea;
	static const int startx = 113; 
	static const int starty = 55;
	static const int sizew = 52;
	static const int sizeh = 45;
	static const int offset = -3;
	static const int xinc = 40;
	static const int ydec = 23;
	static const int rowcount = 5;
	static const int maxrows = 9;
	static const int maxcols = 17;
	static const int firstx = 0;
	static const int firsty = 0;
	static const int maxpositions = 60;
	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 480;
	static const int SCREEN_BPP = 32;
	static const int initialone = 0;
	static const int initialtwo = 4;
	static const int initialthree = 26;
	static const int initialfour = 34;
	static const int initialfive = 56;
	static const int initialsix = 60;
	static const Uint8 blackRGB = 0;
	static const Uint8 whiteRGB = 255;
	static const int maxPositions = 61;
	string STRPOSSIBLE;
	string STRREDPIECE;
	string STRBLUEPIECE;
	string STRBOARDPIECE;
	string STRBACK;
	string STRLEFTTOP;
	string STRLEFTTOPH;
	string STRBOTTOMLEFT;
	SDL_Color textcolor;
	SDL_Color backcolor;
	void setPositions();
	void checkLink(int pos, int& x, int& y); 

public:
	GameBoard(SDL_Surface* screen = 0);
	GameBoard(SDL_Surface* screen, int firstBlack, int firstWhite, int secondBlack, int secondWhite);
	virtual ~GameBoard();
	void setScore(int p1, int p2);
	void setGamePiece(int index, int player);
	void highlight(int index, bool colorStatus, bool status);
	void loadImage(string filename, SDL_Surface* surface, SDL_Rect area);
	void refresh();
	int checkEvents(int x, int y, bitset<BIT_DEPTH> possibleMoves);
	int checkOverEvents(int x, int y);
	void GameBoard::clearHighlights(bitset<BIT_DEPTH> possibleMoves);
	void removePiece(int x, int y);
	void nextTurn(bool player);
	void showPossibleMoves(bitset<BIT_DEPTH> movesBoard);
	void displayBoard(bitset<BIT_DEPTH> blackBoard, bitset<BIT_DEPTH> whiteBoard, int blackScore, int whiteScore);
//	void showAnimation(int x, int y, bool color);

};

#endif;
