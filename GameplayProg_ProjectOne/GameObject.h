#pragma once

#include "glm/glm.hpp"

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

private:

	glm::mat4 m_model;
	glm::mat4 m_modelPos; // Keep track of the position without rotation animation applied

	float m_xOffset, m_yOffset, m_zOffset{ 0.0f };
};