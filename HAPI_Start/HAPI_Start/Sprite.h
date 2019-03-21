#pragma once
#include <HAPI_lib.h>
#include <HAPI_InputCodes.h>
#include "Rectangle.h"

using namespace HAPISPACE;

class Sprite
{
public:
	Sprite();
	~Sprite();
	bool LoadTexture(const std::string &filename, const int numberOfFramesX = 1, const int numberOfFramesY = 1);

	void RenderFast(BYTE *screen, const int &screenWidth, const int &screenHeight, float posX, float posY, const int frameNumber);
	void Render(BYTE *screen, const int &screenWidth, const int &screenHeight, float posX, float posY, const int frameNumber);

private:
	int m_textureWidth{ 0 }, m_textureHeight{ 0 };
	BYTE* m_texture{ nullptr };
	Rectangle m_textureRect;
	Rectangle m_frameRect;

	int m_frameWidth, m_frameHeight, m_noOfFramesX, m_noOfFramesY;

	BYTE *screenPnter{ nullptr };
	BYTE *texturePnter{ nullptr };

	int endOfLineScreenIncrement;
	int endOfTextureIncrement;
};

