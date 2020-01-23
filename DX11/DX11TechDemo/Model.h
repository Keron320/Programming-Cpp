#pragma once
#include "objfilemodel.h"

class Model
{


private:
	
	ID3D11Device*			m_pD3DDevice;
	ID3D11DeviceContext*	m_pImmediateContext;

	ObjFileModel*			m_pObject;
	ID3D11VertexShader*		m_pVShader;	
	ID3D11PixelShader*		m_pPShader;
	ID3D11InputLayout*		m_pInputLayout;
	ID3D11Buffer*			m_pConstantBuffer;
	ID3D11VertexShader*		m_pVertexShader;
	ID3D11PixelShader*		m_pPixelShader;
	ID3D11ShaderResourceView* m_pTexture0;
	ID3D11SamplerState* m_pSampler0;
	D3D11_MAPPED_SUBRESOURCE ms;
	ObjFileModel* mObject;

	XMVECTOR m_directional_light_shines_from = XMVectorSet(0.0f, 1.0f, -1.0f, 0.0f);
	XMVECTOR m_directional_light_colour = XMVectorSet(0.6f, 0.3f, 1.0f, 0.0f);
	XMVECTOR m_ambient_light_colour = XMVectorSet(0.1f, 0.1f, 0.1f, 1.0f);

	XMMATRIX world;


	float	m_xAngle, m_yAngle, m_zAngle;
	float	m_scale, m_scale_x, m_scale_y, m_scale_z;

	int radians = 0;
	int degrees = 0;

	float m_bounding_sphere_centre_x;
	float m_bounding_sphere_centre_y;
	float m_bounding_sphere_centre_z;
	float m_bounding_sphere_radius;

	void CalculateModelCentrePoint();
	void CalculateBoundingSphereRadius();
	XMVECTOR GetBoundingSphereWorldSpacePosition();


public:
	Model(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext);
	HRESULT LoadObjModel(char* filename, char* texture);
	void Draw(XMMATRIX* view, XMMATRIX* projection);
	bool destinationReached = false;
	void setPos(int x,int y,int z);
	void setRotation(float angle);
	void setScale(float x, float y, float z);
	void patrol(int destination);
	float GetBoundingSphereRadius();
	float	m_x, m_y, m_z;
	bool CheckCollision(Model* myObj);
	~Model();
};

