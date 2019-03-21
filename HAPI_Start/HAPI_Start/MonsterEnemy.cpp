#include "MonsterEnemy.h"

MonsterEnemy::MonsterEnemy(std::string spriteName, int numberOfFramesX, int numberOfFramesY, bool isAnimated, int frameWidth, int frameHeight) : EnemyEntity(spriteName, numberOfFramesX, numberOfFramesY, isAnimated, frameWidth, frameHeight)
{
	m_health = 50;
	m_collisionCost = 30;
}

MonsterEnemy::~MonsterEnemy()
{
}

//Moves following a basic path by going up and down
//Resets position to the right hand side when off the screen
void MonsterEnemy::Update()
{
	ShooterEntity::Update();

	if (m_movingUp)
		Move(Vector2(-100.f, 500.f));
	else
		Move(Vector2(-100.f, 700.f));

	if (m_position.posY >= 690.f)
		m_movingUp = true;
	else if (m_position.posY <= 510.f)
		m_movingUp = false;

	if (m_position.posX < -50.f)
		SetPosition(Vector2(1000.f, m_position.posY));
}

//Randomly starts attack animation to fire a bullet
bool MonsterEnemy::PlayAttackAnimation()
{
	int shootingChance = rand() % 7;

	if (m_animationStatus == EAnimationStateMachine::eAttack || shootingChance == 4)
	{
		m_animationStatus = EAnimationStateMachine::eAttack;
		return true;
	}
	else
		return false;
}

//Checks if attack animation is finished then fires bullet
bool MonsterEnemy::IsFiring()
{
	m_numOfFramesInAttackAnimation++;

	if (m_numOfFramesInAttackAnimation == 5)
	{
		m_animationStatus = EAnimationStateMachine::eAlive;
		m_numOfFramesInAttackAnimation = 0;
		return true;
	}
	else
		return false;
}

//Plays the death animation and ends at final frame number
bool MonsterEnemy::PlayDeathAnimation()
{
	if (m_frameNumber == 17)
		return true;
	else
		return false;
}

//Randomly respawns enemy when health is 0 or game is restarted
void MonsterEnemy::Respawn()
{
	m_alive = false;

	int randRespawn = rand() % 50;

	if (randRespawn == 4)
	{
		m_health = 50;
		m_alive = true;
		SetPosition(Vector2(1100.f, 600.f));
		m_animationStatus = EAnimationStateMachine::eAlive;
	}
}
