#include "vnpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"
#include "VinoGL/Application.h"

#include "GLFW/glfw3.h"
#include <glad/glad.h>

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
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui::StyleColorsDark();

	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = .0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	Application& app = Application::Get();
	GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 410");


	Vino::EventAggregator<Vino::WindowSizeChangedEvent>::Subscribe([](const Vino::WindowSizeChangedEvent& windowSize)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(windowSize.Width, windowSize.Height);
	});
}

void Vino::ImGuiLayer::OnDetach()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Vino::ImGuiLayer::OnRender()
{
	static bool show = true;
	ImGui::ShowDemoWindow(&show);
}


void Vino::ImGuiLayer::Begin()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Vino::ImGuiLayer::End()
{
	ImGuiIO& io = ImGui::GetIO();
	Application& app = Application::Get();
	io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}
