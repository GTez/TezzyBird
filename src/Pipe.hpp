#pragma once

class Pipe
{
	public:
		Pipe();
		~Pipe();
		void init(std::string textureName, sf::Vector2f position, float spread);
		void update(float dt, float distance);
		sf::Sprite getSprite();
		sf::Sprite getTopSprite();
		sf::Vector2f getPosition();

	private:
		sf::Texture m_texture;
		sf::Sprite m_sprite;
		sf::Sprite m_spriteTop;
		sf::Vector2f m_position;
		sf::Vector2f m_positionTop;

};