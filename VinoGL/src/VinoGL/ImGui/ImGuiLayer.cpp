#include "vnpch.h"
#include "ImGuiLayer.h"
#include "VinoGL/Platform/OpenGL/ImGuiRenderer.h"
#include "GLFW/glfw3.h"
#include "VinoGL/Events/EventAggregator.h"
#include "VinoGL/Events/Window/WindowEvents.h"
Vino::ImGuiLayer::ImGuiLayer(): Layer("ImGuiLayer")
{
}

Vino::ImGuiLayer::~ImGuiLayer()
{
}

void Vino::ImGuiLayer::OnAttach()
{
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGuiIO& io = ImGui::GetIO();
	io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
	io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
	io.DisplaySize = ImVec2(1280, 720);
	ImGui_ImplOpenGL3_Init("#version 410");

	io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
	io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
	io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
	io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
	io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
	io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
	io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
	io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
	io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
	io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
	io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
	io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
	io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
	io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
	io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
	io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
	io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
	io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
	io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
	io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
	io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

	Vino::EventAggregator<Vino::WindowSizeChanged>::Subscribe([](const Vino::WindowSizeChanged& windowSize)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(windowSize.Width, windowSize.Height);
	});
}

void Vino::ImGuiLayer::OnDetach()
{
	ImGui::DestroyContext();


}

void Vino::ImGuiLayer::OnUpdate()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

	float time = (float)glfwGetTime();
	ImGuiIO& io = ImGui::GetIO();
	io.DeltaTime = m_Time > 0.f ? (time - m_Time) : (1.f / 60.f);
	m_Time = time;
	static bool show = true;
	ImGui::ShowDemoWindow(&show);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
