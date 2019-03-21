#include "ShooterEntity.h"

ShooterEntity::ShooterEntity(std::string spriteName, int numberOfFramesX, int numberOfFramesY, bool isAnimated, int frameWidth, int frameHeight) : WorldEntity(spriteName, numberOfFramesX, numberOfFramesY, isAnimated, frameWidth, frameHeight)
{
}

ShooterEntity::~ShooterEntity()
{
}

//Makes sure there is a delay to prevent shooters from constantly firing bullets
void ShooterEntity::Update()
{
	DWORD time = HAPI.GetTime();

	if (time - m_lastTimeBulletFired >= m_shootingTime && m_animationStatus != EAnimationStateMachine::eDead)
	{
		m_allowedToShoot = true;
		m_lastTimeBulletFired = HAPI.GetTime();
	}
	else
		m_allowedToShoot = false;
}