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


