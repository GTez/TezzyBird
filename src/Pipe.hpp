#ifndef TEZZYBIRD_PIPE_HPP_
#define TEZZYBIRD_PIPE_HPP_

class Pipe
{
	public:
		Pipe(std::string textureName, sf::Vector2f position, float spread);
		~Pipe();
		void update(float dt, float distance);
		sf::Sprite getSprite();
		sf::Sprite getTopSprite();
		sf::Vector2f getPosition();
		bool GetPassed();
		void SetPassed(bool _passed);

	private:
		sf::Texture m_texture;
		sf::Sprite m_sprite;
		sf::Sprite m_spriteTop;
		sf::Vector2f m_position;
		sf::Vector2f m_positionTop;
		bool m_passed;
};

#endif // TEZZYBIRD_PIPE_HPP_