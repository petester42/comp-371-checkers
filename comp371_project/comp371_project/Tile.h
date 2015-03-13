#pragma once
#include <GL\glut.h>
#include "Piece.h"
class Tile
{
	float xpos;
	float ypos;
	float zpos;
	bool color; //0 = black, 1 = red
	float size; //56
	float height;
	//int pieceID;
	bool selected;
	int ID;
	Piece *piece;
	/*GLMmodel* redTile;
	GLMmodel* blackTile;*/

public:
	Tile(void);
	Tile::Tile(int _id,bool c, float x, float y, float z);
	~Tile(void);

	void Draw(void);
	
	void setID(int _id);
	int getID();

	//int getPieceID();

	Piece *getPiece();
	void setPiece(Piece *_piece);

	//void setPieceID(int ID);
	void removePiece();

	bool checkPiece();

	bool getColor();
//	void setColor(bool c);

	float getSize();
	float getHeight();

	float getXPos();
	void setXPos(float x);

	float getYPos();
	void setYPos(float y);

	float getZPos();
	void setZPos(float z);

	bool getSelected();
	void setSelected(bool _selected);

	GLfloat* getVerties();
};

