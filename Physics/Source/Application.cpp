
#include "Application.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

#include "Scenes/SceneManager.h"

GLFWwindow* Application::m_window = NULL;
SceneManager * SceneManager::only_instance = 0;
StopWatch Application::m_timer;
bool Application::exitApp = false;

bool windowResized = false;
int m_width, m_height;

//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}


void resize_callback(GLFWwindow* window, int w, int h)
{
	m_width = w;
	m_height = h;
	glViewport(0, 0, w, h);

	windowResized = true;
	cout << "RESIZED WINDOW" << endl;
}

bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}
bool Application::IsMousePressed(unsigned short key) //0 - Left, 1 - Right, 2 - Middle
{
	return glfwGetMouseButton(m_window, key) != 0;
}
void Application::GetCursorPos(double *xpos, double *ypos)
{
	glfwGetCursorPos(m_window, xpos, ypos);
}
int Application::GetWindowWidth()
{
	return m_width;
}
int Application::GetWindowHeight()
{
	return m_height;
}

bool Application::GetWindowResized()
{
	return windowResized;
}

void Application::SetWindowResized(bool resized)
{
	windowResized = resized;
}

Application::Application()
{
}

Application::~Application()
{
}

void Application::Init()
{
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 
	glfwWindowHint(GLFW_MAXIMIZED, true);
	glfwWindowHint(GLFW_DECORATED, true);

	//Create a window and create its OpenGL context
	b_fullscreen = false;
	m_width = GetSystemMetrics(SM_CXSCREEN);
	m_height = GetSystemMetrics(SM_CYSCREEN);
	m_window = glfwCreateWindow(m_width, m_height, "Physics", NULL, NULL);
	//m_window = glfwCreateWindow(m_width, m_height, "Physics", glfwGetPrimaryMonitor(), NULL);
	
	//If the window couldn't be created
	if (!m_window)
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the window callback
	glfwSetWindowSizeCallback(m_window, resize_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) 
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}

	exitApp = false;
}

void Application::Run()
{
	//Main Loop
	createScene();
	SceneManager::GetInstance().getScene()->Init();

	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame

							 //Check if the ESC key had been pressed or if the window had been closed
	while (!glfwWindowShouldClose(m_window) && !exitApp)
	{
		// Update Mouse Position
		double mouse_currX, mouse_currY;
		glfwGetCursorPos(m_window, &mouse_currX, &mouse_currY);
		// Update Keyboard Input
		for (int i = 0; i < KeyboardController::MAX_KEYS; ++i)
			KeyboardController::GetInstance().UpdateKeyboardStatus(i, IsKeyPressed(i));

		if (KeyboardController::GetInstance().IsKeyPressed(VK_TAB))
		{
			cout << "TAB PRESSED";
			if (!b_fullscreen)
			{
				cout << "GOING FULLSCREEN" << endl;
				glfwSetWindowMonitor(m_window, glfwGetPrimaryMonitor(), 0, 0, m_width, m_height, 60);
				glfwWindowHint(GLFW_DECORATED, true);

				m_width = GetSystemMetrics(SM_CXSCREEN);
				m_height = GetSystemMetrics(SM_CYSCREEN);

				b_fullscreen = true;
			}
			else if (b_fullscreen)
			{
				cout << "GOING FULLSCREEN WINDOWED" << endl;
				glfwSetWindowMonitor(m_window, NULL, 0, 0, m_width, m_height, 60);
				glfwWindowHint(GLFW_DECORATED, true);

				m_width = GetSystemMetrics(SM_CXSCREEN);
				m_height = GetSystemMetrics(SM_CYSCREEN);

				b_fullscreen = false;
			}
		}

		SceneManager::GetInstance().sceneUpdate();

		KeyboardController::GetInstance().EndFrameUpdate();
	}				

	SceneManager::GetInstance().getScene()->Exit();
	delete SceneManager::GetInstance().getScene();
}

void Application::createScene()
{	
}

void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}
