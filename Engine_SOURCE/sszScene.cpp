#include "sszScene.h"
#include "sszTime.h"
#include "sszCircle.h"
#include "sszPlayer.h"
#include "sszEnemy.h"

#define SPAWNTIME 0.3f

namespace ssz
{
	Scene::Scene()
		: mPlayer(nullptr)
		, acc(0.0f)
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::Initialize()
	{
		// ���⼭ �ʱ� ���� �ʵ����͸� ��������� �Ѵ�.
		srand((unsigned int)time(NULL));

		// Player ����
		mPlayer = new Player();
		((Circle*)mPlayer)->SetPos(Vector4(0.f, 0.f, 0.02f, 1.0f));
		((Circle*)mPlayer)->SetColor(0.6f, 0.3f, 0.7f);
		((Player*)mPlayer)->SetRadius(0.02f);
		((Player*)mPlayer)->SetFinalColor(((Circle*)mPlayer)->GetColor());

		// �ʱ� Enemy ���� 20��

		for (int i = 0; i < 20; ++i)
		{
			Circle* EnemyCircle = new Enemy();

			float x, y, r, g, b;
			x = (((float)(rand() % 200)) - 100.f) * 0.01f;
			y = (((float)(rand() % 200)) - 100.f) * 0.01f;
			r = (float)(rand() % 11) * 0.1f;
			g = (float)(rand() % 11) * 0.1f;
			b = (float)(rand() % 11) * 0.1f;

			EnemyCircle->SetPos(Vector4(x, y, 0.015f, 1.0f));
			EnemyCircle->SetColor(r, g, b);

			mGameObjects.push_back(EnemyCircle);
		}
	}

	void Scene::Update()
	{
		
		acc += (float)ssz::Time::DeltaTime();
		
		if (SPAWNTIME < acc)
		{
			acc = acc - SPAWNTIME; // �ʱ�ȭ �� �ʰ��� �ð���ŭ �����ش�.
			Circle* EnemyCircle = new Enemy();
		
			float x, y, r, g, b;
			x = (((float)(rand() % 200)) - 100.f) * 0.01f;
			y = (((float)(rand() % 200)) - 100.f) * 0.01f;
			r = (float)(rand() % 11) * 0.1f;
			g = (float)(rand() % 11) * 0.1f;
			b = (float)(rand() % 11) * 0.1f;

			EnemyCircle->SetPos(Vector4(x, y, 0.015f, 1.0f));
			EnemyCircle->SetColor(r, g, b);
		
			mGameObjects.push_back(EnemyCircle);
		}

		mPlayer->Update();
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->Update();
		}
	}

	void Scene::LateUpdate()
	{
		int deleteCnt;

		deleteCnt = 0;

		Vector4 PlayerPos = ((Circle*)mPlayer)->GetPos();
		Vector4 EnemyPos = {};
		float dist = 0.f;
		float contactdist = 0.f;
		std::vector<GameObject*>::iterator iter = mGameObjects.begin();

		// �浹 �˻�
		for (GameObject* gameObj : mGameObjects)
		{
			
			EnemyPos = ((Circle*)gameObj)->GetPos();	// Enemy Pos
			contactdist = PlayerPos.z + EnemyPos.z;		// ���� �Ÿ� ( �� ��ü ������ �հ� )

			// �Ÿ��Ǵ�
			dist = sqrt((PlayerPos.x - EnemyPos.x) * (PlayerPos.x - EnemyPos.x) + (PlayerPos.y - EnemyPos.y) * (PlayerPos.y - EnemyPos.y));


			// �浹���� ��
			if (dist < contactdist)
			{
				iter = mGameObjects.erase(iter);	// �浹�� �� ��ü ����
				((Player*)mPlayer)->AddRadius(0.005f);	// ������ ũ�� �ݿ�
				((Player*)mPlayer)->GetEffect();
			}

			// �浹���� �ʾ����� ��ó�� ���� ��
			else if (dist < contactdist + 0.08f)
			{
				if (!((Enemy*)gameObj)->IsMagnet())
				{
					((Enemy*)gameObj)->SetMagnet((Circle*)mPlayer);
				}
				iter++;
			}

			// �浹���� �ʾ��� ��
			else
			{
				iter++;
			}
		}
		
	}
	void Scene::Render()
	{
		mPlayer->Render();
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->Render();
		}
	}
}
