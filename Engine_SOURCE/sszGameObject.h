#pragma once
#include "sszEntity.h"
#include "sszComponent.h"
#include "sszScript.h"

namespace ssz
{
	class GameObject : public Entity
	{
	public:
		enum eState
		{
			Active,
			Paused,
			Dead,
		};

		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		std::vector<Component*> GetComponents() { return mComponents; }
		std::vector<Script*> GetScripts() { return mScripts; }

		template <typename T>
		const std::vector<T*>& GetComponents()
		{
			std::vector<T*> comps;

			T* component;
			for (Component* comp : mComponents)
			{
				component = dynamic_cast<T*>(comp);
				if (component != nullptr)
					comps.push_back(component);
			}

			for (Script* script : mScripts)
			{
				component = dynamic_cast<T*>(script);
				if (component != nullptr)
					comps.push_back(component);
			}

			return comps;
		}

		template <typename T>
		T* GetComponent()
		{
			T* component;
			for (Component* comp : mComponents)
			{
				component = dynamic_cast<T*>(comp);
				if (component != nullptr)
					return component;
			}

			for (Script* script : mScripts)
			{
				component = dynamic_cast<T*>(script);
				if (component != nullptr)
					return component;
			}

			return nullptr;
		}

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			
			Component* buff
				= dynamic_cast<Component*>(comp);

			Script* script
				= dynamic_cast<Script*>(buff);

			if (buff == nullptr)
				return nullptr;

			if (script == nullptr)
				mComponents.push_back(buff);
			else
				mScripts.push_back(script);

			comp->SetOwner(this);

			return comp;
		}

		void SetState(eState state) { mState = state; }
		bool IsDead() { return eState::Dead == mState; }
		bool IsActive() { return eState::Active == mState; }
		bool IsPaused() { return eState::Paused == mState; }
		eState GetState() { return mState; }

		void SetParent(GameObject* parent);

	private:
		eState mState;
		std::vector<Component*> mComponents;
		std::vector<Script*> mScripts;
	};
}