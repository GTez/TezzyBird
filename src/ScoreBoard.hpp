#ifndef TEZZY_SCOREBOARD_HPP_
#define TEZZY_SCOREBOARD_HPP_

class ScoreBoard{
	public:
		ScoreBoard();
		~ScoreBoard();
		void SetScore(int _score);
		sf::Sprite sprite0;
		sf::Sprite sprite10;
		sf::Sprite sprite100;

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
		sf::Texture& getNumberedTexture(int _number);
};

#endif // TEZZY_SCOREBOARD_HPP_