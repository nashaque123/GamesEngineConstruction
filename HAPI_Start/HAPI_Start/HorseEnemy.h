#pragma once
#include "EnemyEntity.h"

class HorseEnemy : public EnemyEntity
{
public:
	HorseEnemy(std::string spriteName, int numberOfFramesX = 1, int numberOfFramesY = 1, bool isAnimated = false, int frameWidth = 64, int frameHeight = 64);
	~HorseEnemy();

	void Update() override final;
	bool IsFiring() override final { return false; }
	bool PlayAttackAnimation() override final { return true; }
	bool PlayDeathAnimation() override final { return false; }
	void Respawn() override final;

private:
	void FireBomb();
};

