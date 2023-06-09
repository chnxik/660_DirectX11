#include "sszCollisionManager.h"

#include "sszSceneManager.h"

#include "sszScene.h"
#include "sszLayer.h"

#include "sszGameObject.h"

#include "sszCollider2D.h"

namespace ssz
{
	std::bitset<LAYER_MAX> CollisionManager::mMatrix[LAYER_MAX] = {};
	std::map<UINT64, bool> CollisionManager::mCollisionMap = {};

	void CollisionManager::Initialize()
	{
	}

	void CollisionManager::Update()
	{
		for (UINT iRow = 0; iRow < (UINT)eLayerType::End; ++iRow)
		{
			for (UINT iCol = iRow; iCol < (UINT)eLayerType::End; ++iCol) // 중복 검사를 피하기 위해 열의 시작을 행번호부터 시작 
			{
				if (mMatrix[iRow][iCol])
					LayerCollision((eLayerType)iRow, (eLayerType)iCol); // 충돌검사
			}
		}
	}

	void CollisionManager::LayerCollision(eLayerType left, eLayerType right)
	{
		Scene* ActiveScene = SceneManager::GetActiveScene();

		const std::vector<GameObject*>& lefts
			= ActiveScene->GetLayer(left).GetGameObjects();
		const std::vector<GameObject*>& rights
			= ActiveScene->GetLayer(right).GetGameObjects();

		for (size_t LeftIdx = 0; LeftIdx < lefts.size(); ++LeftIdx)
		{
			// 추후 여러개의 콜라이더를 사용할 경우 수정
			Collider2D* leftCol = lefts[LeftIdx]->GetComponent<Collider2D>();

			if (nullptr == leftCol) // 충돌체가 없는경우
				continue;

			size_t RightIdx = 0;
			if (left == right)	// 충돌검사하는 두 레이어가 동일한 경우, 이중검사를 피하기 위해 RightIdx를 LeftIdx부터 시작한다.
			{
				RightIdx = LeftIdx;
			}

			for (; RightIdx < rights.size(); ++RightIdx)
			{
				Collider2D* rightCol = rights[RightIdx]->GetComponent<Collider2D>();

				if (nullptr == rightCol) // 충돌체가 없는 경우
					continue;

				if (lefts[LeftIdx] == rights[RightIdx]) // 충돌검사 대상이 자기 자신인 경우
					continue;

				bool bDead = lefts[LeftIdx]->IsDead() || rights[RightIdx]->IsDead(); // 검사 대상 객채중 한 객체가 Dead상태이다.

				ColliderCollision(leftCol, rightCol, bDead); // 충돌검사 로직
			}
		}
	}

	void CollisionManager::ColliderCollision(Collider2D* left, Collider2D* right, bool bDead)
	{
		// 두 충돌체의 ID 확인
		ColliderID ID = {};
		ID.left = left->GetColliderID();
		ID.right = right->GetColliderID();

		// 충돌 정보를 가져온다
		std::map<UINT64, bool>::iterator iter = mCollisionMap.find(ID.id);
		if (mCollisionMap.end() == iter) // 충돌정보가 없다
		{
			mCollisionMap.insert(std::make_pair(ID.id, false));
			iter = mCollisionMap.find(ID.id);
		}

		eColliderType LeftColType = left->GetType();
		eColliderType RightColType = right->GetType();
		bool bCollision = false;

		// Type별 충돌검사

		if (eColliderType::Rect == LeftColType && eColliderType::Rect == RightColType) // Rect 충돌
		{
			bCollision = RectIntersect(left, right);
		}
		else if (eColliderType::Circle == LeftColType && eColliderType::Circle == RightColType) // Circle 충돌
		{
			bCollision = CircleIntersect(left, right);
		}
		else // 혼합 충돌
		{
			if (eColliderType::Rect == LeftColType)
			{
				bCollision = MixIntersect(left, right);
			}
			else
			{
				bCollision = MixIntersect(right, left);
			}
		}

		if (bCollision) // 충돌했다
		{
			if (iter->second) // 충돌정보 있음
			{
				if (bDead) // 검사대상이 Dead 이므로 충돌체 벗어남.
				{
					left->OnCollisionExit(right);
					right->OnCollisionExit(left);
					mCollisionMap.erase(iter); // 이 객체간 충돌정보를 삭제
				}
				else // 충돌 중
				{
					left->OnCollisionStay(right);
					right->OnCollisionStay(left);
				}
			}

			else // 충돌정보 없음
			{
				if (!bDead) // 검사대상이 Dead가 아님.
				{
					//최초 충돌
					left->OnCollisionEnter(right);
					right->OnCollisionEnter(left);
					iter->second = true; // 충돌정보 갱신
				}
			}
		}

		else // 충돌하지 않았다
		{
			if (iter->second) // 충돌정보 있음
			{
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);
				iter->second = false; // 충돌정보 갱신
			}

			if (bDead) // 검사 대상이 Dead 상태
			{
				mCollisionMap.erase(iter); // 이 객체간 충돌정보를 삭제
			}
		}

	}

	bool CollisionManager::RectIntersect(Collider2D* left, Collider2D* right)
	{
		// 사각형 충돌

		return false;
	}

	bool CollisionManager::CircleIntersect(Collider2D* left, Collider2D* right)
	{
		// 원 충돌

		return false;
	}

	bool CollisionManager::MixIntersect(Collider2D* Rect, Collider2D* Circle)
	{
		// 사각 원 혼합 충돌

		return false;
	}

	void CollisionManager::SetLayer(eLayerType left, eLayerType right, bool enable)
	{
		UINT iRow = (UINT)left;
		UINT iCol = (UINT)right;

		if (iRow > iCol)
		{
			UINT iTemp = iRow;
			iCol = iRow;
			iRow = iTemp;
		}

		mMatrix[iRow][iCol] = enable;
	}

	void CollisionManager::Clear()
	{
		mMatrix->reset();
		mCollisionMap.clear();
	}
}