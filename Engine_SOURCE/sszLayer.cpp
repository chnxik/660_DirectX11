#include "sszLayer.h"

namespace ssz
{

	Layer::Layer()
	{
	}

	Layer::~Layer()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			delete gameObj;
			gameObj = nullptr;
		}
	}

	void Layer::Initialize()
	{
	}

	void Layer::Update()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->Update();
		}
	}

	void Layer::LateUpdate()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->LateUpdate();
		}
	}

	void Layer::Render()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->Render();
		}
	}

	void Layer::Destory()
	{
		// ���� �����ӿ��� ������û�� ������Ʈ���� �����ϰ� Garbage�迭�� ����ش�.
		{
			// Garbage�� �ִ� �� ����ó��
			for (GameObject* gameObj : mGarbageObjects)
			{
				delete gameObj;
				gameObj = nullptr;
			}
			// Garbage ���� ����ֱ�
			mGarbageObjects.clear();
		}

		{
			// GameObjects���� Garbage�� ����ϱ�
			typedef std::vector<GameObject*>::iterator GameObjectIter;
			for (GameObjectIter iter = mGameObjects.begin(); iter != mGameObjects.end();)
			{
				// iter�� Dead�����̴�.
				if ((*iter)->IsDead())
				{
					// Garbage�� �־��ְ� GameObject �迭���� erase �ϱ�.
					mGarbageObjects.push_back(*iter);
					iter = mGameObjects.erase(iter);
				}
				// iter�� Dead���°� �ƴϴ�.
				else
				{
					iter++;
				}
			}
		}
	}

	void Layer::AddGameObject(GameObject* gameObj)
	{
		mGameObjects.push_back(gameObj);
	}
}