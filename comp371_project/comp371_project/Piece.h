#pragma once

class Piece
{
	float x;
	float y;
	float z;
	bool color; //0 = black, 1 = red
	float height;
	int ID;
	bool queen;

public:
	Piece(void);
	Piece(bool _color, int _id, float _x, float _y, float _z);
	~Piece(void);

	void Draw(void);

	float getXPos();
	void setXPos(float _x);

	float getYPos();
	void setYPos(float _y);

	float getZPos();
	void setZPos(float _z);

	float getHeight();

	int getID();
	bool getColor();

	void setQueen(bool _queen);
};

