#pragma once
#include <sszScript.h>

namespace ssz
{
	class TestScript : public Script
	{
	public:
		TestScript();
		virtual ~TestScript();

		virtual void Initialize() override;
		virtual void Update() override;

		void SetDefault();

	private:
		Vector3 OffsetPos;
		Vector3 OffsetScale;
		Vector3 OffsetRotation;

		float fradius;
		float fradiusx;
		float fradiusy;
	};
}