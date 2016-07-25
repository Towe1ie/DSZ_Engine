#include "AEnemy.h"
#include "BasicGeomentry.h"

AEnemy::AEnemy()
{
	circleComponent = new CircleComponent();
	circleComponent->ChangeChannel(CollisionChannel::ENEMY);
	circleComponent->radius = 1.f;
	AttachComponent(circleComponent);
	sceneComponent->position = XMFLOAT2(3.f, 5.f);
	circleComponent->checkChannels[CollisionChannel::PLAYER] = true;
	circleComponent->rootComponent = sceneComponent;
}

void AEnemy::Render()
{
	DebugDrawCircle(circleComponent->GetWorldPosition(), circleComponent->radius, XMFLOAT4(0.0f, 0.f, 1.f, 1.f), 10);
}

void AEnemy::Update(GameTime& gameTime)
{
}