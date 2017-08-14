
#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "HardwareControllers\KeyboardController.h"
#include "FileReading\MusicPlayer.h"

class Application
{
public:
	static Application& GetInstance()
	{
		static Application app;
		return app;
	}
	void Init();
	void Run();
	static void Exit();
	void createScene();
	static bool IsKeyPressed(unsigned short key);
	static bool IsMousePressed(unsigned short key);
	static void GetCursorPos(double *xpos, double *ypos);
	static int GetWindowWidth();
	static int GetWindowHeight();
	static bool GetWindowResized();
	static void SetWindowResized(bool resized);
	static GLFWwindow* m_window;
	static StopWatch m_timer;	
	Application();
	~Application();

	static bool exitApp;
	bool b_fullscreen;
private:

};

static const unsigned char FPS = 60; // FPS of this game
static const unsigned int frameTime = 1000 / FPS; // time for each frame

#endif