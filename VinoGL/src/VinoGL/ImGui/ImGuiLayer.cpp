#include "vnpch.h"
#include "ImGuiLayer.h"
#include "VinoGL/Platform/OpenGL/ImGuiRenderer.h"
#include "GLFW/glfw3.h"
Vino::ImGuiLayer::ImGuiLayer(): Layer("ImGuiLayer")
{
	m_SizeChangeToken = Vino::EventAggregator<Vino::WindowSizeChangedEvent>::Subscribe([](const Vino::WindowSizeChangedEvent& ev)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(ev.Width, ev.Height);
		io.DisplayFramebufferScale = ImVec2(1.f, 1.f);
	});
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

	Vino::EventAggregator<Vino::WindowSizeChangedEvent>::Subscribe([](const Vino::WindowSizeChangedEvent& windowSize)
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

void Vino::ImGuiLayer::OnMouseButtonPressed(Vino::MouseButtonPressedEvent& ev)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseDown[ev.Button] = true;
}

void Vino::ImGuiLayer::OnMouseButtonReleased(Vino::MouseButtonReleasedEvent& ev)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseDown[ev.Button] = false;
}

void Vino::ImGuiLayer::OnMousePositionChanged(Vino::MousePositionChangedEvent& ev)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = ImVec2(ev.xPos, ev.yPos);
}

void Vino::ImGuiLayer::OnMouseScrolled(Vino::MouseScrolledEvent& ev)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseWheelH += ev.xOffset;
	io.MouseWheel += ev.yOffset;
}

void Vino::ImGuiLayer::OnKeyPressed(Vino::KeyPressedEvent& ev)
{
	ImGuiIO& io = ImGui::GetIO();
	io.KeysDown[ev.Key] = true;

	io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
	io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
	io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
	io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
}

void Vino::ImGuiLayer::OnKeyReleased(Vino::KeyReleasedEvent& ev)
{
	ImGuiIO& io = ImGui::GetIO();
	io.KeysDown[ev.Key] = false;
}

void Vino::ImGuiLayer::OnKeyTyped(Vino::KeyTypedEvent& ev)
{
	ImGuiIO& io = ImGui::GetIO();
	if (ev.Key > 0 && ev.Key < 0x10000)
	{
		io.AddInputCharacter((unsigned short)ev.Key);
	}
}