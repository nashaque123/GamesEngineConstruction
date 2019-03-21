#pragma once
#include "ShooterEntity.h"
class EnemyEntity : public ShooterEntity
{
public:
	EnemyEntity(std::string spriteName, int numberOfFramesX = 1, int numberOfFramesY = 1, bool isAnimated = false, int frameWidth = 64, int frameHeight = 64);
	virtual ~EnemyEntity();

	virtual void Update() override;
	virtual ESide GetSide() const override final { return ESide::eEnemy; }

	void Move(Vector2 destination);

protected:
	const float m_enemySpeedFactor{ 0.7f };
};

