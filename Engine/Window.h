#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>
using namespace std;

enum WindowFlasgs {
	INVISIBLE = 0x1,
	FULLSCREEN = 0X2,
	BORDERLESS = 0X4
};
class Window
{
private:
	SDL_Window* window;
	int screenWidth;
	int screenHeight;
public:
	Window();
	~Window();
	void swapWindow();
	int getScreenWidth() { return screenWidth; }
	int getScreenHeight() { return screenHeight; }
	int create(string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);
};

