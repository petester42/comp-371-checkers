#include "StdAfx.h"
#include "Board.h"
#include "glm.h"

#include <iostream>

GLMmodel* board;

Board::Board(void)
{
	board = NULL;
	xpos = 0;
	ypos = 0;
	zpos = 0;
	tiles = new vector<Tile *>();
	redPieces = new vector<Piece *>();
	blackPieces = new vector<Piece *>();

	createTiles();
}

Board::Board(bitset<64> black, bitset<64> red)
{
	board = NULL;
	xpos = 0;
	ypos = 0;
	zpos = 0;
	tiles = new vector<Tile *>();
	redPieces = new vector<Piece *>();
	blackPieces = new vector<Piece *>();

	createTiles();
	updatePieces(black, red);
}

Board::~Board(void)
{
	for(unsigned int i = 0; i < tiles->size(); ++i)
		delete tiles->at(i);

	for(unsigned int j = 0; j < redPieces->size(); ++j)
		delete redPieces->at(j);

	for(unsigned int w = 0; w < blackPieces->size(); ++w)
		delete blackPieces->at(w);

	delete tiles;
	delete redPieces;
	delete blackPieces;
}

float Board::getXPos()
{
	return xpos;
}

void Board::setXPos(float x)
{
	xpos = x;
}

float Board::getYPos()
{
	return ypos;
}

void Board::setYPos(float y)
{
	ypos = y;
}

float Board::getZPos()
{
	return zpos;
}

void Board::setZPos(float z)
{
	zpos = z;
}

vector<Tile *>* Board::getTiles()
{
	return tiles;
}

void Board::createTiles(){
	//height off board = 10
	//corner of board is x = 7, z = -6
	//size of tile is 56
	//red/black/red/black
	int initialX = 7;
	int initialY = 10;
	int initialZ = -6;
	int size = 56;
	int column = 0;
	bool color = 1;

	for (int i = 0; i < 64; ++i){

		int row = i/8;

		if (i%8 == 0){
			column = 0;
		}

		else {
			column++;

			if (color == 1){
				color = 0;
			}

			else {
				color = 1;
			}
		}		

		Tile *tile = new Tile(i,color, initialX + row*size, initialY, initialZ - column*size);
		tiles->push_back(tile);	
	}
}

vector<Piece *>* Board::getBlackPieces()
{
	return blackPieces;
}

vector<Piece *>* Board::getRedPieces()
{
	return redPieces;
}


void Board::updatePieces(bitset<64> black, bitset<64> red)
{
	//maybe say the tile id where the pieces are

	blackPieces->clear();
	redPieces->clear();

	for (unsigned int i = 0; i < black.size(); ++i)
	{
		if (black[i] == 0){
			continue;
		}

		Tile *tile = tiles->at(i);
		
		Piece *piece = new Piece(0,i,tile->getXPos() + tile->getSize()/2,tile->getYPos()+3, tile->getZPos() - tile->getSize()/2);

		tile->setPiece(piece);
		blackPieces->push_back(piece);
	}

	for (unsigned int j = 0; j < red.size(); ++j)
	{
		if (red[j] == 0){
			continue;
		}

		Tile *tile = tiles->at(j);
	
		Piece *piece = new Piece(1, j, tile->getXPos() + tile->getSize()/2, tile->getYPos()+3, tile->getZPos() - tile->getSize()/2);
		tile->setPiece(piece);
		redPieces->push_back(piece);
	}
}

void Board::highlightTiles(bitset<64> _tiles){

	for (unsigned int i = 0; i < _tiles.size(); ++i)
	{
		tiles->at(i)->setSelected(_tiles[i]);
	}
}

void Board::movePiece(Piece *piece, Tile *tile)
{
	float x = tile->getXPos() + tile->getSize()/2;
	float y = tile->getYPos()+3;
	float z = tile->getZPos() - tile->getSize()/2;

	piece->setXPos(x);
	piece->setYPos(y);
	piece->setZPos(z);
}

Tile* Board::checkTile(float x, float y, float z)
{

	for (unsigned int i = 0; i < tiles->size(); ++i)
	{
		Tile *tile = tiles->at(i);
		Piece piece;

		int xMin = tile->getXPos();
		int xMax = tile->getXPos() + tile->getSize();
		int yMin = tile->getYPos();
		int yMax = tile->getYPos() + tile->getHeight() + piece.getHeight();
		int zMax = tile->getZPos();
		int zMin = tile->getZPos() - tile->getSize();

		if (x>xMin && x<xMax && y>yMin && y<yMax && z>zMin && z<zMax){
			//tile->setSelected(1);
			return tile;
		}
		
	}

	return NULL;
}

void Board::Draw(void)
{
	// Load the model only if it hasn't been loaded before
	// If it's been loaded then model should be a pointer to the model geometry data...otherwise it's null
	if (!board) 
	{
		// this is the call that actualy reads the OBJ and creates the model object
		board = glmReadOBJ("Models/Board.obj");	
		if (!board) exit(0);

		glmFacetNormals(board);        
		glmVertexNormals(board,90);
	}
	
	glmDraw(board,GLM_SMOOTH|GLM_TEXTURE|GLM_MATERIAL);
}