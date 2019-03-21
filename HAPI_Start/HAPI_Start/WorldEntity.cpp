#include "WorldEntity.h"
#include "Visualisation.h"

WorldEntity::WorldEntity(std::string spriteName, int numberOfFramesX, int numberOfFramesY, bool isAnimated, int frameWidth, int frameHeight) : m_spriteName(spriteName)
{
	m_noOfFramesX = numberOfFramesX;
	m_noOfFramesY = numberOfFramesY;
	m_frameWidth = frameWidth;
	m_frameHeight = frameHeight;
	m_isAnimated = isAnimated;
}

WorldEntity::~WorldEntity()
{
}

void WorldEntity::Render(Visualisation &graphics)
{
	graphics.Render(m_spriteName, m_position.posX, m_position.posY, m_frameNumber);
}

void WorldEntity::RenderFast(Visualisation &graphics)
{
	graphics.RenderFast(m_spriteName, m_position.posX, m_position.posY, m_frameNumber);
}

//Plays correct animation depending on status
void WorldEntity::AnimationStateMachine()
{
	switch (m_animationStatus)
	{
	case EAnimationStateMachine::eAlive:
		RunAnimation();
		break;
	case EAnimationStateMachine::eDead:
		DeathAnimation();
		break;
	case EAnimationStateMachine::eAttack:
		AttackAnimation();
		break;
	default:
		RunAnimation();
		break;
	}
}

//Animation for running
void WorldEntity::RunAnimation()
{
	DWORD time = HAPI.GetTime();

	if (time - m_lastTimeAnimated >= m_animationTime)
	{
		m_frameNumber++;

		if (m_frameNumber >= m_noOfFramesX)
			m_frameNumber = 0;

		m_lastTimeAnimated = HAPI.GetTime();
	}
}

//Animation for dying
void WorldEntity::DeathAnimation()
{
	if (m_frameNumber < m_noOfFramesX * (m_noOfFramesY - 1))
		m_frameNumber = m_noOfFramesX * (m_noOfFramesY - 1);

	DWORD time = HAPI.GetTime();

	if (time - m_lastTimeAnimated >= m_animationTime)
	{
		m_frameNumber++;

		if (m_frameNumber >= m_noOfFramesX * m_noOfFramesY)
			m_frameNumber = m_noOfFramesX * (m_noOfFramesY - 1);

		m_lastTimeAnimated = HAPI.GetTime();
	}
}

//Animatino for attack
void WorldEntity::AttackAnimation()
{
	if (m_frameNumber < m_noOfFramesX)
		m_frameNumber = m_noOfFramesX;

	DWORD time = HAPI.GetTime();

	if (time - m_lastTimeAnimated >= m_animationTime)
	{
		m_frameNumber++;

		if (m_frameNumber >= m_noOfFramesX * 2)
			m_frameNumber = m_noOfFramesX;

		m_lastTimeAnimated = HAPI.GetTime();
	}
}

//Checks for collisions between world entities
bool WorldEntity::CheckForCollision(const WorldEntity &other)
{
	//Cannot collide if sides are the same or neutral
	//Also cannot collide if entity is dying
	if (GetSide() == ESide::eNeutral || other.GetSide() == ESide::eNeutral || GetSide() == other.GetSide()
		|| GetAnimationStatus() == EAnimationStateMachine::eDead || other.GetAnimationStatus() == EAnimationStateMachine::eDead)
		return false;

	Rectangle thisRect{ m_frameWidth, m_frameHeight };
	Rectangle otherRect{ other.m_frameWidth, other.m_frameHeight };

	thisRect.Translate((int)m_position.posX, (int)m_position.posY);
	otherRect.Translate((int)other.m_position.posX, (int)other.m_position.posY);

	if (thisRect.CompletelyOutside(otherRect))
		return false;
	else
		return true;
}

//Entity loses health
void WorldEntity::TakeDamage(int damage)
{
	m_health -= damage;

	if (m_health <= 0)
		m_animationStatus = EAnimationStateMachine::eDead;
}
