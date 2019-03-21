#pragma once
#include "EnemyEntity.h"

class MonsterEnemy : public EnemyEntity
{
public:
	MonsterEnemy(std::string spriteName, int numberOfFramesX = 1, int numberOfFramesY = 1, bool isAnimated = false, int frameWidth = 64, int frameHeight = 64);
	~MonsterEnemy();

	void Update() override final;
	bool PlayAttackAnimation() override final;
	bool IsFiring() override final;
	bool PlayDeathAnimation() override final;

	void Respawn() override final;

private:
	bool m_movingUp{ false };
	bool m_isShooting{ false };
};

