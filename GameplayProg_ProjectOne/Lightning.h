#ifndef LIGHTNING_H
#define LIGHTNING_H

#include <SFML/Graphics.hpp>
#include <vector>

// TODO: Add a 'bolt' struct, to give each bolt a lifetime.
// We should manage a queue of bolts with the oldest at the end

class Lightning : public sf::Drawable
{
public:

	Lightning();
	~Lightning() = default;

	/// <summary>
	/// @brief Triggers a lightning strike from the sky to some target
	/// </summary>
	/// <param name="t_target">Position to strike</param>
	void strike(sf::Vector2i t_target);

	/// <summary>
	/// @brief Updates our lightning animations
	/// </summary>
	/// <param name="t_dT">Time in seconds since last frame</param>
	void update(sf::Time t_dT);

	// sf::Drawable override
	// function is called by window.draw(Lightning)
	void draw(sf::RenderTarget& t_target, sf::RenderStates t_state = sf::RenderStates::Default) const override;

private:

	sf::VertexArray m_bolt{ sf::Lines };
};

#endif // !LIGHTNING_H