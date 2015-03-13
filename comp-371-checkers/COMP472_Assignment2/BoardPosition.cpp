/**
 *======================================================================
 *  Student#1: Angelo Pulcini		Student ID: 3946703
 *  Student#2: Jonathan Evans		Student ID: 5201713
 *  Course: COMP 472                Section:  Lec F
 *  Instructor: Sabine Bergler
 *  Assignment #2
 *  
 *  Description:
 *  This is the implementation file for the BoardPosition class.
 *  
 *======================================================================
 */
#include "BoardPosition.h"
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

BoardPosition::BoardPosition(SDL_Surface* screen)
{
	screenArea = screen;

	area.x = startPosition;
	area.y = startPosition;
	area.w = defaultSize;
	area.h = defaultSize;

	pieceArea.x = area.x + defaultOffset;
	pieceArea.y = area.y + defaultOffset;
	pieceArea.w = area.w - defaultOffset + extraOffset;
	pieceArea.h = area.h - defaultOffset + extraOffset;
	lower = "";
	upper = "";
	bitmap = 0;
	gamePiece = 0;
	highlights = false;
}


BoardPosition::BoardPosition(SDL_Surface* screen, int x, int y, int w, int h, int offset, string lowerImage, string upperImage)
{
	if(screen != 0)
		screenArea = screen;

	bitmap = 0;
	gamePiece = 0;
	lower = "";
	upper = "";
	highlights = false;

	if((x >= 0) && (y >= 0) && (w >= 0) && (h >= 0))
	{
		area.x = x;
		area.y = y;
		area.w = w;
		area.h = h;

		pieceArea.x = area.x + offset + extraOffsetCtor2;
		pieceArea.y = area.y + offset;
		pieceArea.w = area.w - (offset + extraWidthCtor2);
		pieceArea.h = area.h - (offset + extraOffsetCtor2);
	}

	if(lowerImage != "")
	{
		lower = lowerImage;
		loadImage(lowerImage, 1);
	}

	if(upperImage != "")
	{
		upper = upperImage;
		loadImage(upperImage, 0);
	}
}


BoardPosition::BoardPosition(const BoardPosition& b)
{
	SDL_FreeSurface(bitmap);
	SDL_FreeSurface(gamePiece);
	if(b.bitmap != 0)
		bitmap = SDL_DisplayFormat(b.bitmap);
	if(b.screenArea != 0)
		screenArea = b.screenArea;
	if(b.gamePiece != 0)
		gamePiece = SDL_DisplayFormat(b.gamePiece);
	area.x = b.area.x;
	area.y = b.area.y;
	area.w = b.area.w;
	area.h = b.area.w;
	pieceArea.x = b.pieceArea.x;
	pieceArea.y = b.pieceArea.y;
	pieceArea.w = b.pieceArea.w;
	pieceArea.h = b.pieceArea.h;
}


BoardPosition::~BoardPosition()
{
	lower = "";
	SDL_FreeSurface(bitmap);
	upper = "";
	SDL_FreeSurface(gamePiece);
	refresh();
}


void BoardPosition::AttachSurface(SDL_Surface* screen)
{
	if(screen != 0)
		screenArea = screen;
}


void BoardPosition::setBitmap(string filename)
{
	if(filename != "")
	{
		lower = filename;
		loadImage(lower, 1);
	}
}


void BoardPosition::setGamePiece(string filename)
{
	if(filename != "")
	{
		upper = filename;
		loadImage(upper, 0);
	}
}


void BoardPosition::setPosition_x(int value)
{
	if(value >= 0)
		area.x = value;
}


int BoardPosition::getPosition_x()
{
	return area.x;
}


void BoardPosition::setPosition_y(int value)
{
	if(value >= 0)
		area.y = value;
}


int BoardPosition::getPosition_y()
{
	return area.y;
}


void BoardPosition::setWidth(int value)
{
	if(value >= 0)
		area.w = value;
}


int BoardPosition::getWidth()
{
	return area.w;
}


void BoardPosition::setHeight(int value)
{
	if(value >= 0)
		area.h = value;
}


int BoardPosition::getHeight()
{
	return area.h;
}


void BoardPosition::setRectArea(int x, int y, int w, int h)
{
	if((x >= 0) && (y >= 0) && (w >= 0) && (h >= 0))
	{
		area.x = x;
		area.y = y;
		area.w = w;
		area.h = h;
	}
}


