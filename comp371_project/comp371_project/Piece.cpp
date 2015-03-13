#include "StdAfx.h"
#include "Piece.h"
#include "glm.h"

GLMmodel* redPiece;
GLMmodel* blackPiece;

GLMmodel* redPieceCrown;
GLMmodel* blackPieceCrown;

Piece::Piece(void)
{
	redPiece = NULL;
	blackPiece = NULL;
	redPieceCrown = NULL;
	blackPieceCrown = NULL;
	height = 10;
	queen = 0;
}

Piece::Piece(bool _color, int _id, float _x, float _y, float _z)
{
	redPiece = NULL;
	blackPiece = NULL;
	redPieceCrown = NULL;
	blackPieceCrown = NULL;
	color = _color;
	ID = _id;
	x = _x;
	y = _y;
	z = _z;
	height = 10;
	queen = 0;
}

Piece::~Piece(void)
{
}

float Piece::getXPos()
{
	return x;
}

void Piece::setXPos(float _x)
{
	x = _x;
}

float Piece::getYPos()
{
	return y;
}

void Piece::setYPos(float _y)
{
	y = _y;
}

float Piece::getZPos()
{
	return z;
}

void Piece::setZPos(float _z)
{
	z = _z;
}

int Piece::getID()
{
	return ID;
}

float Piece::getHeight(){
	return height;
}

bool Piece::getColor()
{
	return color;
}

void Piece::setQueen(bool _queen)
{
	queen = _queen;
}

void Piece::Draw(void)
{
	// Load the model only if it hasn't been loaded before
	// If it's been loaded then model should be a pointer to the model geometry data...otherwise it's null

	if (color == 0)
	{
		if (queen == 1)
		{
			if (!blackPieceCrown) 
			{
				// this is the call that actualy reads the OBJ and creates the model object
				blackPieceCrown = glmReadOBJ("Models/BlackPiece_Crown.obj");
				if (!blackPieceCrown) exit(0);

				glmFacetNormals(blackPieceCrown);        
				//glmVertexNormals(blackPiece, 90.0);
			}
			glmDraw(blackPieceCrown,GLM_SMOOTH|GLM_MATERIAL);
		}

		else 
		{
			if (!blackPiece) 
			{
				// this is the call that actualy reads the OBJ and creates the model object
				blackPiece = glmReadOBJ("Models/BlackPiece.obj");
				if (!blackPiece) exit(0);

				glmFacetNormals(blackPiece);        
				//glmVertexNormals(blackPiece, 90.0);
			}

			glmDraw(blackPiece,GLM_SMOOTH|GLM_MATERIAL);
		}
	}

	else {

		if (queen == 1)
		{
			if (!redPieceCrown) 
			{
				// this is the call that actualy reads the OBJ and creates the model object
				redPieceCrown = glmReadOBJ("Models/RedPiece_Crown.obj");
				if (!redPieceCrown) exit(0);

				glmFacetNormals(redPieceCrown);        
				//glmVertexNormals(blackPiece, 90.0);
			}
			glmDraw(redPieceCrown,GLM_SMOOTH|GLM_MATERIAL);
		}

		else 
		{
			if (!redPiece) 
			{
				// this is the call that actualy reads the OBJ and creates the model object
				redPiece = glmReadOBJ("Models/RedPiece.obj");
				if (!redPiece) exit(0);

				glmFacetNormals(redPiece);        
				//glmVertexNormals(redPiece, 90.0);
			}

			glmDraw(redPiece,GLM_SMOOTH|GLM_MATERIAL);
		}
	}
}
