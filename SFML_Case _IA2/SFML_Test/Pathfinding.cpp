#include "Pathfinding.hpp"


float Pathfinding::GetMag(sf::Vector2i a, sf::Vector2i b) {
	return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

void Pathfinding::UpdatePath(std::vector<sf::Vector2i> node, sf::Vector2i& _start, Game* g) {
	this->g = g;
	auto before = getTimeStamp();
	Init(node, _start);
	while (node.size()) {

		sf::Vector2i s1;
		bool ok = FindMin(node, s1);

		auto pos = std::find(node.begin(), node.end(), s1);
		if (pos != node.end())
			node.erase(pos);
		std::vector<sf::Vector2i> neightbours(getNeightbour(s1));
		for (sf::Vector2i& n : neightbours) {
			maj_distance(s1, n);
		}

	}
	auto after = getTimeStamp() - before;
	std::cout << after << std::endl;
}

void Pathfinding::Init(std::vector<sf::Vector2i>& node, sf::Vector2i& _start) {

	value.clear();
	value.resize(500000, 10000000);
	availableNode = node;

	for (sf::Vector2i& n : availableNode) {
		value[getKey(n)] = 1000 * 1000 * 1000;;
	}
	start = _start;
	value[getKey(start)] = 0;
	parentNode[start] = start;
}


std::vector<sf::Vector2i> Pathfinding::getNeightbour(sf::Vector2i& val) {
	std::vector<sf::Vector2i> nei;
	for (int x = -1; x <= 1; ++x) {
		for (int y = -1; y <= 1; ++y) {
			if (x == 0 && y == 0)
				continue;

			int nx = x + val.x;
			int ny = y + val.y;
			if (nx >= 0 && ny >= 0 && !g->isWall(nx, ny))
				nei.push_back(sf::Vector2i(nx, ny));
		}
	}
	return nei;
}

bool Pathfinding::FindMin(std::vector<sf::Vector2i>& q, sf::Vector2i& result) {
	float min = 1000 * 1000 * 1000;
	sf::Vector2i vertex(-1, -1);
	bool isFound = false;
	for (auto& s : q) {

		if (value[getKey(s)] < min) {
			min = value[getKey(s)];
			vertex = s;
			isFound = true;
		}
	}
	result = vertex;
	return isFound;
}

void Pathfinding::maj_distance(sf::Vector2i s1, sf::Vector2i s2) {
	int ks1 = getKey(s1);
	int ks2 = getKey(s2);
	float ndist = value[ks1] + GetMag(s1, s2);
	if (value[ks2] > ndist) {
		value[ks2] = ndist;
		parentNode[s2] = s1;
	}
}
