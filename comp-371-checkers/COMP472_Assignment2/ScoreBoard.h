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
#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#ifdef WIN32
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#pragma comment(lib, "SDL_ttf.lib")
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>

using namespace std;

class ScoreBoard
{
public:
	ScoreBoard(SDL_Surface* screen = 0);
	ScoreBoard::ScoreBoard(int x, int y, int w, int h, string fontName, string p1Icon, string p2Icon, SDL_Surface* screen, SDL_Color background, SDL_Color text, unsigned int font);
	~ScoreBoard();
	ScoreBoard& operator= (const ScoreBoard& s);
	int getPosition_x();
	int getPosition_y();
	int getPosition_w();
	int getPosition_h();
	void setFont(string fontName);
	string getFont();
	void setBackColor(Uint8 red, Uint8 green, Uint8 blue);
	SDL_Color getBackColor();
	void setTextColor(Uint8 red, Uint8 green, Uint8 blue);
	SDL_Color getTextColor();
	void setP1Score(int value);
	int getP1Score();
	void setP2Score(int value);
	int getP2Score();
	void redraw();

private:
	static const int defaultFontSz = 18;
	static const int defaultCoord = 0;
	static const int defaultWidth = 125;
	static const int defaultHeight = 125;
	static const Uint8 defaultTextC = 255;
	static const Uint8 defaultBackC = 0;
	static const int iconWidth = 45;
	static const int iconHeight = 52;
	static const int verticalSpace = 5;
	static const int leftSpace = 5;
	static const int topSpace = 2;
	static const int scoreHeight = 22;
	static const int p1ScoreWidth = 24;
	static const int p2ScoreWidth = 18;
	static const int p2RightSpace = 7;
	static const int p1ExIconWidth = 2;
	static const Uint8 blackRGB = 0;
	static const Uint8 whiteRGB = 255; 
	TTF_Font* selectedFont;
	int fontSize;
	string fontString;
	SDL_Color textColor;
	SDL_Color backColor;
	int p1Score;
	int p2Score;
	SDL_Surface* screenArea;
	SDL_Rect mainArea;
	SDL_Rect p1Area;
	SDL_Rect p1IconArea;
	SDL_Surface* p1Image;
	SDL_Rect p2Area;
	SDL_Rect p2IconArea;
	SDL_Surface* p2Image;
	void loadImage(string fileName, bool player);
	void showIcons(bool player);
	void loadFont(string fontName);
	void writeScore(bool player);
	void drawBackground();
	ScoreBoard(const ScoreBoard& s);
};

#endif;
