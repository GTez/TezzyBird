#pragma once

class Bird{
	public:
		Bird();
		~Bird();

		void init(std::string textureName, sf::Vector2f position, float mass, float gravity, float maxStamina, float regenRate);
		void flap(float jumpPower);
		void update(float dt);
		sf::Sprite getSprite();
		float getVelocity();
		float getStamina();
		sf::Vector2f getPosition();
		void setPosition(sf::Vector2f position);
		void reset();

	private:
		sf::Texture m_texture;
		sf::Sprite m_sprite;
		sf::Vector2f m_position;
		float m_mass;
		float m_velocity;
		float m_gravity;
		float m_stamina;
		float m_maxStamina;
		float m_regenRate;
};
