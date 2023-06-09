#pragma once
#include "sszScene.h"
#include "sszGameObject.h"

namespace ssz
{
	class MainLobbyScene : public Scene
	{
	public:
		MainLobbyScene();
		virtual ~MainLobbyScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		GameObject* BgSky;
	};
}