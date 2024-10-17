#include "Triangle.h"

#include <glm/geometric.hpp>

Triangle::Triangle (const glm::vec3& a, const glm::vec3& b, const glm::vec3& c)
    : a (a), b (b), c (c), plane (Plane::FromThreePoints (a, b, c))
{}

float Triangle::NearestIntersection (const Ray& ray)
{
    float t = plane.NearestIntersection (ray);

    if (t == -1.f)
        return -1.f;

    glm::vec3 intersection = ray.origin + t * ray.direction;

    glm::vec3 aToIntersection = intersection - a;

    if (glm::dot (glm::cross (b - a, aToIntersection), NormalAt (intersection)) < 0.f)
        return -1.f;

    glm::vec3 bToIntersection = intersection - b;

    if (glm::dot (glm::cross (c - b, bToIntersection), NormalAt (intersection)) < 0.f)
        return -1.f;

    glm::vec3 cToIntersection = intersection - c;

    if (glm::dot (glm::cross (a - c, cToIntersection), NormalAt (intersection)) < 0.f)
        return -1.f;

    return t;
}

glm::vec3 Triangle::NormalAt (const glm::vec3& point)
{
    return plane.NormalAt (point);
}
