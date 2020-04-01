#pragma once

#include "glm/glm.hpp"
#include "CollisionHandler.h"
#include "CoordinateConverter.h"

class GameObject
{
public:

	GameObject() = default;
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

	/// <summary>
	/// @brief Return our bounding box for collision checking
	/// </summary>
	c2AABB getBounds();

private:

	glm::mat4 m_model{ glm::mat4(1.0f) };
	glm::mat4 m_modelPos{ glm::mat4(1.0f) }; // Keep track of the position without rotation animation applied

	float m_xOffset{ 0.0f }; 
	float m_yOffset{ 0.0f }; 
	float m_zOffset{ 0.0f };

	c2AABB m_boundingBox;
};