#pragma once

#include <optional>

#include <glm/vec3.hpp>

#include "Plane.h"
#include "Ray.h"
#include "Shape.h"

struct Triangle : Shape
{
    glm::vec3 a;
    glm::vec3 b;
    glm::vec3 c;

    Plane plane;

    Triangle (const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);

    std::optional<float> NearestIntersection (const Ray& ray);

    glm::vec3 NormalAt (const glm::vec3& point);
};
