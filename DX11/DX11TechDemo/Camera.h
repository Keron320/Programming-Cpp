#include <d3d11.h>

#include <math.h>


#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT
#include <xnamath.h>
#pragma once


class Camera
{
private:

	XMVECTOR m_position;
	XMVECTOR m_lookat;
	XMVECTOR m_up;
public:
	Camera(float cX, float cY, float cZ, float cRotation);
	~Camera();

	float m_x, m_y, m_z, m_dx, m_dz, m_dy;
	float m_camera_rotationX;
	float m_camera_rotationY;

	void Rotate(float degrees);
	void Forward(float distance);
	void Strife(float distance);
	void Up();
	void MoveUpDown(float distance);
	void Pitch(float degrees);
	XMMATRIX GetViewMatrix();


};

