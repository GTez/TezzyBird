#include "Bird.hpp"

 Bird::Bird(sf::Vector2f _position, float _mass, float _gravity, float _stamina, float _regen) :
 	m_mass(_mass),
	m_velocity(_mass),
	m_gravity(_gravity),
	m_maxStamina(_stamina),
	m_stamina(_stamina),
	m_regenRate(_regen)
	{
		m_position = _position;
		m_textureMid.loadFromFile("content/textures/redbird-midflap.png");
		m_textureDown.loadFromFile("content/textures/redbird-downflap.png");
		m_textureUp.loadFromFile("content/textures/redbird-upflap.png");

		m_sprite.setTexture(m_textureMid);
		m_sprite.setOrigin(m_textureMid.getSize().x / 2, m_textureMid.getSize().y /2);
		m_sprite.setPosition(m_position),
		m_flapping_sound_buffer.loadFromFile("content/audio/wing.ogg");
		m_flapping_sound.setBuffer(m_flapping_sound_buffer);
		m_dt = 0.0f;
	}
 Bird::~Bird(){}

void Bird::flap(float jumpPower)
{
	// float max_velocity = 200.0f;
	float m_jumpPower = jumpPower;
	if (m_jumpPower < m_stamina)
	{
		m_stamina = m_stamina - m_jumpPower;
		if (m_flapping_sound.getStatus() != m_flapping_sound.Playing) {
			m_flapping_sound.play();
		}
	}
	else
	{
		// m_jumpPower = -1 * (m_stamina - m_jumpPower);
		m_jumpPower = 0.0f;
		m_stamina = 0.0f;
	}
	m_velocity += m_jumpPower;
}

void Bird::update(float dt)
{
	m_dt = dt;
	m_velocity -= m_mass * m_gravity * dt;
	m_position.y -= m_velocity * dt;
	if (m_position.y < 5)
	{
		m_position.y = 5;
		m_velocity = -10.0;
	}
	else if (m_position.y > 500)
	{
		m_position.y = 500;
		m_velocity = 0;
	}

	if (m_stamina < m_maxStamina)
	{
		m_stamina += m_regenRate * dt;
	}
	m_sprite.setPosition(m_position);
}


sf::Sprite& Bird::getSprite()
{
	// m_dt is the fraction of  a second since the last update
	// I want 3 updates a second
	m_matchTime += m_dt;
	switch ((int)m_matchTime % 3)
	{
		case 1 :
			m_sprite.setTexture(m_textureDown);
			break;
		case 0 :
			m_sprite.setTexture(m_textureUp); // 0
			break;
		default :
			m_sprite.setTexture(m_textureMid);

	};
	return m_sprite;
}

float Bird::getVelocity() {
	return m_velocity;
}

float Bird::getStamina() {
	return m_stamina;
}

sf::Vector2f Bird::getPosition() {
	return m_position;
}

void Bird::setPosition(sf::Vector2f position) {
	m_sprite.setPosition(position);
}

void Bird::reset(sf::Vector2f position) {
	m_position = position;
	m_sprite.setPosition(m_position);
	m_stamina = m_maxStamina;
	m_velocity = m_mass;
}