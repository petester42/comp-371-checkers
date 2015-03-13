/**
 *======================================================================
 *  Student#1: Angelo Pulcini		Student ID: 3946703
 *  Student#2: Jonathan Evans		Student ID: 5201713
 *  Course: COMP 472                Section:  Lec F
 *  Instructor: Sabine Bergler
 *  Assignment #2
 *  
 *  Description:
 *  This is the implementation file for the ScoreBoard class.
 *  
 *======================================================================
 */
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "ScoreBoard.h"
#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <string>

using namespace std;

ScoreBoard::ScoreBoard(SDL_Surface* screen)
{
	if(screen != 0)
		screenArea = screen;

	fontSize = defaultFontSz;

	mainArea.x = defaultCoord;
	mainArea.y = defaultCoord;
	mainArea.w = defaultWidth;
	mainArea.h = defaultHeight;

	p1Score = 0;
	p2Score = 0;

	textColor.r = defaultTextC;
	textColor.g = defaultTextC;
	textColor.b = defaultTextC;

	backColor.r = defaultBackC;
	backColor.g = defaultBackC;
	backColor.b = defaultBackC;
	fontString = "arial.ttf";
	loadFont("arial.ttf");
	p1Image = 0;
	p2Image = 0;
	selectedFont = 0;
}


ScoreBoard::ScoreBoard(int x, int y, int w, int h, string fontName, string p1Icon, string p2Icon, SDL_Surface* screen, SDL_Color background, SDL_Color text, unsigned int font)
{
	if(screen != 0)
		screenArea = screen;

	selectedFont = 0;
	p1Image = 0;
	p2Image = 0;

	fontSize = font;
	fontString = fontName;

	if((x >= 0) && (y >= 0) && (w >= 0) && (h >= 0))
	{
		mainArea.x = x;
		mainArea.y = y;
		mainArea.w = w;
		mainArea.h = h;
	}

	p1Score = 0;
	p2Score = 0;

	textColor.r = text.r;
	textColor.g = text.g;
	textColor.b = text.b;
	backColor.r = background.r;
	backColor.g = background.g;
	backColor.b = background.b;
	loadFont(fontName);
	loadImage(p1Icon, true);
	loadImage(p2Icon, false);
	redraw();
}


ScoreBoard::ScoreBoard(const ScoreBoard& s)
{
	fontSize = s.fontSize;
	fontString = s.fontString;
	p1Score = s.p1Score;
	p2Score = s.p1Score;
	textColor.r = s.textColor.r;
	textColor.g = s.textColor.g;
	textColor.b = s.textColor.b;
	backColor.r = s.backColor.r;
	backColor.g = s.backColor.g;
	backColor.b = s.backColor.b;
	mainArea.x = s.mainArea.x;
	mainArea.y = s.mainArea.y;
	mainArea.w = s.mainArea.w;
	mainArea.h = s.mainArea.h;
	p1Area.x = s.p1Area.x;
	p1Area.y = s.p1Area.y;
	p1Area.w = s.p1Area.w;
	p1Area.h = s.p1Area.h;
	p2Area.x = s.p2Area.x;
	p2Area.y = s.p2Area.y;
	p2Area.w = s.p2Area.w;
	p2Area.h = s.p2Area.h;
	p1IconArea.x = s.p1IconArea.x;
	p1IconArea.y = s.p1IconArea.y;
	p1IconArea.w = s.p1IconArea.w;
	p1IconArea.h = s.p1IconArea.h;
	p2IconArea.x = s.p2IconArea.x;
	p2IconArea.y = s.p2IconArea.y;
	p2IconArea.w = s.p2IconArea.w;
	p2IconArea.h = s.p2IconArea.h;
	screenArea = s.screenArea;
	if(s.p1Image != 0)
		p1Image = SDL_DisplayFormat(s.p1Image);
	if(s.p2Image != 0)
		p2Image = SDL_DisplayFormat(s.p2Image);
	if(s.selectedFont != 0)
	{
		if(selectedFont)
			TTF_CloseFont(selectedFont);
		
		selectedFont = TTF_OpenFont(s.fontString.c_str(), s.fontSize);
	}
}


