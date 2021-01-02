#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.hpp"
#include <iostream>
class ParticleSystem: public sf::Drawable, public sf::Transformable {
public:
	ParticleSystem(unsigned int count, sf::Color _color, sf::Vector2f pos, bool _loop, float speed, float life);

	void setEmitter(sf::Vector2f position)
	{
		m_emitter = position;
	}
	bool isDestroyed() {
		return destroyed;
	}

	void UpdateParticle(double dt);
	private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// our particles don't use a texture
		states.texture = NULL;

		// draw the vertex array
		target.draw(m_vertices, states);
	}
private:

	struct Particle
	{
		sf::Vector2f velocity;
		float lifetime;
	};
	void ChangeSize(int index, float ratio) {
		float val = 4.0 * ratio;
		sf::Vector2f basePos = m_vertices[index - 3].position;
		m_vertices[index - 2].position = basePos + sf::Vector2f(val, 0);
		m_vertices[index - 1].position = basePos + sf::Vector2f(val , val);
		m_vertices[index].position = basePos + sf::Vector2f(0 , val);
	}
	void resetParticle(std::size_t index, sf::Vector2f pos, float angle, float speed);

	std::vector<Particle> m_particles;
	sf::VertexArray m_vertices;
	float m_lifetime;
	sf::Vector2f m_emitter;
	sf::Color color;
	float emitterLife;
	bool destroyed;
	bool loop;
	float baseSpeed;
};