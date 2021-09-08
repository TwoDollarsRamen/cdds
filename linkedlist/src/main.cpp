#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

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
 * Dear ImGui backends such as the Vulkan or DirectX backends. */

static void framebuffer_size_func(GLFWwindow* window, int x, int y) {
	glViewport(0, 0, x, y);
}

int main() {
	glfwInit();

	/* The minimum OpenGL version that the modern Dear ImGui backend
	 * supports. */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	GLFWwindow* window = glfwCreateWindow(1024, 768, "Linked List demo", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_func);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("res/opensans.ttf", 17.0f);

	ImGui::StyleColorsLight();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::ShowDemoWindow();

		ImGui::Render();
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();

	ImGui::DestroyContext();

	glfwDestroyWindow(window);

	glfwTerminate();
}
