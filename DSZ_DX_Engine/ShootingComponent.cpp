#include "ShootingComponent.h"
#include "Weapon.h"
#include "AProjectile.h"

void ShootingComponent::TryShoot()
{
	if (currentWeapon->bCanShoot)
 		currentWeapon->Shoot();
}

void ShootingComponent::SetCurrentWeapon(std::string weaponName)
{
	if (weapons.find(weaponName) != weapons.end())
	{
		currentWeapon = weapons[weaponName];
	}
	else
	{
		currentWeapon = nullptr;
	}
}

ShootingComponent::~ShootingComponent()
{
	auto it = weapons.begin();
	
	for (; it != weapons.end(); it++)
	{
		Weapon* w = (*it).second;
		weapons.erase(it);
		delete w;	
	}
}