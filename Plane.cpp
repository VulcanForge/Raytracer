#include "Plane.h"

#include <glm/geometric.hpp>

Plane::Plane (const glm::vec3& normal, float dot)
    : Shape {}, normal (normal), dot (dot)
{}

Plane Plane::FromNormalAndPoint (const glm::vec3& normal, const glm::vec3& point)
{
    return {normal, glm::dot (normal, point)};
}

Plane Plane::FromThreePoints (const glm::vec3& a, const glm::vec3& b, const glm::vec3& c)
{
    glm::vec3 normal = glm::cross (b - a, c - b);
    return FromNormalAndPoint (normal, a);
}

std::optional<float> Plane::NearestIntersection (const Ray& ray)
{
    float numerator = dot - glm::dot (ray.origin, normal);
    float denominator = glm::dot (ray.direction, normal);

    if (denominator != 0 && numerator / denominator > 0)
        return numerator / denominator;
    else if (numerator == 0)
        return 0;
    else
        return {};
}

glm::vec3 Plane::NormalAt (const glm::vec3& point)
{
    return normal;
}

glm::vec3 Plane::ColourAt (const glm::vec3& point)
{
    return glm::vec3 ();
}
