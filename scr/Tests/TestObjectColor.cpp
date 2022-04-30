#include "TestObjectColor.h"
#include "Renderer.h"
#include "imgui/imgui.h"
#include "Shader.h"
namespace test {
	TestObjectColor::TestObjectColor() :m_color{ 1.0f,1.0f,1.0f,1.0f }
	{
	}
	TestObjectColor::~TestObjectColor()
	{
	}
	void TestObjectColor::OnUpdate(float deltaTime)
	{
	}
	void TestObjectColor::OnRender()
	{

	}
	void TestObjectColor::OnImGui()
	{
		Shader shader("res/Shader/Shader.shader");
		shader.Bind();
		shader.SetUniform4f("u_Color", m_color[0], m_color[1], m_color[2], m_color[3]);
		ImGui::ColorEdit4("Color Edit 1", m_color);
	}
}