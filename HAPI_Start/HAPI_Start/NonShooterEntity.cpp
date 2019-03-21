#include "NonShooterEntity.h"

NonShooterEntity::NonShooterEntity(std::string spriteName, int numberOfFramesX, int numberOfFramesY, bool isAnimated, int frameWidth, int frameHeight) : WorldEntity(spriteName, numberOfFramesX, numberOfFramesY, isAnimated, frameWidth, frameHeight)
{
}

NonShooterEntity::~NonShooterEntity()
{
}
