#ifndef FRAMEANIMATION_H
#define FRAMEANIMATION_H


#ifdef WIN32
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#endif

#include "SDL.h"
#include <string>
#include <vector>

using namespace std;

class FrameAnimation
{
public:
	FrameAnimation(SDL_Surface *screen, string filename, int x, int y, int w, int h, const vector<int>& coordinates);
	~FrameAnimation();
	FrameAnimation(const FrameAnimation& f);
	FrameAnimation& operator= (const FrameAnimation& f);
	void animate();

private:
	void loadImage();
	void setRegions(const vector<int>& coordinates);
	void showFrame(int index);
	SDL_Surface* screenArea;
	SDL_Surface* frames;
	SDL_Rect area[4];
	SDL_Rect position;
	string imageName;
	static const Uint8 whiteRGB = 255; 
	static const Uint8 blackRGB = 0;
	static const int FRAMES_PER_SECOND = 10;
	static const int MAXFRAMES = 4;
	static const int XOFFSET = 2;
};

#endif;
