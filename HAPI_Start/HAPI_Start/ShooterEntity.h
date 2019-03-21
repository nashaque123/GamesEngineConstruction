#pragma once
#include "WorldEntity.h"
class ShooterEntity : public WorldEntity
{
public:
	ShooterEntity(std::string spriteName, int numberOfFramesX = 1, int numberOfFramesY = 1, bool isAnimated = false, int frameWidth = 64, int frameHeight = 64);
	virtual ~ShooterEntity();

	virtual void Update() override;
	virtual ESide GetSide() const override { return ESide(); }
	virtual bool IsFiring() = 0;
	virtual bool PlayAttackAnimation() = 0;
	virtual bool PlayDeathAnimation() = 0;
	virtual	void Respawn() = 0;;

	bool GetAllowedToShoot() { return m_allowedToShoot; }
	bool GetAllowedToDropBomb() { return m_allowedToDropBomb; }

protected:
	DWORD m_lastTimeBulletFired{ 300 };
	DWORD m_shootingTime{ 300 };
	bool m_allowedToShoot{ false }, m_allowedToDropBomb{ false };

	int m_numOfFramesInAttackAnimation{ 0 };
};