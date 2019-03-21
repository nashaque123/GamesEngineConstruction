#include "HorseEnemy.h"

HorseEnemy::HorseEnemy(std::string spriteName, int numberOfFramesX, int numberOfFramesY, bool isAnimated, int frameWidth, int frameHeight) : EnemyEntity(spriteName, numberOfFramesX, numberOfFramesY, isAnimated, frameWidth, frameHeight)
{
}

HorseEnemy::~HorseEnemy()
{
}

//Horses will move across the screen from right to left
//When off the screen they will move back to the right hand side
void HorseEnemy::Update()
{
	Move(Vector2(-100.f, m_position.posY));

	if (m_position.posX <= -100.f)
		SetPosition(1200.f, m_position.posY);

	FireBomb();
}

//Random chance of a horse dropping a bullet
void HorseEnemy::FireBomb()
{
	int random = rand() % 15;

	if (random == 4)
		m_allowedToDropBomb = true;
	else
		m_allowedToDropBomb = false;
}

//Respawns by resetting position when game is restarted
void HorseEnemy::Respawn()
{
	SetPosition(1200.f, m_position.posY);
}