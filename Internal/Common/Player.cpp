#include "Player.h"

#include "../Offsets/Player.h"

void Player::getName()
{
	for (int i = 0; i < 15; i++) {
		this->name[i] = *reinterpret_cast<char*>(this->ptr + Name + i);
	}
}

void Player::getChampionName()
{
	for (int i = 0; i < 35; i++) {
		this->champion_name[i] = *reinterpret_cast<char*> (this->ptr + HeroName + i);
	}
}
										//void getPointer(); Собсна нахуя
float Player::getHealth()
{
	this->health = *reinterpret_cast<float*>(this->ptr + Health);
	return this->health;
}

float Player::getMana()
{
	this->mana = *reinterpret_cast<float*>(this->ptr + Mana);
	return this->mana;
}

Vector3 Player::getPosition()
{
	this->position = *reinterpret_cast<Vector3*>(this->ptr + Position);
	return this->position;
}

Vector2 Player::getDirection()
{	
	// Position.x + (Velocity * direction.x * time)
	return {};
} 

void Player::initialize()
{
	this->mana = this->getMana();
	this->health = this->getHealth();
	this->position = this->getPosition();
	this->direction = this->getDirection();
	this->getName();
	this->getChampionName();
}

Player::Player(uintptr_t pointer)
{
	this->ptr = pointer;
}
