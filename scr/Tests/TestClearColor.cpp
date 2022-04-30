#include "TestClearColor.h"
#include "Renderer.h"
#include "imgui/imgui.h"
namespace test {
	TestClearColor::TestClearColor() : m_Color{1.0f,1.0f, 1.0f, 1.0f, }
	{
	}
	TestClearColor::~TestClearColor()
	{
	}
	void TestClearColor::OnUpdate(float deltaTime)
	{
	}

	void TestClearColor::OnRender()
	{
		glClearColor(m_Color[0], m_Color[1], m_Color[2], m_Color[3]);
		glClear(GL_COLOR_BUFFER_BIT);

	}

	void TestClearColor::OnImGui()
	{
		ImGui::ColorEdit4("BackGround Edit", m_Color);

	}
}

