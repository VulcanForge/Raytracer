#pragma once

#include <memory>
#include <optional>

#include <glm/vec3.hpp>

#include "LightProperties.h"
#include "Ray.h"

struct Shape
{
    std::optional<LightProperties> lightProperties;

    virtual std::optional<float> NearestIntersection (const Ray& ray) = 0;

    virtual glm::vec3 NormalAt (const glm::vec3& point) = 0;

    glm::vec3 ColourAt (const glm::vec3& point);
};

typedef std::unique_ptr<Shape> ShapePtr;
