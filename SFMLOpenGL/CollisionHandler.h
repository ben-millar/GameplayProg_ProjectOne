#pragma once

#include "tinyc2.h"

class CollisionHandler
{
public:

	static bool isColliding(c2Circle t_lightningHit, c2AABB t_gameObject);
};