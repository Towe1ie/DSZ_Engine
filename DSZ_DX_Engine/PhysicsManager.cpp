#include "PhysicsManager.h"
#include "CircleComponent.h"
#include "DSZ_Math.h"
#include <iostream>

using namespace DirectX;

std::map<CollisionChannel, std::vector<ShapeComponent*>> PhysicsManager::collisionChannels;


CollisionCheckResult PhysicsManager::CheckCollision(CircleComponent* c1, CircleComponent* c2)
{
	CollisionCheckResult res;
	XMFLOAT2 diff = c1->GetWorldPosition() - c2->GetWorldPosition();

	res.overlap = Length(diff) < (c1->radius + c2->radius);

	return res;
}

void PhysicsManager::Update(GameTime& gameTime)
{
	// For each collision channel
	for (t_collisionChannels::iterator it = collisionChannels.begin(); it != collisionChannels.end(); it++)
	{
		std::vector<ShapeComponent*> shapes = (*it).second;
		std::vector<ShapeComponent*>::iterator s_it = shapes.begin();

		// For each shape in given collision channel
		for (s_it; s_it != shapes.end(); s_it++)
		{
			// For each channel that given shape needs to check collision
			for (std::map<CollisionChannel, bool>::iterator c_it = (*s_it)->checkChannels.begin(); c_it != (*s_it)->checkChannels.end(); c_it++)
			{
				if ((*c_it).second)
				{
					std::vector<ShapeComponent*> shapes_to_check = collisionChannels[(*c_it).first];
					CircleComponent* first = (CircleComponent*)*s_it;

					// For each shape in given channel
					bool foundOverlap = false;
					for (std::vector<ShapeComponent*>::iterator sc_it = shapes_to_check.begin(); sc_it != shapes_to_check.end(); sc_it++)
					{
						CircleComponent* second = (CircleComponent*)*sc_it;

						// Check if second shape allows collision with first shape 
						if (second->checkChannels[first->myChannel])
						{
							CollisionCheckResult res = CheckCollision(first, second);

							if (res.overlap)
							{
								foundOverlap = true;
								if (first->collisionState == CollisionState::NONE)
								{
									first->collisionState = CollisionState::OVERLAPED;
									if (first->OnOverlapBegin)
										first->OnOverlapBegin();
								}

								if (second->collisionState == CollisionState::NONE)
								{
									second->collisionState = CollisionState::OVERLAPED;
									if (second->OnOverlapBegin)
										second->OnOverlapBegin();
								}
							}
						}
					}

					if (first->collisionState == CollisionState::OVERLAPED && !foundOverlap)
					{
						first->collisionState = CollisionState::NONE;
						if (first->OnOverlapEnd)
							first->OnOverlapEnd();
					}
				}
			}
		}
	}
}