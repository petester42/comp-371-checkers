#include "StdAfx.h"
#include "Camera.h"

Camera::Camera(void)
{
}

Camera::Camera(float eye_x, float eye_y, float eye_z, float target_x, float target_y, float target_z, float up_x, float up_y, float up_z){

	eyeX = eye_x;
	eyeY = eye_y;
	eyeZ = eye_z;
	targetX = target_x;
	targetY = target_y;
	targetZ = target_z;
	upX = up_x;
	upY = up_y; 
	upZ = up_z;
}

Camera::~Camera(void)
{
}

void Camera::setRadius(float r)
{
	radius = r;
}

float Camera::getRadius()
{
	return radius;
}

void Camera::setAngleX(float x)
{
	angleX = x;
}

float Camera::getAngleX()
{
	return angleX;
}

void Camera::setAngleY(float y)
{
	angleY = y;
}

float Camera::getAngleY()
{
	return angleY;
}


float Camera::getEyeX()
{
	return eyeX;
}

void Camera::setEyeX(float eye_x)
{
	eyeX = eye_x;
}

float Camera::getEyeY()
{
	return eyeY;
}

void Camera::setEyeY(float eye_y)
{
	eyeY = eye_y;
}

float Camera::getEyeZ()
{
	return eyeZ;
}

void Camera::setEyeZ(float eye_z)
{
	eyeZ = eye_z;
}

float Camera::getTargetX()
{
	return targetX;
}

void Camera::setTargetX(float target_x)
{
	targetX = target_x;
}

float Camera::getTargetY()
{
	return targetY;
}

void Camera::setTargetY(float target_y)
{
	targetY = target_y;
}

float Camera::getTargetZ()
{
	return targetZ;
}

void Camera::setTargetZ(float target_z)
{
	targetZ = target_z;
}

float Camera::getUpX()
{
	return upX;
}

void Camera::setUpX(float up_x)
{
	upX = up_x;
}

float Camera::getUpY()
{
	return upY;
}

void Camera::setUpY(float up_y)
{
	upY = up_y;
}

float Camera::getUpZ()
{
	return upZ;
}

void Camera::setUpZ(float up_z)
{
	upZ = up_z;
}

void Camera::rotate(float a1, float a2)
{
	angleX += a1;
	if(angleX == 360){
		angleX = 0;
	}

	if(angleX == 0){
		angleX = 360;
	}

	angleY += a2;
	if(angleY == 360){
		angleY = 0;
	}

	if(angleY == 0){
		angleY = 360;
	}
	calculate();
}

void Camera::calculate()
{
	eyeX = (radius * -sinf(angleX*(3.14/180)) * cosf((angleY)*(3.14/180))) + targetX;
	eyeY = (radius * -sinf((angleY)*(3.14/180))) + targetY;
	eyeZ = (-radius * cosf((angleX)*(3.14/180)) * cosf((angleY)*(3.14/180))) + targetZ;

	float lookx = eyeX - targetX;
	float looky = eyeY - targetY;
	float lookz = eyeZ - targetZ;

	float right[3] = {0,0,1};

	upX = right[1]*lookz - right[2]*looky;
	upY = right[2]*lookx - right[0]*lookz;
	upZ = right[0]*looky - right[1]*lookx;
}

void Camera::moveEyes(float _x, float _y, float _z)
{
	eyeX += _x;
	eyeY += _y;
	eyeZ += _z;
}