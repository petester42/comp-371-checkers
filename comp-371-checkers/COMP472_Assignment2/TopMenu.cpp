/**
 *======================================================================
 *  Student#1: Angelo Pulcini		Student ID: 3946703
 *  Student#2: Jonathan Evans		Student ID: 5201713
 *  Course: COMP 472                Section:  Lec F
 *  Instructor: Sabine Bergler
 *  Assignment #2
 *  
 *  Description:
 *  This is the implementation file for the TopMenu class.
 *  
 *======================================================================
 */
#include <iostream>
#include <SDL/SDL.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include "TopMenu.h"

using namespace std;

TopMenu::TopMenu(SDL_Surface* screen, int x, int y, int w, int h, int x2, int y2, int w2, int h2, int x3, int y3, int w3, int h3, string highlightedIn, string highlightedIn2)
{
	if(screen != 0)
		screenArea = screen;

	bitmap = 0;
	highlighted = highlightedIn;
	highlightNew = highlightedIn2;
	highlightChoice = true;
	highNew = false;

	if((x >= 0) && (y >= 0) && (w >= 0) && (h >= 0))
	{
		area.x = x;
		area.y = y;
		area.w = w;
		area.h = h;
	}
	
	if((x2 >= 0) && (y2 >= 0) && (w2 >= 0) && (h2 >= 0))
	{
		menu.x = x2;
		menu.y = y2;
		menu.w = w2;
		menu.h = h2;
	}

	if((x3 >= 0) && (y3 >= 0) && (w3 >= 0) && (h3 >= 0))
	{
		menu2.x = x3;
		menu2.y = y3;
		menu2.w = w3;
		menu2.h = h3;
	}

	loadImage();
}


TopMenu::TopMenu(const TopMenu& t)
{
	SDL_FreeSurface(bitmap);
	if(t.bitmap != 0)
		bitmap = SDL_DisplayFormat(t.bitmap);
	if(t.screenArea != 0)
		screenArea = t.screenArea;

	highlighted = t.highlighted;
	highlightChoice = t.highlightChoice;
	highlightNew = t.highlightNew;
	highNew = t.highNew;
	area.x = t.area.x;
	area.y = t.area.y;
	area.w = t.area.w;
	area.h = t.area.w;
	menu.x = t.menu.x;
	menu.y = t.menu.y;
	menu.w = t.menu.w;
	menu.h = t.menu.w;
	menu2.x = t.menu2.x;
	menu2.y = t.menu2.y;
	menu2.w = t.menu2.w;
	menu2.h = t.menu2.w;

}


TopMenu::~TopMenu()
{
	highlighted = "";
	highlightNew = "";

	if(bitmap != 0)
		SDL_FreeSurface(bitmap);
}


int TopMenu::checkPosition(int x, int y)
{
	int temp;
	if((x > menu.x) && (x < menu.x + menu.w) && (y > menu.y) && (y < menu.y + menu.h))
	{
		highlight(true);
		temp = 1;
	}
	else if((x > menu2.x) && (x < menu2.x + menu2.w) && (y > menu2.y) && (y < menu2.y + menu2.h))
	{
		highlight(false);
		temp = 2;
	}

	return temp;
}


TopMenu& TopMenu::operator= (const TopMenu& t)
{
	if(this != &t)
	{
		SDL_FreeSurface(bitmap);

		if(t.bitmap != 0)
			bitmap = SDL_DisplayFormat(t.bitmap);

		if(t.screenArea != 0)
			screenArea = t.screenArea;

		highlighted = t.highlighted;
		highlightChoice = t.highlightChoice;
		highlightNew = t.highlightNew;
		highNew = t.highNew;
		area.x = t.area.x;
		area.y = t.area.y;
		area.w = t.area.w;
		area.h = t.area.w;
		menu.x = t.menu.x;
		menu.y = t.menu.y;
		menu.w = t.menu.w;
		menu.h = t.menu.w;
		menu2.x = t.menu2.x;
		menu2.y = t.menu2.y;
		menu2.w = t.menu2.w;
		menu2.h = t.menu2.w;
	}
	return *this;
}


void TopMenu::highlight(bool choice)
{
	highlightChoice = choice;
	loadImage();
}


void TopMenu::refresh()
{
	SDL_FillRect(screenArea, &area, SDL_MapRGB(screenArea->format, blackRGB, blackRGB, blackRGB));

	if((highlighted != "") && (highlightNew != "")) 
		loadImage();
}


void TopMenu::loadImage()
{
	string filename;
	int intSrcStatus;
	struct _stat buf;

	if(highlightChoice) 
		filename = highlighted;
	else
		filename = highlightNew;

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
		if(bitmap != 0)
			SDL_FreeSurface(bitmap);
	
		bitmap = SDL_DisplayFormat(loadedImage);

		SDL_FreeSurface(loadedImage);
	}

	if(bitmap != 0)
	{
		Uint32 colorkey = SDL_MapRGB(bitmap->format, whiteRGB, whiteRGB, whiteRGB);
		SDL_SetColorKey(bitmap, SDL_SRCCOLORKEY, colorkey);
	}

	SDL_BlitSurface(bitmap, 0, screenArea, &area);
	SDL_Flip(screenArea);
}
