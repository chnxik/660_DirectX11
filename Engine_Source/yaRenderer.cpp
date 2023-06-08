#include "yaRenderer.h"
#include "yaTime.h"
#include "yaInput.h"

#define CIRCLEVERTEX 20

namespace renderer
{
	Vertex vertexes[CIRCLEVERTEX+1] = {};
	ya::Mesh* mesh = nullptr;
	ya::Shader* shader = nullptr;
	ya::graphics::ConstantBuffer* TransformConstantBuffer = nullptr;
	Vector4 Pos = { 0.f,0.f,0.f,0.f };

	void SetupState()
	{
		// InputLayout ���� ���� ������ �Ѱ��ش�.
		D3D11_INPUT_ELEMENT_DESC arrLayout[2] = {};

		arrLayout[0].AlignedByteOffset = 0;
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		arrLayout[0].InputSlot = 0;
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		arrLayout[1].AlignedByteOffset = 12;
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayout[1].InputSlot = 0;
		arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[1].SemanticName = "COLOR";
		arrLayout[1].SemanticIndex = 0;

		ya::graphics::GetDevice()->CreateInputLayout(arrLayout, 2
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());
	}

	void LoadBuffer()
	{
		// Mesh
		mesh = new ya::Mesh();
		mesh->CreateVertexBuffer(vertexes, CIRCLEVERTEX+1);

		std::vector<UINT> indexes = {};

		for (int i = 0; i < CIRCLEVERTEX; ++i)
		{
			indexes.push_back(0); // ����

			if (CIRCLEVERTEX - 1 == i) // ������
			{
				indexes.push_back(1);
				indexes.push_back(i + 1);
			}
			else
			{
				indexes.push_back(i + 2);
				indexes.push_back(i + 1);
			}
		}

		mesh->CreateIndexBuffer(indexes.data(), indexes.size());

		// Constant Buffer
		TransformConstantBuffer = new ya::graphics::ConstantBuffer(eCBType::Transform);
		TransformConstantBuffer->Create(sizeof(Vector4)*2);

		ColorConstantBuffer = new ya::graphics::ConstantBuffer(eCBType::Color);
		ColorConstantBuffer->Create(sizeof(Vector4));
	}

	void LoadShader()
	{
		shader = new ya::Shader();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
	}

	void Initialize()
	{
		// vertex ����
		vertexes[0].pos = Vector3(0.0f, 0.0f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		for (int i = 0; i < CIRCLEVERTEX; ++i)
		{
			float x = 0.0f;
			float y = 0.0f;
			float r = 0.1f;
			float degree = (360.f / (float)CIRCLEVERTEX) * i;
			float radian = (3.141592f / 180.f) * degree;

			x = r * cosf(radian);
			y = r * sinf(radian);

			vertexes[i + 1].pos = Vector3(x, y, 0.0f);
			vertexes[i + 1].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		}

		LoadBuffer();
		LoadShader();
		SetupState();
	}

	void Release()
	{
		delete mesh;
		delete shader;
		delete TransformConstantBuffer;
		delete ColorConstantBuffer;
	}

	void update()
	{
		if (ya::Input::GetKey(ya::eKeyCode::UP))	{ Pos.y += 1.f *(float)ya::Time::DeltaTime(); }
		if (ya::Input::GetKey(ya::eKeyCode::DOWN))	{ Pos.y -= 1.f *(float)ya::Time::DeltaTime(); }
		if (ya::Input::GetKey(ya::eKeyCode::RIGHT)) { Pos.x += 1.f *(float)ya::Time::DeltaTime(); }
		if (ya::Input::GetKey(ya::eKeyCode::LEFT))	{ Pos.x -= 1.f *(float)ya::Time::DeltaTime(); }
		
		TransformConstantBuffer->SetData(&Pos);
		TransformConstantBuffer->Bind(eShaderStage::VS);
	}
}