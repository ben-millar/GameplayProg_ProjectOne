#pragma once

#include "GLOBALS.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "CollisionHandler.h"
#include "CoordinateConverter.h"

class GameObject
{
public:

	GameObject();
	~GameObject() = default;

	inline glm::mat4 getModel() const { return m_model; }
	inline void setModel(glm::mat4 t_model) { m_model = t_model; }

	inline glm::mat4 getModelPos() const { return m_modelPos; }
	inline void setModelPos(glm::mat4 t_modelPos) { m_modelPos = t_modelPos; }

	inline float xOffset() const { return m_xOffset; }
	inline void xOffset(float t_xOffset) { m_xOffset = t_xOffset; }

	inline float yOffset() const { return m_yOffset; }
	inline void yOffset(float t_yOffset) { m_yOffset = t_yOffset; }

	inline float zOffset() const { return m_zOffset; }
	inline void zOffset(float t_zOffset) { m_zOffset = t_zOffset; }

	void update();

	/// <summary>
	/// @brief Return our bounding box for collision checking
	/// </summary>
	c2AABB getBounds();

	/// <summary>
	/// @brief Called when the object is hit by lightning
	/// </summary>
	void hit();

private:

	void updateSine();

	void walk();
	
	void explode();

	enum class State
	{
		WALKING,
		EXPLODING
	} m_currentState{ State::WALKING };

	glm::mat4 m_model{ glm::mat4(1.0f) };
	glm::mat4 m_modelPos{ glm::mat4(1.0f) }; // Keep track of the position without rotation animation applied

	float m_xOffset{ 0.0f }; 
	float m_yOffset{ 0.0f }; 
	float m_zOffset{ 0.0f };

	sf::Vector2f m_velocity{ 0.1f,0.0f };

	c2AABB m_boundingBox;

	// Used for our walking animation
	int m_angle{ 0 }; // used to generate sine wave
	float m_sine; // sine wave, used for cube rotation
	float m_sine90off; // 90 degrees out of phase from our original sine way, used for cube bounce
};