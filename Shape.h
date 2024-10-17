#pragma once

#include <memory>

#include <glm/vec3.hpp>

#include "LightProperties.h"
#include "Ray.h"

struct Shape
{
    LightProperties lightProperties;

    // Returns the distance along the ray to the nearest intersection,
    // or -1.f if no intersection exists.
    virtual float NearestIntersection (const Ray& ray) = 0;

    // Returns the normal to the shape at the given point,
    // if the point is on that shape.
    // Undefined otherwise.
    virtual glm::vec3 NormalAt (const glm::vec3& point) = 0;

    // Returns the colour of the shape at the given point,
    // if the point is on that shape.
    // Undefined otherwise.
    glm::vec3 ColourAt (const glm::vec3& point);
};

typedef std::unique_ptr<Shape> ShapePtr;
