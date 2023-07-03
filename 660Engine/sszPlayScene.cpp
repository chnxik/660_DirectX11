#include "sszPlayScene.h"

#include "sszTransform.h"
#include "sszMeshRenderer.h"
#include "sszCamera.h"

#include "sszResources.h"
#include "sszMesh.h"

#include "sszCameraScript.h"

#include "sszSceneManager.h"

namespace ssz
{
	PlayScene::PlayScene()
	{
	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initialize()
	{
		{
			GameObject* player = new GameObject();
			player->SetName(L"player");
			AddGameObject(eLayerType::Player, player);
			
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
			player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0001f));
		
			GameObject* player2 = new GameObject();
			player2->SetName(L"Child");
			AddGameObject(eLayerType::Player, player2);
			
			MeshRenderer* mr2 = player2->AddComponent<MeshRenderer>();
			mr2->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr2->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
			player2->GetComponent<Transform>()->SetPosition(Vector3(1.0f, 0.0f, 1.0001f));
			 
			player2->GetComponent<Transform>()->SetParent(player->GetComponent<Transform>()); // player2�� ���� Transform Component�� �θ� player�� Component�� �����Ѵ�.
			
			player->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, DtoR(180.f)));
		}

		// Main Camera
		{
			GameObject* camera = new GameObject();
			camera->SetName(L"MainCamera");
			AddGameObject(eLayerType::UI, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);	// UI Layer �� �׸��� �ʴ´�.
			camera->AddComponent<CameraScript>();
		}

		// UI Camera
		{
			GameObject* camera = new GameObject();
			camera->SetName(L"UICamera");
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::Player, false); // Player Layer �� �׸��� �ʴ´�.
		}
	}

	void PlayScene::Update()
	{
		Scene::Update();
	}

	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}
}