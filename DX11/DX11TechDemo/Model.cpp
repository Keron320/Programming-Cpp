#include "Model.h"
#include <math.h> 
struct MODEL_CONSTANT_BUFFER
{
	XMMATRIX WorldViewProjection; // 64 bytes
	XMVECTOR directional_light_vector;//  16 bytes
	XMVECTOR directional_light_colour;//  16 bytes
	XMVECTOR ambient_light_colour;	//  16 bytes
	//Total byte 112
};



	void Model::Draw(XMMATRIX* view, XMMATRIX* projection)
	{
		world = XMMatrixTranslation(m_scale, m_scale, m_scale);
		world = XMMatrixScaling(m_scale_x, m_scale_y, m_scale_z);
		world *= XMMatrixRotationY(XMConvertToRadians(radians));
		world *= XMMatrixRotationZ(XMConvertToDegrees(degrees));
		world *= XMMatrixTranslation(m_x, m_y, m_z);

		MODEL_CONSTANT_BUFFER model_cb_values;
		model_cb_values.WorldViewProjection = world * (*view) * (*projection);

		XMMATRIX transpose = XMMatrixTranspose(world);

		transpose = XMMatrixTranspose(world); // model world matrix


		model_cb_values.directional_light_colour = m_directional_light_colour;
		model_cb_values.ambient_light_colour = m_ambient_light_colour;
		model_cb_values.directional_light_vector = XMVector3Transform(m_directional_light_shines_from, transpose);
		model_cb_values.directional_light_vector = XMVector3Normalize(model_cb_values.directional_light_vector);

		m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, 0, &model_cb_values, 0, 0);
		m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);

		m_pImmediateContext->PSSetSamplers(0, 1, &m_pSampler0);
		m_pImmediateContext->PSSetShaderResources(0, 1, &m_pTexture0);
		m_pImmediateContext->VSSetShader(m_pVShader, 0, 0);
		m_pImmediateContext->PSSetShader(m_pPShader, 0, 0);
		m_pImmediateContext->IASetInputLayout(m_pInputLayout);

		CalculateModelCentrePoint();
		CalculateBoundingSphereRadius();

		m_pObject->Draw();
	}

	void Model::setPos(int x, int y, int z)
	{
		m_x = x;
		m_y = y;
		m_z = z;
	}

	void Model::setRotation(float angle)
	{
		//radians = angle;
		radians += angle;
		m_x = sin(radians * (XM_PI / 180.0));
		m_z = cos(radians * (XM_PI / 180.0));
	}

	void Model::setScale(float x, float y, float z)
	{
		m_scale_x = x;
		m_scale_y = y;
		m_scale_z = z;
	}

	void Model::patrol(int destination)
	{

		// destinationReached bool is always false at the start so it will start moving to the given direction if its positive
		if (m_x >= destination)
			destinationReached = true;

		//Move back to zero position when reached the destination
		if (destinationReached == true)
		{
			m_x -= 0.1;
			if (m_x <= 0)
				destinationReached = false;
		}

		else if (destinationReached == false)
			m_x += 0.1;

	}

	float Model::GetBoundingSphereRadius()
	{
		//Return radius multiplied with scale
		return m_bounding_sphere_radius * m_scale;
	}


	bool Model::CheckCollision(Model* myObj)
	{
		XMVECTOR myPos = this->GetBoundingSphereWorldSpacePosition();
		XMVECTOR myObjPos = myObj->GetBoundingSphereWorldSpacePosition(); //Obj to collide with pos

		float x1 = XMVectorGetX(myPos);
		float y1 = XMVectorGetY(myPos);
		float z1 = XMVectorGetZ(myPos);

		float x2 = XMVectorGetX(myObjPos);
		float y2 = XMVectorGetY(myObjPos);
		float z2 = XMVectorGetZ(myObjPos);

		float distance_squared = pow((x1 - x2),2) + pow((y1 - y2), 2) + pow((z1 - z2), 2);

		if (distance_squared < pow(this->m_bounding_sphere_radius + myObj->m_bounding_sphere_radius, 2))
			return true;

		//returns false if colliding with itself
		if (this != myObj)
			return false;


		return false;
	}

	Model::~Model()
	{
		if (m_pConstantBuffer) m_pConstantBuffer->Release();
		if (m_pInputLayout) m_pInputLayout->Release();
		if (m_pVShader) m_pVShader->Release();
		if (m_pPShader) m_pPShader->Release();
		if (m_pObject) m_pObject->~ObjFileModel();
		if (m_pTexture0) m_pTexture0->Release();
		if (m_pSampler0) m_pSampler0->Release();
		if (m_pImmediateContext) m_pImmediateContext->Release();
		if (m_pD3DDevice) m_pD3DDevice->Release();

	}

	void Model::CalculateModelCentrePoint()
	{
		double xMax = m_pObject->vertices[0].Pos.x;
		double yMax = m_pObject->vertices[0].Pos.y;
		double zMax = m_pObject->vertices[0].Pos.z;
		double xMin = m_pObject->vertices[0].Pos.x;
		double yMin = m_pObject->vertices[0].Pos.y;
		double zMin = m_pObject->vertices[0].Pos.z;

		for (int i = 0; i < m_pObject->numverts; i++)
		{
			//Go through vertices
			m_pObject->vertices[i].Pos.x;
			m_pObject->vertices[i].Pos.y;
			m_pObject->vertices[i].Pos.z;

			// Get max
			if (m_pObject->vertices[i].Pos.x > xMax)
				xMax= m_pObject->vertices[i].Pos.x;
			if (m_pObject->vertices[i].Pos.y > yMax)
				yMax = m_pObject->vertices[i].Pos.y;
			if (m_pObject->vertices[i].Pos.z > zMax)
				zMax = m_pObject->vertices[i].Pos.z;
			// Get min
			if (m_pObject->vertices[i].Pos.x < xMin)
				xMin = m_pObject->vertices[i].Pos.x;
			if (m_pObject->vertices[i].Pos.y < yMin)
				yMin = m_pObject->vertices[i].Pos.y;
			if (m_pObject->vertices[i].Pos.z < zMin)
				zMin = m_pObject->vertices[i].Pos.z;
		}

		// To get the center point we add the lowest and highest values together and divide with 2
		m_bounding_sphere_centre_x = (xMax + xMin) / 2;
		m_bounding_sphere_centre_y = (yMax + yMin) / 2;
		m_bounding_sphere_centre_z = (zMax + zMin) / 2;
	}

	void Model::CalculateBoundingSphereRadius()
	{

		for (int i = 0; i < m_pObject->numverts; i++)
		{
			//Go through vertices
			m_pObject->vertices[i].Pos.x;
			m_pObject->vertices[i].Pos.y;
			m_pObject->vertices[i].Pos.z;
			
			//Distance calculation formula
			sqrt(pow(m_pObject->vertices[0].Pos.x - m_pObject->vertices[i].Pos.x, 2) +
				pow(m_pObject->vertices[0].Pos.y - m_pObject->vertices[i].Pos.y, 2) +
				pow(m_pObject->vertices[0].Pos.z - m_pObject->vertices[i].Pos.z, 2));

			//// Get max
			if (m_pObject->vertices[i].Pos.x > m_pObject->vertices[0].Pos.x)
				m_pObject->vertices[0].Pos.x = m_pObject->vertices[i].Pos.x;

			if (m_pObject->vertices[i].Pos.y > m_pObject->vertices[0].Pos.y)
				m_pObject->vertices[0].Pos.y = m_pObject->vertices[i].Pos.y;

			if (m_pObject->vertices[i].Pos.z > m_pObject->vertices[0].Pos.z)
				m_pObject->vertices[0].Pos.z = m_pObject->vertices[i].Pos.z;
		}

		//Sets the radius based on the highest value
		if (m_pObject->vertices[0].Pos.x >= m_pObject->vertices[0].Pos.y && m_pObject->vertices[0].Pos.x >= m_pObject->vertices[0].Pos.z)
			m_bounding_sphere_radius = m_pObject->vertices[0].Pos.x;
		else if (m_pObject->vertices[0].Pos.y >= m_pObject->vertices[0].Pos.y && m_pObject->vertices[0].Pos.y >= m_pObject->vertices[0].Pos.z)
			m_bounding_sphere_radius = m_pObject->vertices[0].Pos.y;
		else if (m_pObject->vertices[0].Pos.z >= m_pObject->vertices[0].Pos.y && m_pObject->vertices[0].Pos.z >= m_pObject->vertices[0].Pos.z)
			m_bounding_sphere_radius = m_pObject->vertices[0].Pos.z;
		}

	XMVECTOR Model::GetBoundingSphereWorldSpacePosition()
	{
		XMVECTOR offset;

		world = XMMatrixTranslation(m_scale_x, m_scale_y, m_scale_z);
		world *= XMMatrixRotationY(XMConvertToRadians(radians));
		world *= XMMatrixRotationZ(XMConvertToDegrees(degrees));
		world *= XMMatrixTranslation(m_x, m_y, m_z);

		offset = XMVectorSet(m_bounding_sphere_centre_x, m_bounding_sphere_centre_y, m_bounding_sphere_centre_z, 0.0);
		offset = XMVector3Transform(offset, world);

		return offset;
	}

	Model::Model(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext)
	{
			m_pD3DDevice = pDevice;
			m_pImmediateContext = pImmediateContext;
			m_x = 0;
			m_y = 0;
			m_z = 0;
			m_xAngle = m_yAngle = m_zAngle = 0;
			m_scale_x = 1;
			m_scale_y = 1;
			m_scale_z = 1;
			m_scale = 1;
	}


	HRESULT Model::LoadObjModel(char* filename, char* texture)
	{

		HRESULT hr;

		m_pObject = new ObjFileModel(filename, m_pD3DDevice, m_pImmediateContext);

		if (m_pObject->filename == "FILE NOT LOADED") 
			return S_FALSE;

		// Set up and create vertex buffer
		D3D11_BUFFER_DESC constant_buffer_desc0;
		ZeroMemory(&constant_buffer_desc0, sizeof(constant_buffer_desc0));
		constant_buffer_desc0.Usage = D3D11_USAGE_DEFAULT; // can use updatesubresource() to update
		constant_buffer_desc0.ByteWidth = 112; // must be a multiple of 16
		constant_buffer_desc0.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		hr = m_pD3DDevice->CreateBuffer(&constant_buffer_desc0, NULL, &m_pConstantBuffer);


		if (FAILED(hr))//Return an error code if failed
		{
			return hr;
		}

		ID3DBlob* VS, * PS, * error;

		hr = D3DX11CompileFromFile("model_shaders.hlsl", 0, 0, "ModelVS", "vs_4_0", 0, 0, 0, &VS, &error, 0);

		if (error != 0)//Check for shader compilation error
		{
			OutputDebugStringA((char*)error->GetBufferPointer());
			error->Release();
			if (FAILED(hr))//Don't fail if error is just a warning
			{
				return hr;
			}
		}

		hr = D3DX11CompileFromFile("model_shaders.hlsl", 0, 0, "ModelPS", "ps_4_0", 0, 0, 0, &PS, &error, 0);
		if (error != 0)//Check for shader compilation error
		{
			OutputDebugStringA((char*)error->GetBufferPointer());
			error->Release();
			if (FAILED(hr))//Don't fail if error is just a warning
			{
				return hr;
			}
		}

		// Create shader objects
		hr = m_pD3DDevice->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &m_pVShader);
		if (FAILED(hr))
			return hr;
		hr = m_pD3DDevice->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &m_pPShader);
		if (FAILED(hr))
			return hr;

		m_pImmediateContext->VSSetShader(m_pVShader, 0, 0);
		m_pImmediateContext->PSSetShader(m_pPShader, 0, 0);

		//Create and set the input layout object
		D3D11_INPUT_ELEMENT_DESC iedesc[] =
		{
			//Be very careful setting the correct dxgi format and D3D version
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
			//NOTE the spelling of COLOR. Again, be careful setting the correct dxgi format (using A32) and correct D3D version
			{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		hr = m_pD3DDevice->CreateInputLayout(iedesc, ARRAYSIZE(iedesc), VS->GetBufferPointer(), VS->GetBufferSize(), &m_pInputLayout);
		if (FAILED(hr))
		{
			return hr;
		}

		hr = D3DX11CreateShaderResourceViewFromFile(m_pD3DDevice, texture, NULL, NULL, &m_pTexture0, NULL);
		if (FAILED(hr)) exit(0);

		// Create sampler for texture
		D3D11_SAMPLER_DESC sampler_desc;
		ZeroMemory(&sampler_desc, sizeof(sampler_desc));
		sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

		hr = m_pD3DDevice->CreateSamplerState(&sampler_desc, &m_pSampler0);

		m_pImmediateContext->IASetInputLayout(m_pInputLayout);

		return S_OK;
	}
