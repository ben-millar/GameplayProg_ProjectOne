#include "GameObjectPool.h"

GameObjectPool::GameObjectPool()
{
	// init first in list
	m_firstAvailable = &m_pool.at(0);

	// init middle of list
	for (int i = 0; i < POOL_SIZE - 1; i++)
	{
		m_pool.at(i).setNext(&m_pool.at(i+1));
	}

	// init last in list
	m_pool.at(POOL_SIZE - 1).setNext(nullptr);
}

///////////////////////////////////////////////////////////////

void GameObjectPool::create()
{
	// ensure there is a projectile available
	assert(m_firstAvailable != nullptr);

	// move our first available to next available projectile
	GameObject* newObj = m_firstAvailable;
	m_firstAvailable = newObj->getNext();

	newObj->init();

	DEBUG_MSG("Creating new cube");
}

///////////////////////////////////////////////////////////////

void GameObjectPool::kill(GameObject& t_objToKill)
{
	// add back to our linked list
	t_objToKill.setNext(m_firstAvailable);
	m_firstAvailable = &t_objToKill;

	// set inactive
	t_objToKill.m_active = false;

	DEBUG_MSG("Killing cube :'(");
}

///////////////////////////////////////////////////////////////

std::vector<GameObject*> GameObjectPool::getActive()
{
	std::vector<GameObject*> m_activeVector;

	// Search our array for active elements
	for (GameObject& obj : m_pool)
	{
		if (obj.m_active)
		{
			m_activeVector.push_back(&obj);
		}
	}

	return m_activeVector;
}