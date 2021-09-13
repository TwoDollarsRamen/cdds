#include <string>

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl2.h>
#include <imnodes.h>

/* The reason why I chose to use Dear ImGui over RayGUI is because
 * Dear ImGui is simply a better GUI. More difficult to set up, and
 * requires choosing a windowing and rendering backend, but in my
 * opinion it's worth it because it's so much more convinient to
 * use, because it includes things like automatic layout, meaning
 * that you don't have to manually specify the positions and sizes
 * of GUI elements, which makes using RayGUI for anything more than
 * a basic debug menu incredibly painful.
 *
 * I chose GLFW as the windowing and input backend and OpenGL as the
 * rendering backend because those are what I'm familiar with, and
 * they are quick and easy to setup in comparison to the other
 * Dear ImGui backends such as the Vulkan or DirectX backends.
 *
 * I'm using the OpenGL 2 backend instead of the modern one
 * because my Windows virtual machine doesn't support OpenGL 3.x. */

#include "tree.hpp"

static void framebuffer_size_func(GLFWwindow* window, int x, int y) {
	glViewport(0, 0, x, y);
}

int main() {
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(1024, 768, "Binary Tree Demo", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_func);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("res/opensans.ttf", 17.0f);

	ImGui::StyleColorsLight();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL2_Init();

	ImNodes::CreateContext();

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		ImGui_ImplOpenGL2_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (ImGui::Begin("Binary Tree Demo")) {
		    ImNodes::BeginNodeEditor();

		    ImNodes::BeginNode(1);

		    ImNodes::BeginNodeTitleBar();
		    ImGui::TextUnformatted("node");
		    ImNodes::EndNodeTitleBar();

		    ImNodes::EndNode();

		    ImNodes::EndNodeEditor();
		}
		ImGui::End();

		ImGui::Render();
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplGlfw_Shutdown();

	ImNodes::DestroyContext();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);

	glfwTerminate();
}