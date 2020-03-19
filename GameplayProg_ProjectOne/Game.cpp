#include "Game.h"

Game::Game() :
	m_window{ sf::VideoMode{ 800, 600, 32 }, "Taranis", sf::Style::Close },
	m_exitGame{ false }
{
	setupBackground();

	m_clouds = new Clouds(m_window.getSize().x, 80);
}

///////////////////////////////////////////////////////////////

Game::~Game()
{
	delete m_clouds;
}

///////////////////////////////////////////////////////////////

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f); // run at 60fps
	srand(static_cast<unsigned>(time(nullptr)));

	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}
		render();
	}
}

///////////////////////////////////////////////////////////////

void Game::setupBackground()
try
{
	if (!m_backgroundTexture.loadFromFile("ASSETS\\TEXTURES\\background.png"))
	{
		std::string msg{ "Error loading background texture" };
		throw std::exception(msg.c_str());
	}
	else
	{
		m_backgroundSprite.setTexture(m_backgroundTexture);
	}
}
catch (const std::exception& e)
{
	std::cout << e.what() << std::endl;
}

///////////////////////////////////////////////////////////////

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == event.type)
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_exitGame = true;
			}
		}

		if (sf::Event::MouseButtonPressed == event.type)
		{
			m_lightning.strike({ event.mouseButton.x, event.mouseButton.y });
		}
	}
}

///////////////////////////////////////////////////////////////

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	m_lightning.update(t_deltaTime);
	m_clouds->update(t_deltaTime);
}

///////////////////////////////////////////////////////////////

void Game::render()
{
	m_window.clear(sf::Color::White);

	m_window.draw(m_backgroundSprite);
	m_window.draw(m_lightning);
	m_window.draw(*m_clouds);

	m_window.display();
}