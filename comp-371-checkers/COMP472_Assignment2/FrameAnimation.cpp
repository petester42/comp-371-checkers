/**
 *======================================================================
 *  Student Name: Angelo Pulcini    Student ID: 3946703
 *  Course: COMP 446                Section:  Lec S
 *  Instructor: Rene Witte
 *  Course Project
 *  
 *  Description:
 *  This is the definition file for the FrameAnimation class.
 *  
 *======================================================================
 */
#include "FrameAnimation.h"
#include <iostream>
#include "SDL.h"
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>

using namespace std;

FrameAnimation::FrameAnimation(SDL_Surface *screen, string filename, int x, int y, int w, int h, const vector<int>& coordinates)
{
	if(screen != 0)
		screenArea = screen;

	position.x = x + XOFFSET;
	position.y = y;
	position.w = w;
	position.h = h;

	frames = 0;
	imageName = filename;
	setRegions(coordinates);
	loadImage();
}


FrameAnimation::FrameAnimation(const FrameAnimation& f)
{
	screenArea = f.screenArea;
	
	if(frames != 0)
		SDL_FreeSurface(frames);

	if(f.frames != 0)
		frames = SDL_DisplayFormat(f.frames);

	for(int i = 0; i != MAXFRAMES; ++i)
	{
		area[i].x = f.area[i].x;
		area[i].y = f.area[i].y;
		area[i].w = f.area[i].w;
		area[i].h = f.area[i].h;
	}

	position.x = f.position.x;
	position.y = f.position.y;
	position.w = f.position.w;
	position.h = f.position.h;

	imageName = f.imageName;
}


FrameAnimation::~FrameAnimation()
{
	if(frames != 0)
		SDL_FreeSurface(frames);
}


void FrameAnimation::animate()
{
	for(int i = 0; i != 4; ++i)
	{
		showFrame(i);
		SDL_Delay(150);
	}
}


FrameAnimation& FrameAnimation::operator= (const FrameAnimation& f)
{
	if(this != &f)
	{
		screenArea = f.screenArea;

		if(frames != 0)
			SDL_FreeSurface(frames);

		if(f.frames != 0)
			frames = SDL_DisplayFormat(f.frames);

		for(int i = 0; i != MAXFRAMES; ++i)
		{
			area[i].x = f.area[i].x;
			area[i].y = f.area[i].y;
			area[i].w = f.area[i].w;
			area[i].h = f.area[i].h;
		}

		position.x = f.position.x;
		position.y = f.position.y;
		position.w = f.position.w;
		position.h = f.position.h;

		imageName = f.imageName;
	}
	return *this;
}


void FrameAnimation::loadImage()
{
	int intSrcStatus;
	struct _stat buf;

	const char* srcfile = imageName.c_str();
	
	if ((intSrcStatus = _stat(srcfile, &buf)) != 0)
	{
		cerr << "The source image " << imageName << " does not exist.";
		exit(-1);
	}

	SDL_Surface* loadedImage = 0;

	loadedImage = SDL_LoadBMP(imageName.c_str());

	if(loadedImage != 0)
	{
		if(frames != 0)
			SDL_FreeSurface(frames);
	
		frames = SDL_DisplayFormat(loadedImage);

		SDL_FreeSurface(loadedImage);
	}

	if(frames != 0)
	{
		Uint32 colorkey = SDL_MapRGB(frames->format, whiteRGB, whiteRGB, whiteRGB);
		SDL_SetColorKey(frames, SDL_SRCCOLORKEY, colorkey);
	}
}


void FrameAnimation::setRegions(const vector<int>& coordinates)
{
	int count = 0;

	if(coordinates.size() == 16)
	{
		for(vector<int>::size_type i = 0; i != coordinates.size(); i += 4)
		{
			area[count].x = coordinates.at(i);
			area[count].y = coordinates.at(i + 1);
			area[count].w = coordinates.at(i + 2);
			area[count].h = coordinates.at(i + 3);
			++count;
		}
	}
}


void FrameAnimation::showFrame(int index)
{
	SDL_BlitSurface(frames, &area[index], screenArea, &position);
	SDL_Flip(screenArea);
}
