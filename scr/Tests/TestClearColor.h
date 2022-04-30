#pragma once
#include "test.h"

namespace test {
	class  TestClearColor : public Test
	{
	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate(float deltaTime) override ;
		void OnRender()override;
		void OnImGui()override;

	private:
		float m_Color[4];
	};


}