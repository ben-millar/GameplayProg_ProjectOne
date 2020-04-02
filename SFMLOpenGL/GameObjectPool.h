#ifndef GAME_OBJECT_POOL_H
#define GAME_OBJECT_POOL_H

#include <array>
#include <iostream>

#include "GLOBALS.h"
#include "Debug.h"
#include "GameObject.h"

class GameObjectPool
{
public:

	GameObjectPool();

	/// <summary>
	/// @brief Initialise a new cube
	/// </summary>
	void create();

	/// <summary>
	/// @brief Kill off a game object and return it to the available pool
	/// </summary>
	/// <param name="t_objToKill">Reference to specific object to murder</param>
	void kill(GameObject& t_objToKill);

	/// <summary>
	/// @brief Returns a vector of pointers to active objects
	/// </summary>
	std::vector<GameObject*> getActive();

private:
	int static const POOL_SIZE{ 30 };
	std::array<GameObject, POOL_SIZE> m_pool;

	// First game object available to use
	GameObject* m_firstAvailable;
};

#endif // !GAME_OBJECT_POOL_H