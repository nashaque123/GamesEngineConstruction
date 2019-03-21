#pragma once
#include "WorldEntity.h"
class NonShooterEntity : public WorldEntity
{
public:
	NonShooterEntity(std::string spriteName, int numberOfFramesX = 1, int numberOfFramesY = 1, bool isAnimated = false, int frameWidth = 64, int frameHeight = 64);
	virtual ~NonShooterEntity();

	virtual void Update() = 0;
	virtual ESide GetSide() const = 0;
};

