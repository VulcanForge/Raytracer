#pragma once

#include <optional>

#include <glm/vec3.hpp>

#include "Ray.h"
#include "Shape.h"

struct Plane : Shape
{
    glm::vec3 normal;
    float dot;

    Plane (const glm::vec3& normal, float dot);

    static Plane FromNormalAndPoint (const glm::vec3& normal, const glm::vec3& point);
    static Plane FromThreePoints (const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);

    std::optional<float> NearestIntersection (const Ray& ray);

    glm::vec3 NormalAt (const glm::vec3& point);

    glm::vec3 ColourAt (const glm::vec3& point);
};
