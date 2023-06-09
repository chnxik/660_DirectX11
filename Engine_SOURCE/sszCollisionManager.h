#pragma once
#include "sszEngine.h"

namespace ssz
{
#define LAYER_MAX (UINT)eLayerType::End
	using namespace enums;

	class Collider2D;
	class CollisionManager
	{
	public:
		union ColliderID
		{
			struct
			{
				UINT left;
				UINT right;
			};
			UINT64 id;
		};

		static void Initialize();
		static void Update();
		static void LayerCollision(eLayerType left, eLayerType right);
		static void ColliderCollision(Collider2D* left, Collider2D* right, bool bDead);
		static bool RectIntersect(Collider2D* left, Collider2D* right);
		static bool CircleIntersect(Collider2D* left, Collider2D* right);
		static bool MixIntersect(Collider2D* Rect, Collider2D* Circle);

		static void SetLayer(eLayerType left, eLayerType right, bool enable);
		static void Clear();

	private:

		static std::bitset<LAYER_MAX> mMatrix[LAYER_MAX];
		static std::map<UINT64, bool> mCollisionMap;
	};
}