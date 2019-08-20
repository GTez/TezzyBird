#pragma once
class Pipe
{
	public:
		Pipe();
		~Pipe();
		void init(std::string textureName, sf::Vector2f position);
		void update(float dt, float distance);
		sf::Sprite getSprite();
		sf::Vector2f getPosition();

	private:
		sf::Texture m_texture;
		sf::Sprite m_sprite;
		sf::Vector2f m_position;

};