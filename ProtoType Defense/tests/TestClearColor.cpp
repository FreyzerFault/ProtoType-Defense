#include "pch.h"
#include "TestClearColor.h"

test::TestClearColor::TestClearColor()
	: m_ClearColor { 0.2f, 0.3f, 0.8f, 1.0f }
{
	
}

test::TestClearColor::~TestClearColor() = default;

void test::TestClearColor::onUpdate(DeltaTime deltaTime)
{

}

void test::TestClearColor::onRender()
{
	Renderer::setClearColor(m_ClearColor);
	Renderer::clear();
}

void test::TestClearColor::onImGuiRender()
{
	ImGui::ColorEdit3("Clear Color", &m_ClearColor.x);
}
