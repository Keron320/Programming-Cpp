#include "Camera.h"

Camera::Camera(float cX, float cY, float cZ, float cRotation)
{
	m_camera_rotationX = cRotation;
	m_camera_rotationY = cRotation;
	m_x = cX;
	m_y = cY;
	m_z = cZ;

		
		m_dz = cos(m_camera_rotationY * (XM_PI / 180.0));
		m_dy = (float)sin(m_camera_rotationX * (XM_PI / 180.0));
		m_dx = sin(m_camera_rotationY * (XM_PI / 180.0));
}

Camera::~Camera()
{
}

void Camera::Rotate(float degrees)
{
	m_camera_rotationX += degrees;
	m_dx = sin(m_camera_rotationX * (XM_PI / 180.0));
	m_dz = cos(m_camera_rotationX * (XM_PI / 180.0));
}

void Camera::Forward(float distance)
{
	m_x += m_dx * distance;
	m_z += m_dz * distance;
}

void Camera::Strife(float distance)
{
	XMVECTOR direction = XMVector3Cross((m_position - m_lookat), (XMVECTOR{ 0.0f,1.0f + m_y, 0.0f, 0.0f } -m_position));
	m_x += direction.x * distance;
	m_z += direction.z * distance;
}

void Camera::MoveUpDown(float distance)
{
	m_y += m_dz * distance;
	m_z += m_dy * distance;
}

void Camera::Up()
{
	m_up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
}

void Camera::Pitch(float degrees)
{
	m_camera_rotationY += degrees;
	m_dy = sin(m_camera_rotationY * (XM_PI / 180.0));
	//m_dz = cos(m_camera_rotationX * (XM_PI / 180.0));
}


XMMATRIX Camera::GetViewMatrix()
{
	m_position = XMVectorSet(m_x, m_y, m_z, 0.0f);
	m_lookat = XMVectorSet(m_x + m_dx, m_y, m_z + m_dz, 0.0f);
	Up();
	return XMMatrixLookAtLH(m_position, m_lookat, m_up);
}
