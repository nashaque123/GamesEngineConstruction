#include "Sprite.h"
#include "Rectangle.h"

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
	delete[] m_texture;
}

//Loads the texture or outputs error message if incorrect
bool Sprite::LoadTexture(const std::string &filename, const int numberOfFramesX, const int numberOfFramesY)
{
	if (!HAPI.LoadTexture(filename, &m_texture, m_textureWidth, m_textureHeight)) {
		HAPI.UserMessage("Attempting to load a missing texture!", "Error!");
		return false;
	}

	m_frameWidth = m_textureWidth / numberOfFramesX;
	m_frameHeight = m_textureHeight / numberOfFramesY;
	m_noOfFramesX = numberOfFramesX;
	m_noOfFramesY = numberOfFramesY;

	return true;
}

//Renders the sprite without checking alpha values
void Sprite::RenderFast(BYTE *screen, const int &screenWidth, const int &screenHeight, float posX, float posY, const int frameNumber)
{
	static Rectangle screenRect(screenWidth, screenHeight);
	m_textureRect = { m_textureWidth, m_textureHeight };

	m_textureRect.ClipBlit(screenRect, m_textureRect, (int)posX, (int)posY);

	if (posX < 0)
		posX = 0;

	if (posY < 0)
		posY = 0;

	int* screenPointer = ((int*)screen) + ((int)posX + (int)posY * screenWidth) ;
	texturePnter = m_texture + (m_textureRect.left + m_textureRect.top * m_textureWidth) * 4;

	for (int y = m_textureRect.top; y < m_textureRect.bottom; y++)
	{
		for (int x = m_textureRect.left; x < m_textureRect.right; x++)
		{
			*(screenPointer++) = *((int*)texturePnter);
			texturePnter += 4;
		}
		screenPointer += (screenWidth - m_textureRect.Width()) ;
		texturePnter += (m_textureWidth - m_textureRect.Width()) * 4;
	}
}

//Blits the texture checking alpha and blending it to the background
void Sprite::Render(BYTE *screen, const int &screenWidth, const int &screenHeight, float posX, float posY, const int frameNumber)
{
	static Rectangle screenRect(screenWidth, screenHeight);
	m_frameRect = { m_frameWidth, m_frameHeight };

	endOfLineScreenIncrement = (screenWidth - m_frameRect.Width()) * 4;
	endOfTextureIncrement = (m_textureWidth - m_frameRect.Width()) * 4;

	int framesX = frameNumber % m_noOfFramesX;
	int framesY = std::max((frameNumber / m_noOfFramesX), 0);

	m_frameRect.Translate((int)posX, (int)posY);

	//Checks if on screen
	if (!(m_frameRect.CompletelyOutside(screenRect)))
	{
		//Checks if completely or partially on - clips it if partial
		if (!(screenRect.CompletelyContains(m_frameRect)))
		{			
			m_frameRect.Translate((int)-posX, (int)-posY);
			m_frameRect.ClipBlit(screenRect, m_frameRect, (int)posX, (int)posY);

			if (posX < 0)
				posX = 0;

			if (posY < 0)
				posY = 0;
		}
		else
			m_frameRect.Translate((int)-posX, (int)-posY);

		m_frameRect.Translate(framesX * m_frameWidth, framesY * m_frameHeight);

		endOfLineScreenIncrement = (screenWidth - m_frameRect.Width()) * 4;
		endOfTextureIncrement = (m_textureWidth - m_frameRect.Width()) * 4;

		screenPnter = screen + ((int)posX + (int)posY * screenWidth) * 4;
		texturePnter = m_texture + (m_frameRect.left + m_frameRect.top * m_textureWidth) * 4;

		for (int y = m_frameRect.top; y < m_frameRect.bottom; y++)
		{
			for (int x = 0; x < m_frameRect.Width(); x++)
			{
				BYTE alpha = texturePnter[3];

				//Uses memcpy if alpha is 255
				if (alpha == 255)
				{
					memcpy(screenPnter, texturePnter, 4);
				}
				else if (alpha > 0) //Will do nothing if the alpha is 0
				{
					BYTE red = texturePnter[0];
					BYTE green = texturePnter[1];
					BYTE blue = texturePnter[2];

					screenPnter[0] = screenPnter[0] + ((alpha*(red - screenPnter[0])) >> 8);
					screenPnter[1] = screenPnter[1] + ((alpha*(green - screenPnter[1])) >> 8);
					screenPnter[2] = screenPnter[2] + ((alpha*(blue - screenPnter[2])) >> 8);

				}

				texturePnter += 4;
				screenPnter += 4;
			}

			screenPnter += endOfLineScreenIncrement;
			texturePnter += endOfTextureIncrement;
		}
	}
}