#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.hpp"
#include <iostream>
class ParticleSystem: public sf::Drawable, public sf::Transformable {
public:
	/*float life = 1.0;
	ParticleSystem(Game* g, sf::Vector2f spawnPos, sf::Vector2f speed, sf::Color color, float maxLife = 1) {
		dx = speed.x;
		dy = speed.y;
		sprite.setSize(sf::Vector2f(6, 6));
		sprite.setOrigin(sf::Vector2f(3,3));
		sprite.setFillColor(color);
		SetPosition(spawnPos);
		radius = 4;
		life = maxLife;
		game = g;
	}
	~ParticleSystem() {}
	bool CheckType(Entity* type) {
		if (dynamic_cast<ParticleSystem*>(type)) {
			return true;
		}
		return false;
	}
	void UpdateEntity(double dt) {
		MoveX();
		MoveY();
		SetSpriteCoor();
		life -= dt;
		if (life < 0) {
			destroyed = true;
		}
	}
	void MoveY();
	void MoveX();*/


	ParticleSystem(unsigned int count, sf::Color _color, sf::Vector2f pos, bool _loop, float speed):
		m_particles(count),
		m_vertices(sf::Points, count)
	{
		m_lifetime = 3.0f;
		m_emitter = pos;
		color = _color;
		destroyed = false;
		emitterLife = 5.0f;
		loop = _loop;
		baseSpeed = speed;
		for (std::size_t i = 0; i < m_particles.size(); ++i){
			resetParticle(i);
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
			p.lifetime -= dt;
			// if the particle is dead, respawn it
			if (p.lifetime <= 0 && loop) {
				resetParticle(i);
			}
			else if(p.lifetime <= 0 && !loop){
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

	void resetParticle(std::size_t index)
	{
		// give a random velocity and lifetime to the particle
		float angle = (std::rand() % 360) * 3.14f / 180.f;
		float speed = (std::rand() % 50) + baseSpeed;
		m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
		m_particles[index].lifetime = m_lifetime;
		// reset the position of the corresponding vertex
		m_vertices[index].position = m_emitter;
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