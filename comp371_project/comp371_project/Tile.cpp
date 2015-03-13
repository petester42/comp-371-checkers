#include "StdAfx.h"
#include "Tile.h"
#include "glm.h"

GLMmodel* redTile;
GLMmodel* blackTile;
GLMmodel* selectedTile;

Tile::Tile(void)
{
	redTile = NULL;
	blackTile = NULL;
	selectedTile = NULL;
	size = 56;
	height = 2;
	piece = NULL;
	selected = 0;
}

Tile::Tile(int _id,bool c, float x, float y, float z)
{
	ID = _id;
	redTile = NULL;
	blackTile = NULL;
	selectedTile = NULL;
	xpos = x;
	ypos = y;
	zpos = z;
	color = c;
	size = 56;
	height = 2;
	piece = NULL;
	selected = 0;
}

Tile::~Tile(void)
{
}

void Tile::setID(int _id){
	ID = _id;
}

Piece* Tile::getPiece(){
	return piece;
}

void Tile::setPiece(Piece *_piece){
	piece = _piece;
}

int Tile::getID(){
	return ID;
}

//int Tile::getPieceID()
//{
//	//add check for NULL
//	return pieceID;
//}

//void Tile::setPieceID(int ID)
//{
//	pieceID = ID;
//	piece = 1;
//}

void Tile::removePiece()
{
	piece = NULL;
	piece = 0;
}

bool Tile::checkPiece()
{
	if (piece != NULL)
		return 1;

	else
		return 0;
}

float Tile::getXPos()
{
	return xpos;
}

void Tile::setXPos(float x)
{
	xpos = x;
}

float Tile::getYPos()
{
	return ypos;
}

void Tile::setYPos(float y)
{
	ypos = y;
}

float Tile::getZPos()
{
	return zpos;
}

void Tile::setZPos(float z)
{
	zpos = z;
}

float Tile::getSize()
{
	return size;
}

float Tile::getHeight()
{
	return height;
}

bool Tile::getColor()
{
	return color;
}

bool Tile::getSelected()
{
	return selected;
}

void Tile::setSelected(bool _selected)
{
	selected = _selected;
}

GLfloat* Tile::getVerties()
{
	if(color = 0){
		return blackTile->vertices;
	}
	else{
		return redTile->vertices;
	}
}

void Tile::Draw(void)
{
	// Load the model only if it hasn't been loaded before
	// If it's been loaded then model should be a pointer to the model geometry data...otherwise it's null

	if (selected == 1){
		if (!selectedTile) 
		{
			// this is the call that actualy reads the OBJ and creates the model object
			selectedTile = glmReadOBJ("Models/SelectedTile.obj");
			if (!selectedTile) exit(0);

			glmFacetNormals(selectedTile);        
			//glmVertexNormals(blackTile,60);
		}

		glmDraw(selectedTile,GLM_SMOOTH|GLM_MATERIAL);
	}

	else {
		if (color == 0)
		{
			if (!blackTile) 
			{
				// this is the call that actualy reads the OBJ and creates the model object
				blackTile = glmReadOBJ("Models/BlackTile.obj");
				if (!blackTile) exit(0);

				glmFacetNormals(blackTile);        
				//glmVertexNormals(blackTile,60);
			}

			glmDraw(blackTile,GLM_SMOOTH|GLM_MATERIAL);
		}

		else {
			if (!redTile) 
			{
				// this is the call that actualy reads the OBJ and creates the model object
				redTile = glmReadOBJ("Models/RedTile.obj");
				if (!redTile) exit(0);

				glmFacetNormals(redTile);        
				//glmVertexNormals(redTile, 90.0);
			}

			glmDraw(redTile,GLM_SMOOTH|GLM_MATERIAL);
		}
	}
}
