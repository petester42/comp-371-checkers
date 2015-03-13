/**
 *======================================================================
 *  Student#1: Angelo Pulcini		Student ID: 3946703
 *  Student#2: Jonathan Evans		Student ID: 5201713
 *  Course: COMP 472                Section:  Lec F
 *  Instructor: Sabine Bergler
 *  Assignment #2
 *  
 *  Description:
 *  This is the header file for the BoardPosition class.
 *  
 *======================================================================
 */
#ifndef BOARDPOSITION_H
#define BOARDPOSITION_H

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <string>

using namespace std;

class BoardPosition
{
public:
	explicit BoardPosition(SDL_Surface* screen = 0);
	BoardPosition(SDL_Surface* screen, int x, int y, int w, int h, int offset, string lowerImage = "", string upperImage = "");
	BoardPosition(const BoardPosition& b);
	virtual ~BoardPosition();
	void AttachSurface(SDL_Surface* screen);
	void setBitmap(string filename);
	void setGamePiece(string filename);
	void setPosition_x(int value);
	int getPosition_x();
	void setPosition_y(int value);
	int getPosition_y();
	void setWidth(int value);
	int getWidth();
	void setHeight(int value);
	int getHeight();
	void setRectArea(int x, int y, int w, int h);
	int* getRectArea();
	bool checkPosition(int x, int y);
	BoardPosition& operator= (const BoardPosition& b);
	void highlight(bool colorSelect);
	void refresh();
	void clean();
	void removePiece();

private:
	static const int defaultOffset = 8;
	static const int defaultSize = 50;
	static const int startPosition = 0;
	static const int extraOffset = 3;
	static const int extraOffsetCtor2 = 9;
	static const int extraWidthCtor2 = 27;
	static const Uint8 defaultAlpha = 255;
	static const Uint8 greenR = 0;
	static const Uint8 greenG = 255;
	static const Uint8 greenB = 0;
	static const Uint8 yellowR = 251;
	static const Uint8 yellowG = 254;
	static const Uint8 yellowB = 40;
	static const Uint8 blueR = 1;
	static const Uint8 blueG = 74;
	static const Uint8 blueB = 189;
	static const Uint8 blackRGB = 0;
	static const Uint8 whiteRGB = 255; 
	string lower;
	string upper;
	bool highlights;
	SDL_Surface* bitmap;
	SDL_Surface* screenArea;
	SDL_Surface* gamePiece;
	SDL_Rect area;
	SDL_Rect pieceArea;
	void loadImage(string filename, bool type);
};

#endif;
