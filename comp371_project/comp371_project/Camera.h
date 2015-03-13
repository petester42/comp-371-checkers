#pragma once
#include <math.h>

class Camera
{	
	float angleX;
	float angleY;
	float radius;
	float eyeX;
	float eyeY;
	float eyeZ;
	float targetX;
	float targetY;
	float targetZ;
	float upX;
	float upY;
	float upZ;

public:
	Camera(void);
	Camera(float eye_x, float eye_y, float eye_z, float target_x, float target_y, float target_z, float up_x, float up_y, float up_z);
	~Camera(void);

	void setRadius(float r);
	float getRadius();

	void setAngleX(float x);
	float getAngleX();

	void setAngleY(float y);
	float getAngleY();

	float getEyeX();
	void setEyeX(float eye_x);

	float getEyeY();
	void setEyeY(float eye_y);

	float getEyeZ();
	void setEyeZ(float eye_z);

	float getTargetX();
	void setTargetX(float target_x);

	float getTargetY();
	void setTargetY(float target_y);

	float getTargetZ();
	void setTargetZ(float target_z);

	float getUpX();
	void setUpX(float up_x);

	float getUpY();
	void setUpY(float up_y);

	float getUpZ();
	void setUpZ(float up_z);

	void rotate(float a1, float a2);
	void calculate();
	void moveEyes(float _x, float _y, float _z);
};

