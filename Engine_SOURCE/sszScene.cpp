#include "sszScene.h"
#include "sszPlayer.h"
#include "sszTime.h"

namespace ssz
{
	Scene::Scene()
		: acc(0.0f)
		, position(0.0f)
	{
	}
	Scene::~Scene()
	{
	}

	void Scene::Initialize()
	{
		// ���⼭ �ʱ� ���� �ʵ����͸� ��������� �Ѵ�.
		GameObject* PlayerCicle = new Player();
		PlayerCicle->Initialize();
		((Circle*)PlayerCicle)->CreateCicle(Vector4(0.f, 0.f, 0.1f, 1.0f), Vector4(1.0f, 0.f, 1.0f, 1.0f));

		mGameObjects.push_back(PlayerCicle);
	}

	void Scene::Update()
	{
		acc += (float)ssz::Time::DeltaTime();
		if (1.0f < acc)
		{
			acc = acc - 1.0f; // �ʱ�ȭ �� �ʰ��� �ð���ŭ �����ش�.
			GameObject* Enemy = new Circle();
			Enemy->Initialize();
			((Circle*)Enemy)->CreateCicle(Vector4(position, 0.f, 0.05f, 1.0f), Vector4(1.0f, 1.f, 1.0f, 1.0f));
			position += 0.1f;
		
			mGameObjects.push_back(Enemy);
		}

		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->Update();
		}
	}

	void Scene::LateUpdate()
	{
	}
	void Scene::Render()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->Render();
		}
	}
}
