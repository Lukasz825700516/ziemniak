#include <iostream>
#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <imnodes.h>

int main() {
	GLFWwindow* window;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(800, 600, "ziemniak", 0, 0);
	if (!window) {
		std::cerr << "Failed to create window!" << std::endl;
		std::exit(1);
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		std::exit(1);
	} 
	glad_glViewport(0, 0, 800, 600);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	imnodes::Initialize();

	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.MouseDrawCursor = true;

	ImGui::StyleColorsDark();
	imnodes::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");

	std::vector<std::pair<int, int>> links;

	while (!glfwWindowShouldClose(window)) {

		glad_glClearColor(0.1, 0.5, 0.5, 0.1);
		glad_glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::DockSpaceOverViewport();

		ImGui::Begin("Hello world!");

        imnodes::BeginNodeEditor();

		imnodes::PushColorStyle(imnodes::ColorStyle_TitleBar, IM_COL32(0, 255 * 0.8, 0, 255));
		imnodes::PushColorStyle(imnodes::ColorStyle_TitleBarHovered, IM_COL32(255 * 0.1, 255 * 0.8, 255 * 0.1, 255));
		imnodes::PushColorStyle(imnodes::ColorStyle_TitleBarSelected, IM_COL32(0, 255, 0, 255));
        imnodes::BeginNode(1);
        imnodes::BeginNodeTitleBar();
        ImGui::TextUnformatted("Perlin noise");
        imnodes::EndNodeTitleBar();
        imnodes::BeginOutputAttribute(2);
        ImGui::Indent(40);
        ImGui::Text("heightmap");
        imnodes::EndOutputAttribute();
        imnodes::EndNode();
		imnodes::PopColorStyle();
		imnodes::PopColorStyle();
		imnodes::PopColorStyle();

        imnodes::BeginNode(3);
        imnodes::BeginNodeTitleBar();
        ImGui::TextUnformatted("Hydraulic erosion");
        imnodes::EndNodeTitleBar();
		imnodes::BeginInputAttribute(4);
        ImGui::Text("heightmap");
		imnodes::EndInputAttribute();
        imnodes::BeginOutputAttribute(5);
        ImGui::Indent(40);
        ImGui::Text("heightmap");
        imnodes::EndOutputAttribute();
        imnodes::EndNode();

		imnodes::PushColorStyle(imnodes::ColorStyle_TitleBar, IM_COL32(255 * 0.8, 0, 0, 255));
		imnodes::PushColorStyle(imnodes::ColorStyle_TitleBarHovered, IM_COL32(255 * 0.8, 255 * 0.1, 255 * 0.1, 255));
		imnodes::PushColorStyle(imnodes::ColorStyle_TitleBarSelected, IM_COL32(255, 0, 0, 255));
        imnodes::BeginNode(6);
        imnodes::BeginNodeTitleBar();
        ImGui::TextUnformatted("Output");
        imnodes::EndNodeTitleBar();
        imnodes::BeginInputAttribute(7);
        ImGui::Text("heightmap");
        imnodes::EndOutputAttribute();
        imnodes::EndNode();
		imnodes::PopColorStyle();
		imnodes::PopColorStyle();
		imnodes::PopColorStyle();

		for (int i = 0; i < links.size(); ++i) {
			const std::pair<int, int> p = links[i];
			imnodes::Link(i, p.first, p.second);
		}

        imnodes::EndNodeEditor();
		ImGui::End();

		ImGui::Begin("HELLLLOOOO world!");
		ImGui::End();


		int start_attr, end_attr;
		if (imnodes::IsLinkCreated(&start_attr, &end_attr)) {
			links.push_back(std::make_pair(start_attr, end_attr));
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	imnodes::Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
