#pragma once

#include "GLOBALS.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "CollisionHandler.h"
#include "CoordinateConverter.h"

class GameObject
{
	friend class GameObjectPool;
public:

	GameObject();
	~GameObject() = default;

	inline glm::mat4 getModel() const { return m_model; }
	inline void setModel(glm::mat4 t_model) { m_model = t_model; }

	inline glm::mat4 getModelPos() const { return m_modelPos; }
	inline void setModelPos(glm::mat4 t_modelPos) { m_modelPos = t_modelPos; }

	inline float xOffset() const { return m_offset.x; }
	inline void xOffset(float t_xOffset) { m_offset.x = t_xOffset; }

	inline float yOffset() const { return m_offset.y; }
	inline void yOffset(float t_yOffset) { m_offset.y = t_yOffset; }

	inline float zOffset() const { return m_offset.z; }
	inline void zOffset(float t_zOffset) { m_offset.z = t_zOffset; }

	GameObject* getNext() const { return m_next; }
	void setNext(GameObject* t_nextObj) { m_next = t_nextObj; }

	bool update();

	/// <summary>
	/// @brief Return our bounding box for collision checking
	/// </summary>
	c2AABB getBounds();

	/// <summary>
	/// @brief Called when the object is hit by lightning
	/// </summary>
	void hit();

private:

	void init();

	void updateSine();

	bool walk();
	
	bool explode();

	enum class State
	{
		WALKING,
		EXPLODING
	} m_currentState{ State::WALKING };

	glm::mat4 m_model{ glm::mat4(1.0f) };
	glm::mat4 m_modelPos{ glm::mat4(1.0f) }; // Keep track of the position without rotation animation applied

	sf::Vector3f m_offset{ 0.0f,0.0f,0.0f };

	sf::Vector3f m_velocity{ 0.1f,0.0f,0.0f };

	const float GRAVITY{ 0.03f };

	c2AABB m_boundingBox;

	// Used for our walking animation
	int m_angle{ 0 }; // used to generate sine wave
	float m_sine{ 0.0f }; // sine wave, used for cube rotation
	float m_sine90off{ 90.0f }; // 90 degrees out of phase from our original sine way, used for cube bounce

	// Points to the next game object in a singly linked list
	GameObject* m_next{ nullptr };

	// Keeps track of whether the cube is active or not (on screen, or ready to spawn)
	bool m_active{ false };
};