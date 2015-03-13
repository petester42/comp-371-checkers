#include "stdafx.h"
#include "comp371_project.h"

Board *board = NULL;
Camera *camera = NULL;

gameLogic* model;
bool quit = false;
bool update = false;
bitset<64> black;
bitset<64> white;
bitset<64> intendedMove;
bitset<64> emptyBoard;
bitset<64> possibleMoves;

bool showWireFrame = 0;
int piece = NULL;

GLfloat light0Position[] = {460/2, 300.0f, -460/2, 1.0f};
GLfloat light1Position[4];
GLfloat spotCutoff1[1] = {50};
GLfloat spotDirection1[3];
float angleX = 90;
float angleY = 230;
float radius = 300;
float zoomFactor = 1.0;


void output(bitset<64> board)
{
	for(int counter = 0; counter != 64; ++counter)
	{
		cout << board[counter];

		if((counter != 0) && (counter % 8 == 0))
			cout << endl;
	}
}


bitset<64> convertBitset(bitset<64> input)
{
	int inner = 63;
	bitset<64> output;

	for(int outer = 0; outer != 64; ++outer)
	{
		output[inner] = input[outer];
		inner -= 1;
	}

	return output;
}


void init(void) 
{
	glClearColor (0.4, 0.4, 0.4, 1.0);   
	glEnable(GL_DEPTH_TEST);
	glShadeModel (GL_SMOOTH);
	//glutFullScreen();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
}

void redraw(void)
{
	GLfloat params[4]; 

	glGetFloatv(GL_VIEWPORT,params);

	GLfloat w = params[2];
	GLfloat h = params[3];

	reshape(w,h);

	glutPostRedisplay();
}

void light0(void)
{
	// Create light components
	GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
	GLfloat diffuseLight[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat specularLight[] = {0.5f, 0.5f, 0.5f, 1.0f};

	GLfloat constantAttenuation = 1.0;
	GLfloat linearAttenuation = 0.0;
	GLfloat quadraticAttenuation = 0.0;

	GLfloat spotCutoff = 90.0;
	GLfloat spotDirection[] = {0,-1,0};
	GLfloat spotExponent = 0.0;

	//set light components
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, constantAttenuation);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, linearAttenuation);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);

	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotCutoff);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent);

	glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
	//enable light
	glEnable(GL_LIGHT0);
}

void light1(void)
{
	// Create light components
	GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat diffuseLight[] = {0.8f, 0.8f, 0.8, 1.0f};
	GLfloat specularLight[] = {0.5f, 0.5f, 0.5f, 1.0f};

	GLfloat constantAttenuation = 1.0;
	GLfloat linearAttenuation = 0.0;
	GLfloat quadraticAttenuation = 0.0;

	GLfloat spotCutoff = spotCutoff1[0];
	GLfloat spotDirection[] = {spotDirection1[0],spotDirection1[1],spotDirection1[2]};
	GLfloat spotExponent = 1.0;

	//set light components
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);

	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, constantAttenuation);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, linearAttenuation);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotCutoff);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spotExponent);

	glLightfv(GL_LIGHT1, GL_POSITION, light1Position);
	//enable light
	glEnable(GL_LIGHT1);
}

void reshape (int w, int h)
{
	glViewport(0,0,(GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0*zoomFactor, (GLfloat)w/(GLfloat)h, 0.1, 5000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

vector<float> GetOGLPos(int x, int y)
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

	gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

	vector<float> pos;
	pos.push_back(posX);
	pos.push_back(posY);
	pos.push_back(posZ);

	return pos;
}

void keyboard(unsigned char key, int x, int y)
{
	//use wasd to rotate camera around board
	//use arrows to move light

	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'w'|'W':
		camera->rotate(0,1);
		break;
	case 'a'|'A':
		camera->rotate(-1,0);
		break;
	case 's'|'S':	
		camera->rotate(0,-1);
		break;
	case 'd'|'D':
		camera->rotate(1,0);
		break;
	case 'q'|'Q':
		zoomFactor += 0.1;
		break;
	case 'e'|'E':
		zoomFactor -= 0.1;
		break;
	case 't'|'T':
		if(showWireFrame == 0)
			showWireFrame = 1;
		else
			showWireFrame = 0;
		break;
	}
}

void arrows (int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		angleY += 1;
		if(angleY == 360)
			angleY = 0;
		break;
	case GLUT_KEY_LEFT:
		angleX -= 1;
		if(angleX == 0)
			angleX = 360;
		break;
	case GLUT_KEY_DOWN:	
		angleY -= 1;
		if(angleY == 0)
			angleY = 360;
		break;
	case GLUT_KEY_RIGHT:
		angleX += 1;
		if(angleX == 360)
			angleX = 0;
		break;
	}

	calculateLight();
}

