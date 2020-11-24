#include "PathfindingAStar.hpp"
namespace std
{
    template <class T>
    struct hash<sf::Vector2<T>>
    {
        std::size_t operator()(const sf::Vector2<T>& v) const
        {
            using std::hash;

            std::size_t tmp0 = hash<T>()(v.x);
            std::size_t tmp1 = hash<T>()(v.y);

            tmp0 ^= tmp1 + 0x9e3779b9 + (tmp0 << 6) + (tmp0 >> 2);
            return tmp0;
        }
    };
}
std::vector<sf::Vector2i> PathfindingAStar::reconstruct_path(std::unordered_map<sf::Vector2i, sf::Vector2i> cameFrom, sf::Vector2i current) {
	std::vector<sf::Vector2i> total_path;
	total_path.insert(total_path.begin(), current);
	while (current != start) {
		current = cameFrom[current];
		total_path.insert(total_path.begin(), current);
	}
    return total_path;
}

std::vector<sf::Vector2i> PathfindingAStar::UpdatePath(std::vector<sf::Vector2i>& node, sf::Vector2i& _start, sf::Vector2i& _goal) {
    start = _start;
    std::vector<sf::Vector2i> openSet = { _start };


    std::unordered_map<sf::Vector2i, sf::Vector2i> cameFrom;

    std::unordered_map<sf::Vector2i, float> gScore;
    for (sf::Vector2i& n : node) {
        gScore[n] = std::numeric_limits<float>::max();
    }
    gScore[start] = 0;

    std::unordered_map<sf::Vector2i, float> fScore;
    for (sf::Vector2i& n : node) {
        fScore[n] = std::numeric_limits<float>::max();
    }
    fScore[start] = h(start, _goal);

    while (openSet.size() > 0) {

        sf::Vector2i current = FindMin(openSet, gScore);
        if (current == _goal) {
            return reconstruct_path(cameFrom, current);
        }
        openSet.erase(openSet.begin() + getIndex(current, openSet));
        std::vector<sf::Vector2i> neightbours = getNeightbour(current, node);
        for (sf::Vector2i& neighbour : neightbours) {
            float tentative_gScore = gScore[current] + h(current, neighbour);
            if (tentative_gScore < gScore[neighbour]) {
                cameFrom[neighbour] = current;
                gScore[neighbour] = tentative_gScore;
                fScore[neighbour] = gScore[neighbour] + h(neighbour, _goal);
                if (getIndex(neighbour, openSet) == -1) {
                    openSet.push_back(neighbour);
                }
            }
        }
    }
    return openSet;
}

sf::Vector2i PathfindingAStar::FindMin(std::vector<sf::Vector2i>& _node, std::unordered_map<sf::Vector2i, float> value) {
    float mini = std::numeric_limits<float>::max();
    sf::Vector2i sommet(-1, -1);
    for (int i = 0; i < _node.size(); i++) {
        if (value[_node[i]] < mini) {
            mini = value[_node[i]];
            sommet = _node[i];
        }
    }
    return sommet;
}

int PathfindingAStar::getIndex(sf::Vector2i val, std::vector<sf::Vector2i>& node) {
    for (int i = 0; i < node.size(); i++) {
        if (val == node[i]) {
            return i;
        }
    }
    return -1;
}

std::vector<sf::Vector2i> PathfindingAStar::getNeightbour(sf::Vector2i val, std::vector<sf::Vector2i>& availableNode) {
    std::vector<sf::Vector2i> neightbour;
    if (getIndex(sf::Vector2i(val.x + 1, val.y), availableNode) > -1) { neightbour.push_back(sf::Vector2i(val.x + 1, val.y)); }
    if (getIndex(sf::Vector2i(val.x - 1, val.y), availableNode) > -1) { neightbour.push_back(sf::Vector2i(val.x - 1, val.y)); }
    if (getIndex(sf::Vector2i(val.x, val.y + 1), availableNode) > -1) { neightbour.push_back(sf::Vector2i(val.x, val.y + 1)); }
    if (getIndex(sf::Vector2i(val.x, val.y - 1), availableNode) > -1) { neightbour.push_back(sf::Vector2i(val.x, val.y - 1)); }
    return neightbour;
}