ScoreBoard::~ScoreBoard()
{
	SDL_FillRect(screenArea, &mainArea, SDL_MapRGB(screenArea->format, blackRGB, blackRGB, blackRGB));

	if(selectedFont)
	{
		TTF_CloseFont(selectedFont);
		TTF_Quit();
	}

	if(p1Image != 0)
		SDL_FreeSurface(p1Image);

	if(p2Image != 0)
		SDL_FreeSurface(p2Image);
}


ScoreBoard& ScoreBoard::operator= (const ScoreBoard& s)
{
	if(this != &s)
	{
		fontSize = s.fontSize;
		fontString = s.fontString;
		p1Score = s.p1Score;
		p2Score = s.p1Score;
		textColor.r = s.textColor.r;
		textColor.g = s.textColor.g;
		textColor.b = s.textColor.b;
		backColor.r = s.backColor.r;
		backColor.g = s.backColor.g;
		backColor.b = s.backColor.b;
		mainArea.x = s.mainArea.x;
		mainArea.y = s.mainArea.y;
		mainArea.w = s.mainArea.w;
		mainArea.h = s.mainArea.h;
		p1Area.x = s.p1Area.x;
		p1Area.y = s.p1Area.y;
		p1Area.w = s.p1Area.w;
		p1Area.h = s.p1Area.h;
		p2Area.x = s.p2Area.x;
		p2Area.y = s.p2Area.y;
		p2Area.w = s.p2Area.w;
		p2Area.h = s.p2Area.h;
		p1IconArea.x = s.p1IconArea.x;
		p1IconArea.y = s.p1IconArea.y;
		p1IconArea.w = s.p1IconArea.w;
		p1IconArea.h = s.p1IconArea.h;
		p2IconArea.x = s.p2IconArea.x;
		p2IconArea.y = s.p2IconArea.y;
		p2IconArea.w = s.p2IconArea.w;
		p2IconArea.h = s.p2IconArea.h;
		screenArea = s.screenArea;
		if(s.p1Image != 0)
			p1Image = SDL_DisplayFormat(s.p1Image);
		if(s.p2Image != 0)
			p2Image = SDL_DisplayFormat(s.p2Image);
		if(s.selectedFont != 0)
		{
			if(selectedFont)
				TTF_CloseFont(selectedFont);

			selectedFont = TTF_OpenFont(s.fontString.c_str(), s.fontSize);
		}
	}
	return *this;
}


int ScoreBoard::getPosition_x()
{
	return mainArea.x;
}


int ScoreBoard::getPosition_y()
{
	return mainArea.y;
}


int ScoreBoard::getPosition_w()
{
	return mainArea.w;
}


int ScoreBoard::getPosition_h()
{
	return mainArea.h;
}


void ScoreBoard::setFont(string fontName)
{
	fontString = fontName;
	if(selectedFont)
		TTF_CloseFont(selectedFont);
	TTF_Quit();
	loadFont(fontName);
	redraw();
}


void ScoreBoard::setBackColor(Uint8 red, Uint8 green, Uint8 blue)
{
	backColor.r = red;
	backColor.g = green;
	backColor.b = blue;
	redraw();
}


SDL_Color ScoreBoard::getBackColor()
{
	SDL_Color tempColor = {backColor.r, backColor.g, backColor.b};

	return tempColor;
}


void ScoreBoard::setTextColor(Uint8 red, Uint8 green, Uint8 blue)
{
	textColor.r = red;
	textColor.g = green;
	textColor.b = blue;
	redraw();
}


SDL_Color ScoreBoard::getTextColor()
{
	SDL_Color tempColor = {textColor.r, textColor.g, textColor.b};

	return tempColor;
}


void ScoreBoard::setP1Score(int value)
{
	if(value >= 0)
	{
		p1Score = value;
		redraw();
	}
}


int ScoreBoard::getP1Score()
{
	return p1Score;
}


void ScoreBoard::setP2Score(int value)
{
	if(value >= 0)
	{
		p2Score = value;
		redraw();
	}
}


int ScoreBoard::getP2Score()
{
	return p2Score;
}


