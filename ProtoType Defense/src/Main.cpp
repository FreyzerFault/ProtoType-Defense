// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "GLDebugging.h"

#include "WindowManager.h"

int main(void)
{
	// GLFW
	if (!glfwInit())
		return -1;

	{
		WindowManager windowManager(1280, 720, "Prototype Defence", 2);

		if (!windowManager.getWindow())
		{
			glfwTerminate();
			return -1;
		}

		GLgetVersion();

		// Rendering Frequency (1 screen update per frame)
		glfwSwapInterval(1);
		
		// GLEW
		if (glewInit() != GLEW_OK)
			std::cout << "GlewInit Error" << std::endl;

		windowManager.setup();

		
		windowManager.renderingLoop();

		
		windowManager.shutdown();
	}
	// End of Scope para que glfwTerminate() no de errores de OpenGL
	
	glfwTerminate();
	// Si guardamos objetos de OpenGL como VBO, IBO, VAO,... en la pila, se intentará liberar los recursos al acabar el programa
	//  pero como al usar glfwTerminate() el contexto de OpenGL desaparece, OpenGL reproduce errores porque necesita
	//  un contexto para eliminar sus objetos
	return 0;
}

