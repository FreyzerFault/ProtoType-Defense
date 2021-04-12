// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "GLDebugging.h"
#include "GlobalParameters.h"
#include "Renderer.h"

#include "TestClearColor.h"
#include "TestSprite.h"
#include "TestBatchRendering.h"
#include "TestDynamicSprites.h"
#include "TestDynamicBuffer.h"
#include "TestThreads.h"
#include "TestShootDeltaTime.h"

#include "DeltaTime.h"



// IMGUI
static void imGuiShowWindow(glm::vec3 &translation) // NO ESTA EN USO
{
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	/*if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);*/

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
		            ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}
}




int main(void)
{
	if (!glfwInit())
		return -1;

	GLFWwindow* window = glfwCreateWindow(
		(int)windowWidth, (int)windowHeight, 
		"Guapo el que lo lea", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);

	GLgetVersion(); // Muestra la version de OpenGL por consola

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "GlewInit Error" << std::endl;

	{

		// BLENDING:
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)); // src * alpha + destination * (1 - alpha)

		const Renderer renderer;

		//Setup IMGUI
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init((const char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));


		// TESTS
		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu = new test::TestMenu(currentTest);
		currentTest = testMenu;

		testMenu->addTest<test::TestClearColor>("Clear Color");
		testMenu->addTest<test::TestSprite>("Sprite");
		testMenu->addTest<test::TestBatchRendering>("Batch Rendering");
		testMenu->addTest<test::TestDynamicSprites>("Dynamic Sprites");
		testMenu->addTest<test::TestDynamicBuffer>("Dynamic Buffer");
		testMenu->addTest<test::TestThreads>("Threads");
		testMenu->addTest<test::TestShootDeltaTime>("Delta Time Shooting");

		float lastFrameTime = (float) glfwGetTime();

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			Renderer::clear();
			Renderer::setClearColor();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			if (currentTest)
			{
				// DELTA TIME
				const float time = (float) glfwGetTime(); // Secs
				const DeltaTime deltaTime = time - lastFrameTime;
				lastFrameTime = time;
				
				currentTest->onUpdate(deltaTime);
				currentTest->onRender();
				ImGui::Begin("Test");

				// Return to Tests Menu
				if (currentTest != testMenu && ImGui::Button("<-"))
				{
					currentTest = testMenu;
				}
				
				currentTest->onImGuiRender();
				ImGui::End();
			}


			//Render ImGui
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		delete currentTest;
		if (currentTest != testMenu)
			delete testMenu;
	}// End of Scope para que glfwTerminate() no de errores de OpenGL

	

	// Shutdown ImGui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	// Si guardamos objetos de OpenGL como VBO, IBO, VAO,... en la pila, se intentará liberar los recursos al acabar el programa
	//  pero como al usar glfwTerminate() el contexto de OpenGL desaparece, OpenGL reproduce errores porque necesita
	//  un contexto para eliminar sus objetos
	return 0;
}

