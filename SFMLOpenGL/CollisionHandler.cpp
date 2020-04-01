#include "CollisionHandler.h"

bool CollisionHandler::isColliding(c2Circle t_lightningHit, c2AABB t_gameObject)
{
	return c2CircletoAABB(t_lightningHit, t_gameObject);
}
