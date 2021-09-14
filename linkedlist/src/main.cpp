#include <string>
#include <functional>

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl2.h>

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

#include "list.hpp"

static void framebuffer_size_func(GLFWwindow* window, int x, int y) {
	glViewport(0, 0, x, y);
}

void run_tests();

int main() {
	/* Test the linked list */
	run_tests();

	/* Initialise stuff */
	glfwInit();

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
	ImGui_ImplOpenGL2_Init();

	/* The list itself */
	list<int> some_list;

	/* This is the value that will be pushed in to the
	 * list when the push back or push front buttons are pressed.
	 * 
	 * It's value is set by Daer ImGui Widget. */
	int create_value = 0;

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		ImGui_ImplOpenGL2_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		/* The main GUI. */
		if (ImGui::Begin("Linked List Demo")) {
			ImGui::Text("List count: %d", some_list.count());

			if (ImGui::Button("Sort List")) {
				some_list.sort([](const int& a, const int& b) -> bool {
						return a < b;
					});
			}

			ImGui::DragInt("###VINPUT", &create_value); ImGui::SameLine();

			if (ImGui::Button("Push Front")) {
				some_list.push_front(create_value);
			} ImGui::SameLine();

			if (ImGui::Button("Push Back")) {
				some_list.push_back(create_value);
			}

			list_node<int>* cur = some_list.head;
			list_node<int>* to_remove = nullptr;
			while (cur) {
				ImGui::Text("List item: %d", cur->value);
				ImGui::SameLine();
				/* This mouthful of a function call... pain.
				 *
				 * It's because Dear ImGui uses element names as a unique
				 * ID, everything breaks when two elements have the same name.
				 * An ID can be passed after three #s in the name, though, so
				 * in this case we simply convert the pointer of the
				 * current element to a string and append that to the element
				 * name after three #s.
				 
				 * Might be faster to use a stack-allocated buffer and append the
				 * ID using `sprintf'... Instead of allocating on the three times here.*/
				if (ImGui::Button(std::string("Delete Item###" + std::to_string((unsigned long long)cur)).c_str())) {
					to_remove = cur;
				}

				cur = cur->next;
			}

			if (to_remove) {
				some_list.remove(to_remove);
			}
		}
		ImGui::End();

		/* Draw & update */
		ImGui::Render();
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	/* Free everything */
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplGlfw_Shutdown();

	ImGui::DestroyContext();

	glfwDestroyWindow(window);

	glfwTerminate();
}

/* Run a test. The function for the test must return true if the test passed
 * and return false if it failed. */
static void run_test(const char* name, std::function<bool()> func) {
	printf("Running test: '%s'... ", name);

	printf(func() ? "OK" : "FAILED");
	printf("\n");
}

/* Run all the tests */
void run_tests() {
	run_test("push_front", []() -> bool {
			list<int> l;
			l.push_front(2);
			l.push_front(5);
			return l.head->value == 5;
		});

	run_test("push_back", []() -> bool {
			list<int> l;
			l.push_back(2);
			l.push_back(5);
			return l.tail->value == 5;
		});

	run_test("count", []() -> bool {
			list<int> l;
			l.push_back(2);
			l.push_back(5);
			return l.count() == 2;
		});

	run_test("first", []() -> bool {
			list<int> l;
			l.push_front(2);
			l.push_front(5);
			return l.first()->value == 5;
		});

	run_test("last", []() -> bool {
			list<int> l;
			l.push_front(2);
			l.push_front(5);
			return l.last()->value == 2;
		});
}
