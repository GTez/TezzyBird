#ifndef TEZZYBIRD_BIRD_HPP_
#define TEZZYBIRD_BIRD_HPP_

class Bird{
	public:
		Bird(sf::Vector2f _position, float _mass, float _gravity, float _stamina, float _regen);
		~Bird();

		// void init(std::string textureName, sf::Vector2f position, float mass, float gravity, float maxStamina, float regenRate);
		void flap(float jumpPower);
		void update(float dt);
		sf::Sprite& getSprite();
		float getVelocity();
		float getStamina();
		sf::Vector2f getPosition();
		void setPosition(sf::Vector2f position);
		void reset(sf::Vector2f position);

	private:
		const float m_mass;
		float m_velocity;
		const float m_gravity;
		const float m_maxStamina;
		float m_stamina;
		const float m_regenRate;
		sf::Vector2f m_position;
		sf::Texture m_textureDown;
		sf::Texture m_textureUp;
		sf::Texture m_textureMid;
		sf::Sprite m_sprite;
		sf::SoundBuffer m_flapping_sound_buffer;
		sf::Sound m_flapping_sound;
		float m_dt;
		float m_matchTime;
};

#endif // TEZZYBIRD_BIRD_HPP_