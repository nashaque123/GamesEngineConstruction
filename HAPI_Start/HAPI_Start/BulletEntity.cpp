#include "BulletEntity.h"

BulletEntity::BulletEntity(std::string spriteName, int numberOfFramesX, int numberOfFramesY, bool isAnimated, int frameWidth, int frameHeight) : NonShooterEntity(spriteName, numberOfFramesX, numberOfFramesY, isAnimated, frameWidth, frameHeight)
{
	m_health = 10;
	m_collisionCost = 10;
	m_alive = false;
}

BulletEntity::~BulletEntity()
{
}

void BulletEntity::Update()
{
	//If alive then travels in correct direction depending on who fired it
	if (m_alive)
	{
		if (m_side == ESide::ePlayer)
			m_position.posX += m_speed * bulletSpeedFactor;
		else if (m_side == ESide::eEnemy)
			m_position.posX -= m_speed * bulletSpeedFactor;
		else if (m_side == ESide::eBomb)
			m_position.posY += m_speed * bulletSpeedFactor;
	}

	//Marks alive as false if off screen
	if (m_position.posX <= 0 || m_position.posX >= 1100 || m_position.posY >= 900)
	{
		m_frameNumber = 0;
		m_alive = false;
	}
}

bool BulletEntity::PlayExplosionAnimation()
{
	if (m_frameNumber == 12)
	{
		m_frameNumber = 0;
		return true;
	}
	else
		return false;
}