#include "sszCursorScript.h"

#include "sszApplication.h"
#include "sszGameObject.h"

#include "sszInput.h"

#include "sszTransform.h"
#include "sszMeshRenderer.h"
#include "sszMaterial.h"
#include "sszCamera.h"

extern ssz::Application application;

namespace ssz
{
	CursorScript::CursorScript()
		: CursorSize{}
	{
	}

	CursorScript::~CursorScript()
	{
	}

	void CursorScript::Initialize()
	{
		CursorSize = GetOwner()->GetComponent<MeshRenderer>()->GetMaterial()->GetTexture()->GetTextureSize() / 2.f;
	}
	
	void CursorScript::LateUpdate()
	{
		{
			// Get Mouse Pos
			Vector2 MousePos = Input::GetMousePos();
		
			// CursorSize�� ��ġ ����
			Vector3 FinalPos(MousePos.x + CursorSize.x, MousePos.y + CursorSize.y, 0.0f);
		
			// Mouse Cursor�� Adjust window rect �ϸ� �޶���
			RECT rect = {};
			GetClientRect(application.GetHwnd(), &rect);
			float width = (float)(rect.right - rect.left);
			float height = (float)(rect.bottom - rect.top);
		
			Viewport viewport;
			viewport.width = width;
			viewport.height = height;
			
			viewport.x = (float)rect.left;
			viewport.y = (float)rect.top;
			viewport.minDepth = 0.0f;
			viewport.maxDepth = 1.0f;
			
			FinalPos = viewport.Unproject(FinalPos, Camera::GetProjectionMatrix(), Camera::GetViewMatrix(), Matrix::Identity);
			FinalPos *= Vector3(width, height, 1.0f);
			
			GetOwner()->GetComponent<Transform>()->SetPosition(FinalPos);
		}
	}
}