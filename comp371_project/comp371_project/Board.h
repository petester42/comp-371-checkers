#pragma once
#include <vector>
#include "Tile.h"
#include "Piece.h"
#include <bitset>

using namespace std;

class Board
{
	float xpos;
	float ypos;
	float zpos;
	vector<Tile *>* tiles;
	vector<Piece *>* redPieces;
	vector<Piece *>* blackPieces;

public:
	Board(void);
	Board(bitset<64> black, bitset<64> red);
	~Board(void);

	void Draw(void);

	float getXPos();
	void setXPos(float x);

	float getYPos();
	void setYPos(float y);

	float getZPos();
	void setZPos(float z);

	vector<Tile *>* getTiles();
	vector<Piece *>* getRedPieces();
	vector<Piece *>* getBlackPieces();

	void movePiece(Piece *piece, Tile *tile);
	Tile* checkTile(float x, float y, float z);

	void highlightTiles(bitset<64> _tiles);
	void updatePieces(bitset<64> black, bitset<64> red);
private:
	void createTiles();
};

