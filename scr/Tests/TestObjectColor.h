#pragma once
#include "test.h"
namespace test {
	class TestObjectColor : public Test
	{
	public:
		TestObjectColor();
		~TestObjectColor();

		void OnUpdate(float deltaTime) override;
		void OnRender()override;
		void OnImGui()override;

	private:
		float m_color[4];
	

	};

	
}