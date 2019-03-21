#include "PlayerEntity.h"
#include <HAPI_lib.h>
#include <HAPI_InputCodes.h>

using namespace HAPISPACE;

PlayerEntity::PlayerEntity(std::string spriteName, int numberOfFramesX, int numberOfFramesY, bool isAnimated, int frameWidth, int frameHeight) : ShooterEntity(spriteName, numberOfFramesX, numberOfFramesY, isAnimated, frameWidth, frameHeight)
{
	m_collisionCost = 50;
}

PlayerEntity::~PlayerEntity()
{
}

void PlayerEntity::Update()
{
	ShooterEntity::Update();

	if (HAPI.GetControllerData(0).isAttached)
		XboxControllerMovement();

	KeyboardMovement();
	ClampPosition();
	SetControllerRumble();
}

//Checks input from xbox controller
void PlayerEntity::XboxControllerMovement()
{
	static const HAPI_TControllerData &data = HAPI.GetControllerData(0);

	int leftXValue = data.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X];
	int leftYValue = data.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y];

	if (leftXValue >= 15000)
	{
		if (leftYValue <= -15000)
		{
			m_position.posX += m_diagonalSpeed;
			m_position.posY += m_diagonalSpeed;
		}
		else if (leftYValue >= 15000)
		{
			m_position.posX += m_diagonalSpeed;
			m_position.posY -= m_diagonalSpeed;
		}
		else
			m_position.posX += m_speed;
	}
	else if (leftXValue <= -15000)
	{
		if (leftYValue <= -15000)
		{
			m_position.posX -= m_diagonalSpeed;
			m_position.posY += m_diagonalSpeed;
		}
		else if (leftYValue >= 15000)
		{
			m_position.posX -= m_diagonalSpeed;
			m_position.posY -= m_diagonalSpeed;
		}
		else
			m_position.posX -= m_speed;
	}
	else if (leftYValue <= -15000)
		m_position.posY += m_speed;
	else if (leftYValue >= 15000)
		m_position.posY -= m_speed;
}

//Plays the death animation and ends at final frame number
bool PlayerEntity::PlayDeathAnimation()
{
	if (m_frameNumber == 7)
		return true;
	else
		return false;
}

//Check input from keyboard
void PlayerEntity::KeyboardMovement()
{
	const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();

	if (keyData.scanCode[HK_RIGHT])
	{
		if (keyData.scanCode[HK_DOWN])
		{
			m_position.posX += m_diagonalSpeed;
			m_position.posY += m_diagonalSpeed;
		}
		else if (keyData.scanCode[HK_UP])
		{
			m_position.posX += m_diagonalSpeed;
			m_position.posY -= m_diagonalSpeed;
		}
		else
			m_position.posX += m_speed;
	}
	else if (keyData.scanCode[HK_LEFT])
	{
		if (keyData.scanCode[HK_DOWN])
		{
			m_position.posX -= m_diagonalSpeed;
			m_position.posY += m_diagonalSpeed;
		}
		else if (keyData.scanCode[HK_UP])
		{
			m_position.posX -= m_diagonalSpeed;
			m_position.posY -= m_diagonalSpeed;
		}
		else
			m_position.posX -= m_speed;
	}
	else if (keyData.scanCode[HK_DOWN])
		m_position.posY += m_speed;
	else if (keyData.scanCode[HK_UP])
		m_position.posY -= m_speed;
}

//Clamp position of player to certain moveable region
void PlayerEntity::ClampPosition()
{
	if (m_position.posX < 135)
		m_position.posX = 136.f;
	else if (m_position.posX > 800)
		m_position.posX = 799.f;
	
	if (m_position.posY < 550)
		m_position.posY = 551.f;
	else if (m_position.posY > 650)
		m_position.posY = 649.f;
}

//Rumble controller when...
void PlayerEntity::SetControllerRumble()
{
	if (m_health <= 0)
		HAPI.SetControllerRumble(0, 65535 / 2, 65535 / 2);
	else
		HAPI.SetControllerRumble(0, 0, 0);
}

//Checks if player is firing bullet
bool PlayerEntity::IsFiring()
{
	if (HAPI.GetControllerData(0).digitalButtons[HK_DIGITAL_B] || HAPI.GetKeyboardData().scanCode[HK_SPACE])
		return true;
	else
		return false;
}

//Resets health when game is restarted
void PlayerEntity::Respawn()
{
	m_health = 100;
	m_alive = true;
	m_animationStatus = EAnimationStateMachine::eAlive;
	SetPosition(Vector2(10.f, 200.f));
}