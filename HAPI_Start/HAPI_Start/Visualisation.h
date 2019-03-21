#pragma once
#include <HAPI_lib.h>
#include <unordered_map>
#include "Rectangle.h"
#include "EAnimationStateMachine.h"

using namespace HAPISPACE;

class Sprite;

class Visualisation
{
public:
	Visualisation();
	~Visualisation();
	bool Initialise(int width, int height);

	void GreyScaleClearScreen();
	void SetPixelToColour(int red, int green, int blue, int x, int y);
	void CheckRGBvalues(int &red, int &green, int &blue);

	bool CreateSprite(const std::string &filename, const std::string &name, int numberOfFramesX = 1, int numberOfFramesY = 1);

	const void RenderFast(const std::string &name, float m_posX, float m_posY, const int frameNumber);
	const void Render(const std::string &name, float m_posX, float m_posY, const int frameNumber);

private:
	int m_screenWidth;
	int m_screenHeight;
	BYTE* m_screen{ nullptr };

	bool animate = false;

	std::unordered_map <std::string, Sprite*> m_spriteMap;
};

