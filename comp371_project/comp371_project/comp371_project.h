#pragma once
#include <vector>
#include <GL\glut.h>
#include "Board.h"
#include "Camera.h"
#include "gameLogic.h"
#include <tchar.h>
#include <Windows.h>
#include <math.h>
#include <iostream>
using namespace std;

void init(void);
void redraw(void);
void light0(void);
void light1(void);
void reshape (int w, int h);
void motion (int x, int y);
void arrows (int key, int x, int y);
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void Draw_Axes (void);
void resetColor();
vector<float> GetOGLPos(int x, int y);
void calculateLight();