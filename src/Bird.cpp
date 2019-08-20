#include "Bird.h"

 Bird::Bird(){}
 Bird::~Bird(){}

void Bird::init(std::string textureName, sf::Vector2f position, float mass, float gravity, float maxStamina, float regenRate) {
	m_position = position;
	m_mass = mass;
	m_velocity = mass;
	m_gravity = gravity;
	m_stamina = maxStamina;
	m_maxStamina = maxStamina;
	m_regenRate = regenRate;
	m_texture.loadFromFile(textureName.c_str());
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y /2);
	m_sprite.setPosition(m_position);
}

void Bird::flap(float jumpPower) {
	// float max_velocity = 200.0f;
	float m_jumpPower = jumpPower;
	if (m_jumpPower < m_stamina) {
		m_stamina = m_stamina - m_jumpPower;
	} else {
		// m_jumpPower = -1 * (m_stamina - m_jumpPower);
		m_jumpPower = 0.0f;
		m_stamina = 0.0f;
	}
	m_velocity += m_jumpPower;
}

void Bird::update(float dt) {
	m_velocity -= m_mass * m_gravity * dt;
	m_position.y -= m_velocity * dt;
	if (m_position.y < 5) {
		m_position.y = 5;
		m_velocity = -10.0;
	} else if (m_position.y > 500) {
		m_position.y = 500;
		m_velocity = 0;
	}

	if (m_stamina < m_maxStamina) {
		m_stamina += m_regenRate * dt;
	}
	m_sprite.setPosition(m_position);
}


sf::Sprite Bird::getSprite(){
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