#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.hpp"
#include <iostream>
class ParticleSystem: public sf::Drawable, public sf::Transformable {
public:
	sf::Texture tex;
	ParticleSystem(unsigned int count, sf::Color _color, sf::Vector2f pos, bool _loop, float speed, float life):
		m_particles(count),
		m_vertices(sf::Quads, count)
	{
		m_lifetime = 3.0f;
		m_emitter = pos;
		color = _color;
		destroyed = false;
		emitterLife = life;
		loop = _loop;
		baseSpeed = speed;
		for (std::size_t i = 0; i < m_particles.size(); i+=4){
			float angle = (std::rand() % 360) * 3.14f / 180.f;
			float speed = (std::rand() % (int)baseSpeed) + baseSpeed;
			resetParticle(i, pos,angle, speed);
			resetParticle(i+1, pos + sf::Vector2f(4,0), angle, speed);
			resetParticle(i+2, pos + sf::Vector2f(4,4), angle, speed);
			resetParticle(i+3, pos + sf::Vector2f(0,4), angle, speed);
			m_vertices[i].texCoords = sf::Vector2f(0, 0);
			m_vertices[i+1].texCoords = sf::Vector2f(128, 0);
			m_vertices[i+2].texCoords = sf::Vector2f(128, 128);
			m_vertices[i+3].texCoords = sf::Vector2f(0, 128);
		}
	}

	void setEmitter(sf::Vector2f position)
	{
		m_emitter = position;
	}
	bool isDestroyed() {
		return destroyed;
	}

	void UpdateParticle(double dt)
	{
		emitterLife -= dt;
		if (emitterLife <= 0) {
			destroyed = true;
		}
		for (std::size_t i = 0; i < m_particles.size(); ++i)
		{

			// update the particle lifetime
			Particle& p = m_particles[i];
			if (i % 4 == 0 ||i == 0) {
				if (m_vertices[i].position.x >= 1280 || m_vertices[i].position.x <= 0) {
					p.velocity.x = -p.velocity.x;
					for (int j = i + 1; j < i + 4; j++) {
						m_particles[j].velocity.x = -m_particles[j].velocity.x;
					}
				}
				if (m_vertices[i].position.y >= 720 || m_vertices[i].position.y <= 0) {
					p.velocity.y = -p.velocity.y;
					for (int j = i + 1; j < i + 4; j++) {
						m_particles[j].velocity.y = -m_particles[j].velocity.y;
					}
				}
			}
			p.lifetime -= dt;
			if(p.lifetime <= 0 && !loop){
				m_particles.erase(m_particles.begin() + i); 
				m_vertices[i].color.a = static_cast<sf::Uint8>(0);
				continue;
			}
			// update the position of the corresponding vertex
			m_vertices[i].position += p.velocity * (float)dt;

			// update the alpha (transparency) of the particle according to its lifetime
			float ratio = p.lifetime / m_lifetime;
			m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
		}
	}
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

	void resetParticle(std::size_t index, sf::Vector2f pos, float angle, float speed)
	{
		// give a random velocity and lifetime to the particle

		m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
		m_particles[index].lifetime = m_lifetime;
		// reset the position of the corresponding vertex
		m_vertices[index].position = pos;
		m_vertices[index].color = color;
	}

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