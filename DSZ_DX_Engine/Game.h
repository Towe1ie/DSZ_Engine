#pragma once

class GameTime;

class Game
{
public:
	virtual void LoadContent() = 0;
	virtual void Update(GameTime &gameTime) = 0;
	virtual void Render() = 0;
	virtual void UnloadContent() = 0;
};
