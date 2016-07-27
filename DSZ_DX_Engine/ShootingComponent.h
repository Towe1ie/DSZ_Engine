#pragma once

#include "Component.h"
#include <map>
#include <string>

class Weapon;

class ShootingComponent : public Component
{
public:
	~ShootingComponent();

	void TryShoot();
	void SetCurrentWeapon(std::string weaponName);

	std::map<std::string, Weapon*> weapons;

private:
	Weapon* currentWeapon = nullptr;
};