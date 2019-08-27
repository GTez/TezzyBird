#include "ScoreBoard.hpp"

ScoreBoard::ScoreBoard() 	{
	m_score = 0;
	m_0_texture.loadFromFile("content/textures/0.png");
	m_0_sprite.setTexture(m_0_texture);
	m_0_sprite.setOrigin(sf::Vector2f(m_0_texture.getSize().x / 2, m_0_texture.getSize().y / 2));
	m_1_texture.loadFromFile("content/textures/1.png");
	m_1_sprite.setTexture(m_1_texture);
	m_1_sprite.setOrigin(sf::Vector2f(m_1_texture.getSize().x / 2, m_1_texture.getSize().y / 2));
	m_2_texture.loadFromFile("content/textures/2.png");
	m_2_sprite.setTexture(m_2_texture);
	m_2_sprite.setOrigin(sf::Vector2f(m_2_texture.getSize().x / 2, m_2_texture.getSize().y / 2));
	m_3_texture.loadFromFile("content/textures/3.png");
	m_3_sprite.setTexture(m_3_texture);
	m_3_sprite.setOrigin(sf::Vector2f(m_3_texture.getSize().x / 2, m_3_texture.getSize().y / 2));
	m_4_texture.loadFromFile("content/textures/4.png");
	m_4_sprite.setTexture(m_4_texture);
	m_4_sprite.setOrigin(sf::Vector2f(m_4_texture.getSize().x / 2, m_4_texture.getSize().y / 2));
	m_5_texture.loadFromFile("content/textures/5.png");
	m_5_sprite.setTexture(m_5_texture);
	m_5_sprite.setOrigin(sf::Vector2f(m_5_texture.getSize().x / 2, m_5_texture.getSize().y / 2));
	m_6_texture.loadFromFile("content/textures/6.png");
	m_6_sprite.setTexture(m_6_texture);
	m_6_sprite.setOrigin(sf::Vector2f(m_6_texture.getSize().x / 2, m_6_texture.getSize().y / 2));
	m_7_texture.loadFromFile("content/textures/7.png");
	m_7_sprite.setTexture(m_7_texture);
	m_7_sprite.setOrigin(sf::Vector2f(m_7_texture.getSize().x / 2, m_7_texture.getSize().y / 2));
	m_8_texture.loadFromFile("content/textures/8.png");
	m_8_sprite.setTexture(m_8_texture);
	m_8_sprite.setOrigin(sf::Vector2f(m_8_texture.getSize().x / 2, m_8_texture.getSize().y / 2));
	m_9_texture.loadFromFile("content/textures/9.png");
	m_9_sprite.setTexture(m_9_texture);
	m_9_sprite.setOrigin(sf::Vector2f(m_9_texture.getSize().x / 2, m_9_texture.getSize().y / 2));
}
ScoreBoard::~ScoreBoard(){}

void ScoreBoard::SetScore(int _score) {

	/// Note to self - Move from a Sprite injection system to a Texture swap on each
	// digit and instead of figuring out the width figure out the number of sprites to return.
	m_score = _score;
	std::vector<int> _temp_array;
	int n = _score;
	while (n != 0) { // Get each of the places and put them in an array
		_temp_array.push_back(n % 10);
		n = n / 10;
	}
	// printf( "The array is %lu Long \n", _temp_array.size() );
	while (!_temp_array.empty())
	{
		printf("%i \n", _temp_array.back());
		_temp_array.pop_back();
	}
	printf("The Score is %i \n", _score);
}

sf::FloatRect ScoreBoard::GetDimentions() {
	sf::FloatRect _obj = sf::FloatRect(0.0f, 0.0f, m_0_texture.getSize().x, m_0_texture.getSize().y);
	return _obj;
}

