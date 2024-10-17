#include "Sphere.h"

#include <glm/geometric.hpp>

#include "ObjectManager.h"

std::optional<float> Sphere::NearestIntersection (const Ray& ray)
{
    // Solve dist((x,y,z) * t,center) = radius
    // (x * t - xc)^2 + (y * t - yc)^2 + (z * t - zc)^2 = radius^2
    // (x^2 + y^2 + z^2)t^2 - 2(x * xc + y * yc + z * zc) * t + (xc^2 + yc^2 + zc^2 - radius^2) = 0

    // Translate into coordinate system where the ray emanates from the origin for convenience.
    glm::vec3 shiftedCenter = center - ray.origin;
    float a = glm::dot (ray.direction, ray.direction);
    float b = -2 * glm::dot (ray.direction, shiftedCenter);
    float c = glm::dot (shiftedCenter, shiftedCenter) - radius * radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return std::optional<float> {};
    else if (discriminant == 0)
    {
        float t = -b / (2 * a);

        if (t < 0)
            return std::optional<float> {};
        else
            return t;
    }
    else
    {
        float sd = sqrt (discriminant);
        float tminus = (-b - sd) / (2 * a);
        float tplus = (-b + sd) / (2 * a);

        if (tplus < 0)
            return std::optional<float> {};
        else if (tminus < 0)
            return tplus;
        else
            return tminus;
    }
}

glm::vec3 Sphere::NormalAt (const glm::vec3& point)
{
    return point - center;
}