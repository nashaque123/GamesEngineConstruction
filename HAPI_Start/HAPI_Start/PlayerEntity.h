#pragma once
#include "ShooterEntity.h"
class PlayerEntity : public ShooterEntity
{
public:
	PlayerEntity(std::string spriteName, int numberOfFramesX = 1, int numberOfFramesY = 1, bool isAnimated = false, int frameWidth = 64, int frameHeight = 64);
	~PlayerEntity();

	void Update() override final;
	ESide GetSide() const override final { return ESide::ePlayer; }
	bool IsFiring() override final;
	bool PlayAttackAnimation() override final { return true; }
	bool PlayDeathAnimation() override final;
	void Respawn() override final;

	void XboxControllerMovement();
	void KeyboardMovement();
	void ClampPosition();
	void SetControllerRumble();
};