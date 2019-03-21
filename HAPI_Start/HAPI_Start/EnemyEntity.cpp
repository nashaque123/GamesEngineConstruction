#include "EnemyEntity.h"

EnemyEntity::EnemyEntity(std::string spriteName, int numberOfFramesX, int numberOfFramesY, bool isAnimated, int frameWidth, int frameHeight) : ShooterEntity(spriteName, numberOfFramesX, numberOfFramesY, isAnimated, frameWidth, frameHeight)
{
}

EnemyEntity::~EnemyEntity()
{
}

void EnemyEntity::Update()
{
}

//AI moves to destination by comparing positions and moving in the direction it needs to go
void EnemyEntity::Move(Vector2 destination)
{
	if (m_position.posX > destination.posX)
	{
		if (m_position.posY > destination.posY)
		{
			m_position.posX -= m_enemySpeedFactor * m_diagonalSpeed;
			m_position.posY -= m_enemySpeedFactor * m_diagonalSpeed;
		}
		else if (m_position.posY < destination.posY)
		{
			m_position.posX -= m_enemySpeedFactor * m_diagonalSpeed;
			m_position.posY += m_enemySpeedFactor * m_diagonalSpeed;
		}
		else
			m_position.posX -= m_speed;
	}
	else if (m_position.posX < destination.posX)
	{
		if (m_position.posY > destination.posY)
		{
			m_position.posX += m_enemySpeedFactor * m_diagonalSpeed;
			m_position.posY -= m_enemySpeedFactor * m_diagonalSpeed;
		}
		else if (m_position.posY < destination.posY)
		{
			m_position.posX += m_enemySpeedFactor * m_diagonalSpeed;
			m_position.posY += m_enemySpeedFactor * m_diagonalSpeed;
		}
		else
			m_position.posX += m_speed;
	}
	else if (m_position.posY > destination.posY)
		m_position.posY -= m_speed;
	else if (m_position.posY < destination.posY)
		m_position.posY += m_speed;
}
