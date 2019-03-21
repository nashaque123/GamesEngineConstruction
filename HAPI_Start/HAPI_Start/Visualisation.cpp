#include "Visualisation.h"
#include "Sprite.h"

Visualisation::Visualisation()
{
}

Visualisation::~Visualisation()
{
	for (auto i = m_spriteMap.begin(); i != m_spriteMap.end(); i++)
	{
		delete i->second;
	}
}

bool Visualisation::Initialise(int width, int height)
{
	//Creating a pointer for the screen data
	m_screen = HAPI.GetScreenPointer();

	m_screenWidth = width;
	m_screenHeight = height;

	//If Initialise fails to launch, end the program
	if (!HAPI.Initialise(m_screenWidth, m_screenHeight))
	{
		std::cerr << "Couldn't initialise" << std::endl;
		return false;
	}

	return true;
}

//Function to set a specific pixel to a new colour. RGB values and coordinates passed through parameters
void Visualisation::SetPixelToColour(int red, int green, int blue, int x, int y)
{
	CheckRGBvalues(red, green, blue);

	HAPI_TColour col(red, green, blue);

	int offset = (x + y * m_screenWidth) * 4;
	BYTE *screenPointer = m_screen + offset;

	memcpy(screenPointer, &col, 4);
}

//Clear screen to a value of grey scale
void Visualisation::GreyScaleClearScreen()
{
	m_screen = HAPI.GetScreenPointer();

	BYTE *screen = m_screen;
	memset(screen, 128, m_screenWidth*m_screenHeight * 4);
}

//Checks whether the RGB values passed through are within the correct bounds (0 to 255)
//Clamps the invalid value - if greater than 255, set at 255. If less than 0, set to 0.
void Visualisation::CheckRGBvalues(int &red, int &green, int &blue)
{
	if (red < 0)
		red = 0;
	else if (red > 255)
		red = 255;

	if (green < 0)
		green = 0;
	else if (green > 255)
		green = 255;

	if (blue < 0)
		blue = 0;
	else if (blue > 255)
		blue = 255;
}

//Loads texture and creates instance in map
bool Visualisation::CreateSprite(const std::string &filename, const std::string &name, int numberOfFramesX, int numberOfFramesY)
{
	Sprite *newSprite = new Sprite;

	if (!newSprite->LoadTexture(filename, numberOfFramesX, numberOfFramesY))
	{
		delete[] newSprite;
		return false;
	}

	m_spriteMap[name] = newSprite;

	return true;
}

//Blits the entire texture using memcpy
const void Visualisation::RenderFast(const std::string &name, float posX, float posY, const int frameNumber)
{
	if (m_spriteMap.find(name) == m_spriteMap.end())
		return;

	m_spriteMap.at(name)->RenderFast(m_screen, m_screenWidth, m_screenHeight, posX, posY, frameNumber);
}

//Blits the texture using alpha
const void Visualisation::Render(const std::string &name, float posX, float posY, const int frameNumber)
{
	if (m_spriteMap.find(name) == m_spriteMap.end())
		return;

	m_spriteMap.at(name)->Render(m_screen, m_screenWidth, m_screenHeight, posX, posY, frameNumber);
}
