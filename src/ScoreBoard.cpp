#include "ScoreBoard.hpp"

ScoreBoard::ScoreBoard() 	{
	m_score = 0;
	m_0_texture.loadFromFile("content/textures/0.png");
	m_1_texture.loadFromFile("content/textures/1.png");
	m_2_texture.loadFromFile("content/textures/2.png");
	m_3_texture.loadFromFile("content/textures/3.png");
	m_4_texture.loadFromFile("content/textures/4.png");
	m_5_texture.loadFromFile("content/textures/5.png");
	m_6_texture.loadFromFile("content/textures/6.png");
	m_7_texture.loadFromFile("content/textures/7.png");
	m_8_texture.loadFromFile("content/textures/8.png");
	m_9_texture.loadFromFile("content/textures/9.png");
	sprite0.setTexture(m_0_texture);
	sprite10.setTexture(m_0_texture);
	sprite100.setTexture(m_0_texture);
	sf::Vector2f _origin_vector = sf::Vector2f(m_0_texture.getSize().x / 2, m_0_texture.getSize().y / 2);  // This isn't the safest way to do this. It'll require the Textures to all be the same size.
	sprite0.setOrigin(_origin_vector);
	sprite10.setOrigin(_origin_vector);
	sprite100.setOrigin(_origin_vector);
}

ScoreBoard::~ScoreBoard(){}

void ScoreBoard::SetScore(int _score) {
	m_score = _score;
	std::vector<int> _temp_array;
	int n = _score;
	if (n > 999) n = 999; // Digit protection
	sprite0.setTexture(getNumberedTexture(n % 10));
	if (n > 10) {
		sprite10.setTexture(getNumberedTexture((n / 10) % 10));
	} else {
		sprite10.setTexture(getNumberedTexture(0));
	}
	if (n > 100) {
		sprite100.setTexture(getNumberedTexture((n / 100) % 10));
	} else {
		sprite100.setTexture(getNumberedTexture(0));
	}
}

sf::Texture& ScoreBoard::getNumberedTexture(int _number)
{
	switch(_number) {
		case 0 : return m_0_texture;
		case 1 : return m_1_texture;
		case 2 : return m_2_texture;
		case 3 : return m_3_texture;
		case 4 : return m_4_texture;
		case 5 : return m_5_texture;
		case 6 : return m_6_texture;
		case 7 : return m_7_texture;
		case 8 : return m_8_texture;
		default : return m_9_texture;
	};
}
