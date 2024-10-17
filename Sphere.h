#pragma once

#include <optional>

#include <glm/vec3.hpp>

#include "Ray.h"
#include "Shape.h"

struct Sphere : Shape
{
    glm::vec3 center;
    float radius;

    std::optional<float> NearestIntersection (const Ray& ray);

    glm::vec3 NormalAt (const glm::vec3& point);

    glm::vec3 ColourAt (const glm::vec3& point);
};
