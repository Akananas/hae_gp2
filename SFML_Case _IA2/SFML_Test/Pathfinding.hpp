#pragma once
#include <iostream> 
#include "SFML/Graphics.hpp"
#include <limits>
#include <unordered_map> 
#include "Game.hpp"
#include <chrono>
#include <ctime>
using namespace std;
using namespace std::chrono;
class Game;
namespace std
{
	template <>
	struct hash<sf::Vector2i>
	{
		std::size_t operator()(const sf::Vector2i& k) const
		{
			return (hash<int>()(k.x) ^ (hash<int>()(k.y)));
		};
	};
}
class Pathfinding {
public:
	std::vector<sf::Vector2i> availableNode;
	std::vector<float> value;
	std::unordered_map<sf::Vector2i, sf::Vector2i> parentNode;
	sf::Vector2i start;
	Game* g = nullptr;
	float GetMag(sf::Vector2i a, sf::Vector2i b);
	void UpdatePath(std::vector<sf::Vector2i> node, sf::Vector2i& _start, Game* g);
	void Init(std::vector<sf::Vector2i>& node, sf::Vector2i& _start);
	double getTimeStamp() //retourne le temps actuel en seconde
	{
		std::chrono::nanoseconds ns =
			duration_cast<std::chrono::nanoseconds>(system_clock::now().time_since_epoch());
		return ns.count() / 1000000000.0;
	}
	std::vector<sf::Vector2i> getNeightbour(sf::Vector2i& val);

	bool FindMin(std::vector<sf::Vector2i>& q, sf::Vector2i& result);
	int getKey(sf::Vector2i vec) {
		return vec.x + (vec.y * 256);
	}
	void maj_distance(sf::Vector2i s1, sf::Vector2i s2);
};