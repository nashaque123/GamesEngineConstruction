#include "BackgroundEntity.h"

BackgroundEntity::BackgroundEntity(std::string spriteName, int numberOfFramesX, int numberOfFramesY, bool isAnimated) : NonShooterEntity(spriteName, numberOfFramesX, m_noOfFramesY, isAnimated)
{
}

BackgroundEntity::~BackgroundEntity()
{
}

void BackgroundEntity::Update()
{
	//Moves background by offset speed every frame
	SetPosition(m_position.posX - m_speed, m_position.posY);

	if (m_position.posX < -m_backWidth)
		SetPosition(m_backWidth, m_position.posY);
}