void ScoreBoard::loadImage(string fileName, bool player)
{
	int intSrcStatus;
	struct stat buf;
	const char* srcfile = fileName.c_str();
	SDL_Surface* bitmap;

	if ((intSrcStatus = stat(srcfile, &buf)) != 0)
	{
		cerr << "The source image " << fileName << " does not exist.";
		exit(-1);
	}

	SDL_Surface* loadedImage = NULL;

	loadedImage = SDL_LoadBMP(fileName.c_str());

	if(loadedImage != 0)
	{
		if(player)
		{
			if(p2Image != 0)
				SDL_FreeSurface(p2Image);

			p2Image = SDL_DisplayFormat(loadedImage);
			bitmap = p2Image;
		}
		else
		{
			if(p1Image != 0)
				SDL_FreeSurface(p1Image);

			p1Image = SDL_DisplayFormat(loadedImage);
			bitmap = p1Image;
		}
		SDL_FreeSurface(loadedImage);
	}

	if(bitmap != 0)
	{
		Uint32 colorkey = SDL_MapRGB(bitmap->format, whiteRGB, whiteRGB, whiteRGB);
		SDL_SetColorKey(bitmap, SDL_SRCCOLORKEY, colorkey);
	}
}


void ScoreBoard::showIcons(bool player)
{
	if(player)
	{
		if(p2Image != 0)
		{
			p2IconArea.x = mainArea.w - (iconWidth + p1ExIconWidth);
			p2IconArea.y = mainArea.y + verticalSpace;
			p2IconArea.h = iconHeight;
			p2IconArea.w = iconWidth;
			SDL_BlitSurface(p2Image, 0, screenArea, &p2IconArea);
		}
	}
	else
	{
		if(p1Image != 0)
		{
			p1IconArea.x = mainArea.x + leftSpace;
			p1IconArea.y = mainArea.y + verticalSpace;
			p1IconArea.h = iconHeight;
			p1IconArea.w = iconWidth;	
			SDL_BlitSurface(p1Image, 0, screenArea, &p1IconArea);
		}
	}
}


void ScoreBoard::loadFont(string fontName)
{
	int intSrcStatus;
	struct _stat buf;
	fontString = fontName;
	const char* srcfile = fontName.c_str();

	if ((intSrcStatus = _stat(srcfile, &buf)) != 0)
	{
		cerr << "The source image " << fontName << " does not exist.";
		exit(-1);
	}

	if(TTF_Init() == -1)
	{
		exit(-1);
	}

	selectedFont = TTF_OpenFont(fontName.c_str(), fontSize);
}


void ScoreBoard::writeScore(bool player)
{
	if(selectedFont != 0)
	{
		ostringstream outs;
		SDL_Rect tempArea;
		string message;
		SDL_Color text = {blackRGB, blackRGB, blackRGB};
		SDL_Surface* tfontArea;

		if(player)
		{
			outs << p2Score;
			message = outs.str();
			p2Area.x = mainArea.w - p2RightSpace;
			p2Area.y = mainArea.y + topSpace;
			p2Area.h = scoreHeight;
			p2Area.w = p2ScoreWidth;
			tempArea = p2Area;
		}
		else
		{
			outs << p1Score;
			message = outs.str();
			p1Area.x = mainArea.x;
			p1Area.y = mainArea.y + topSpace;
			p1Area.h = scoreHeight;
			p1Area.w = p1ScoreWidth;
			tempArea = p1Area;
		}

		SDL_FillRect(screenArea, &tempArea, SDL_MapRGB(screenArea->format, backColor.r, backColor.g, backColor.b));

		tfontArea = TTF_RenderText_Solid(selectedFont, message.c_str(), textColor);

		SDL_BlitSurface(tfontArea, 0, screenArea, &tempArea);
		SDL_FreeSurface(tfontArea);
	}
}


void ScoreBoard::drawBackground()
{
	SDL_FillRect(screenArea, &mainArea, SDL_MapRGB(screenArea->format, backColor.r, backColor.g, backColor.b));
}


void ScoreBoard::redraw()
{
	drawBackground();
	writeScore(false);
	showIcons(false);
	writeScore(true);
	showIcons(true);
	SDL_Flip(screenArea);
}
