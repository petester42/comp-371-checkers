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
#ifndef TOPMENU_H
#define TOPMENU_H

#ifdef WIN32
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#endif

#include <SDL/SDL.h>
#include <string>

using namespace std;

class TopMenu
{
public:
	TopMenu(SDL_Surface* screen, int x, int y, int w, int h, int x2, int y2, int w2, int h2, int x3, int y3, int w3, int h3, string highlightedIn, string highlightedIn2);
	TopMenu(const TopMenu& t);
	virtual ~TopMenu();
	int checkPosition(int x, int y);
	TopMenu& operator= (const TopMenu& b);
	void highlight(bool choice);
	void refresh();

private:
	static const int defaultOffset = 8;
	static const int defaultSize = 50;
	static const int startPosition = 0;
	static const Uint8 blackRGB = 0;
	static const Uint8 whiteRGB = 255; 
	string original;
	string highlighted;
	string highlightNew;
	bool highlightChoice;
	bool highNew;
	SDL_Surface* bitmap;
	SDL_Surface* screenArea;
	SDL_Rect area;
	SDL_Rect menu;
	SDL_Rect menu2;
	void loadImage();
};

#endif;
