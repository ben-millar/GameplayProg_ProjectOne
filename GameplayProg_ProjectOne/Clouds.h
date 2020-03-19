#ifndef CLOUDS_H
#define CLOUDS_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <array>

class Clouds : public sf::Drawable
{
public:

	Clouds(int t_width, int t_height);

	~Clouds() = default;

	/// <summary>
	/// @brief Updates the cloud 'animations'
	/// </summary>
	/// <param name="t_dT">Time in seconds since last frame</param>
	void update(sf::Time t_dT);

	// sf::Drawable override
	// function is called by window.draw(Clouds)
	void draw(sf::RenderTarget& t_target, sf::RenderStates t_state = sf::RenderStates::Default) const override;

private:

	/// <summary>
	/// @brief Loads our cloud texture in from file
	/// </summary>
	void loadTextures();

	/// <summary>
	/// @brief Initialise the shapes in our CloudPiece array
	/// </summary>
	void initArray();

	// How far across the screen from {0,0} should our clouds span
	int m_width;

	// How far down the screen from {0,0} should our clouds span
	int m_height;

	struct CloudPiece
	{
		sf::CircleShape shape;
		float rad{ -1.0f };

		// If not growing, then shrinking
		bool growing{ false };
	};

	const int MIN_RAD, MAX_RAD;

	static const int NUM_CLOUDS{ 100 };

	std::array<CloudPiece, NUM_CLOUDS> m_cloudArray;

	sf::Texture m_texture;
};

#endif // !CLOUDS_H