void mouse(int button, int state, int x, int y)
{
	switch(button){
	case GLUT_LEFT_BUTTON:
		if(state == GLUT_DOWN){

			vector<float> pos = GetOGLPos(x,y);

			Tile *tile = board->checkTile(pos.at(0), pos.at(1), pos.at(2));

			if (model->getTurn() == 0 && tile != NULL)
			{
				if(possibleMoves[tile->getID()] == 1)
				{
					intendedMove.set(tile->getID());
					bitset<64> originalPos;
					originalPos.set(piece);
					model->performMove(model->getTurn(), intendedMove, originalPos);
					board->updatePieces(convertBitset(model->getWhiteBoard()), convertBitset(model->getBlackBoard()));

					intendedMove = emptyBoard;
					piece = NULL;
					board->highlightTiles(emptyBoard);
					possibleMoves = emptyBoard;
				}

				else
				{
					if (tile->checkPiece() == 1 && tile->getPiece()->getColor() == 1)
					{
						piece = tile->getID();
						possibleMoves = model->generateAcceptedMoves(model->getTurn(), tile->getID());

						board->highlightTiles(possibleMoves);
					}

					else 
					{
						piece = NULL;
						board->highlightTiles(emptyBoard);
						possibleMoves = emptyBoard;
					}
				}
			}


			else if (model->getTurn() == 1 && tile != NULL){

				if(possibleMoves[tile->getID()] == 1)
				{
					intendedMove.set(tile->getID());
					bitset<64> originalPos;
					originalPos.set(piece);
					model->performMove(model->getTurn(), intendedMove, originalPos);
					board->updatePieces(convertBitset(model->getWhiteBoard()), convertBitset(model->getBlackBoard()));

					intendedMove = emptyBoard;
					piece = NULL;
					board->highlightTiles(emptyBoard);
					possibleMoves = emptyBoard;
				}

				else{
					if (tile->checkPiece() == 1 && tile->getPiece()->getColor() == 0)
					{
						piece = tile->getID();
						possibleMoves = model->generateAcceptedMoves(model->getTurn(), tile->getID());
						board->highlightTiles(possibleMoves);
					}

					else {
						piece = NULL;	
						board->highlightTiles(emptyBoard);
						possibleMoves = emptyBoard;
					}
				}
			}
		}

		break;
	}
}

void Draw_Axes (void)
{
	glDisable(GL_LIGHTING);
	glPushMatrix ();

	glLineWidth (2.0);

	glBegin (GL_LINES);
	glColor3f (1,0,0); // X axis is red.
	glVertex3f (0,0,0);
	glVertex3f (500,0,0); 
	glVertex3f (0,0,0);
	glVertex3f (-500,0,0); 
	glColor3f (0,1,0); // Y axis is green.
	glVertex3f (0,0,0);
	glVertex3f (0,500,0);
	glVertex3f (0,0,0);
	glVertex3f (0,-500,0);
	glColor3f (0,0,1); // z axis is blue.
	glVertex3f (0,0,0);
	glVertex3f (0,0,500); 
	glVertex3f (0,0,0);
	glVertex3f (0,0,-500); 

	glColor3f (0,0,1); // z axis is blue.
	glVertex3f (light1Position[0],light1Position[1],light1Position[2]);
	glVertex3f ((light1Position[0]+20*spotDirection1[0]),(light1Position[1]+20*spotDirection1[1]),(light1Position[2]+20*spotDirection1[2]));  
	glEnd();

	glPopMatrix ();
	glEnable(GL_LIGHTING);
}

