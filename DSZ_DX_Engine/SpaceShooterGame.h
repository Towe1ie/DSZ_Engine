#pragma once

#include "Game.h"

class SpaceShooterGame : public Game
{
public:
	virtual void LoadContent() override;
	virtual void Update(GameTime& gameTime) override;
	virtual void Render() override;
	virtual void UnloadContent() override;
};