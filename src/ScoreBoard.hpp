#pragma once

class ScoreBoard{
	public:
		ScoreBoard();
		~ScoreBoard();
		void SetScore(int _score);
		sf::FloatRect GetDimentions();

	private:
		int m_score;
		sf::Texture m_0_texture;
		sf::Texture m_1_texture;
		sf::Texture m_2_texture;
		sf::Texture m_3_texture;
		sf::Texture m_4_texture;
		sf::Texture m_5_texture;
		sf::Texture m_6_texture;
		sf::Texture m_7_texture;
		sf::Texture m_8_texture;
		sf::Texture m_9_texture;
		sf::Sprite m_0_sprite;
		sf::Sprite m_1_sprite;
		sf::Sprite m_2_sprite;
		sf::Sprite m_3_sprite;
		sf::Sprite m_4_sprite;
		sf::Sprite m_5_sprite;
		sf::Sprite m_6_sprite;
		sf::Sprite m_7_sprite;
		sf::Sprite m_8_sprite;
		sf::Sprite m_9_sprite;
};