void resetColor()
{
	glColor3f(1.0,1.0,1.0);
}

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	gluLookAt(camera->getEyeX(), camera->getEyeY(), camera->getEyeZ(), camera->getTargetX(), camera->getTargetY(), camera->getTargetZ(), camera->getUpX(), camera->getUpY(), camera->getUpZ());

	glEnable(GL_LIGHTING);

	glPushMatrix();
	glScalef(0.9965,1.0,0.9963);
	board->Draw();
	glPopMatrix();
	resetColor();

	for (unsigned int i=0; i < board->getTiles()->size(); ++i){

		glPushMatrix();
		Tile *tile = board->getTiles()->at(i);
		glTranslatef(tile->getXPos(),tile->getYPos(),tile->getZPos());
		tile->Draw();
		glPopMatrix();
		resetColor();
	}

	for (unsigned int j=0; j < board->getRedPieces()->size(); ++j){

		glPushMatrix();
		Piece *piece = board->getRedPieces()->at(j);
		glTranslatef(piece->getXPos(),piece->getYPos(),piece->getZPos());
		glRotatef(90,0,1,0);
		piece->Draw();
		glPopMatrix();
		resetColor();
	}

	for (unsigned int j=0; j < board->getBlackPieces()->size(); ++j){

		glPushMatrix();
		Piece *piece = board->getBlackPieces()->at(j);
		glTranslatef(piece->getXPos(),piece->getYPos(),piece->getZPos());
		glRotatef(-90,0,1,0);
		piece->Draw();
		glPopMatrix();
		resetColor();
	}

	if (showWireFrame == 1){
	//remove after testing
	Draw_Axes();
	resetColor();

	//remove after testing
	glDisable(GL_LIGHTING);
	glColor3f(0.0,1.0,0.0);
	glPushMatrix();
	glTranslatef(light0Position[0], light0Position[1], light0Position[2]);
	glutWireCube (25.0);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	resetColor();

	//remove after testing
	glDisable(GL_LIGHTING);
	glColor3f(0.0,0.0,1.0);
	glPushMatrix();
	glTranslatef(light1Position[0], light1Position[1], light1Position[2]);
	glutWireCube (25.0);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	resetColor();
	}

	glPushMatrix();
	light0();
	glPopMatrix();

	glPushMatrix();
	light1();
	glPopMatrix();

	glutSwapBuffers();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow(argv[0]);

	init();

	model = new gameLogic();

	board = new Board(model->getBlackBoard(), model->getWhiteBoard());

	float targetX = board->getXPos() + 460/2;
	float targetY = board->getYPos() + 5;
	float targetZ = board->getZPos() - 460/2;
	float eyeX = targetX;
	float eyeY = targetY;
	float eyeZ = targetZ;
	float upX = 0;
	float upY = 0;
	float upZ = 0;

	camera = new Camera(eyeX,eyeY,eyeZ,targetX,targetY,targetZ,upX,upY,upZ);
	camera->setRadius(350);
	camera->setAngleX(90);
	camera->setAngleY(230);
	camera->calculate();

	calculateLight();

	glutIdleFunc(redraw);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrows);

	glutMainLoop();
	return 0;
}

void calculateLight()
{
	light1Position[0] = (radius * -sinf(angleX*(3.14/180)) * cosf((angleY)*(3.14/180)))+ camera->getTargetX();
	light1Position[1] = (radius * -sinf((angleY)*(3.14/180))) + camera->getTargetY();
	light1Position[2] = (-radius * cosf((angleX)*(3.14/180)) * cosf((angleY)*(3.14/180)) + camera->getTargetZ());

	spotDirection1[0] = camera->getTargetX() - light1Position[0];
	spotDirection1[1] = camera->getTargetY() - light1Position[1];
	spotDirection1[2] = camera->getTargetZ() - light1Position[2];

	float magnitude = abs(sqrt((spotDirection1[0] * spotDirection1[0]) + (spotDirection1[1] * spotDirection1[1]) + (spotDirection1[2] * spotDirection1[2])));
	
	spotDirection1[0] = spotDirection1[0]/magnitude;
	spotDirection1[1] = spotDirection1[1]/magnitude;
	spotDirection1[2] = spotDirection1[2]/magnitude;
}