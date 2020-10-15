#pragma once
#include <SFML/Graphics.hpp>
class catmull2 {
    public: 
    sf::VertexArray points;
    catmull2(sf::VertexArray points) {
        this->points = points;
    }
    float catmull(float p0, float p1, float p2, float p3, float t) {
        float q = 2.0 * p1;
        float t2 = t * t;

        q += (-p0 + p2) * t;
        q += (2.0 * p0 - 5.0 * p1 + 4 * p2 - p3) * t2;
        q += (-p0 + 3 * p1 - 3 * p2 + p3) * t2 * t;

        return 0.5 * q;
    }
    sf::Vertex getVert(int idx) {
        return points[std::max(0, std::min(idx, (int)points.getVertexCount() - 1))];
    }
    sf::Vertex c2(float i, sf::Vertex point) {

        sf::Vertex p0 = getVert((int)(i - 1));
        sf::Vertex p1 = getVert((int)(i));
        sf::Vertex p2 = getVert((int)(i + 1));
        sf::Vertex p3 = getVert((int)(i + 2));

        float t = i - (int)i;
        point.position.x = catmull(p0.position.x, p1.position.x, p2.position.x, p3.position.x, t);
        point.position.y = catmull(p0.position.y, p1.position.y, p2.position.y, p3.position.y, t);
        return point;
    }
    sf::Vertex plotWhole(float t, sf::Vertex point) {
        return c2(t * (points.getVertexCount() - 1), point);
    }
};