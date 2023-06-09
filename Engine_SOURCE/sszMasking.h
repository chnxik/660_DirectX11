#pragma once
#include "sszComponent.h"

namespace ssz
{
	class Masking : public Component
	{
	public:
		Masking();
		~Masking();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void BindConstantBuffer() override;

	private:
		Vector3 LeftTop;
		Vector3 RightBottom;
	};
}