int* BoardPosition::getRectArea()
{
	int* temp = new int[4];

	temp[0] = area.x;
	temp[1] = area.y;
	temp[2] = area.w;
	temp[3] = area.h;

	return temp;
}


bool BoardPosition::checkPosition(int x, int y)
{
	return ((x > pieceArea.x) && (x < pieceArea.x + pieceArea.w) && (y > pieceArea.y) && (y < pieceArea.y + pieceArea.h));
}


void BoardPosition::loadImage(string filename, bool type)
{
	int intSrcStatus;
	struct _stat buf;
	const char* srcfile = filename.c_str();
	SDL_Surface* temp;
	SDL_Rect tempArea;
	
	if ((intSrcStatus = _stat(srcfile, &buf)) != 0)
	{
		cerr << "The source image " << filename << " does not exist.";
		exit(-1);
	}

	SDL_Surface* loadedImage = 0;

	loadedImage = SDL_LoadBMP(filename.c_str());

	if(loadedImage != 0)
	{
		if(type)
		{
			if(bitmap != 0)
				SDL_FreeSurface(bitmap);
	
			bitmap = SDL_DisplayFormat(loadedImage);
			temp = bitmap;
			tempArea.x = area.x;
			tempArea.y = area.y;
			tempArea.w = area.w;
			tempArea.h = area.h;
		}
		else
		{
			if(gamePiece != 0)
				SDL_FreeSurface(gamePiece);

			gamePiece = SDL_DisplayFormat(loadedImage);
			temp = gamePiece;
			tempArea.x = area.x;
			tempArea.y = area.y;
			tempArea.w = area.w;
			tempArea.h = area.h;

			if(highlights)
				highlights = false;
		}

		SDL_FreeSurface(loadedImage);
	}

	if(bitmap != 0)
	{
		Uint32 colorkey = SDL_MapRGB(temp->format, whiteRGB, whiteRGB, whiteRGB);
		SDL_SetColorKey(temp, SDL_SRCCOLORKEY, colorkey);
	}

	SDL_BlitSurface(temp, 0, screenArea, &tempArea);
	SDL_Flip(screenArea);
}


BoardPosition& BoardPosition::operator= (const BoardPosition& b)
{
	if(this != &b)
	{
		SDL_FreeSurface(bitmap);
		SDL_FreeSurface(gamePiece);
		if(b.bitmap != 0)
			bitmap = SDL_DisplayFormat(b.bitmap);
		if(b.screenArea != 0)
			screenArea = b.screenArea;
		if(b.gamePiece != 0)
			gamePiece = SDL_DisplayFormat(b.gamePiece);
		area.x = b.area.x;
		area.y = b.area.y;
		area.w = b.area.w;
		area.h = b.area.w;
		pieceArea.x = b.pieceArea.x;
		pieceArea.y = b.pieceArea.y;
		pieceArea.w = b.pieceArea.w;
		pieceArea.h = b.pieceArea.h;
	}
	return *this;
}


void BoardPosition::highlight(bool colorSelect)
{
	if(colorSelect)
		rectangleRGBA(screenArea, pieceArea.x, pieceArea.y, pieceArea.x + pieceArea.w, pieceArea.y + pieceArea.h, greenR, greenG, greenB, defaultAlpha);
	else
		rectangleRGBA(screenArea, pieceArea.x, pieceArea.y, pieceArea.x + pieceArea.w, pieceArea.y + pieceArea.h, yellowR, yellowG, yellowB, defaultAlpha);

	SDL_Flip(screenArea);
}


void BoardPosition::refresh()
{
	SDL_FillRect(screenArea, &area, SDL_MapRGB(screenArea->format, blackRGB, blackRGB, blackRGB));

	if(lower != "")
		loadImage(lower, 1);

	if(upper != "")
		loadImage(upper, 0);
}


void BoardPosition::clean()
{
	if(gamePiece == 0)
	{
		rectangleRGBA(screenArea, pieceArea.x, pieceArea.y, pieceArea.x + pieceArea.w, pieceArea.y + pieceArea.h, greenR, greenG, greenB, 0);
		SDL_Flip(screenArea);
	}
}


void BoardPosition::removePiece()
{
	if(gamePiece != 0)
	{
		SDL_FreeSurface(gamePiece);
		gamePiece = 0;
		upper = "";
		loadImage(lower, true);
	}
}