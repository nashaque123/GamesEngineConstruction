#pragma once
#include "NonShooterEntity.h"
class BulletEntity : public NonShooterEntity
{
public:
	BulletEntity(std::string spriteName, int numberOfFramesX = 1, int numberOfFramesY = 1, bool isAnimated = false, int frameWidth = 4, int frameHeight = 2);
	~BulletEntity();

	virtual void Update() override final;
	ESide GetSide() const override final { return m_side; }
	void SetSide(ESide side) { m_side = side; }

	bool PlayExplosionAnimation();

private:
	ESide m_side;
	const float bulletSpeedFactor{ 1.8f };
};

