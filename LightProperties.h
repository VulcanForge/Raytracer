#pragma once

#include <glm/vec3.hpp>

struct LightProperties
{
    glm::vec3 colour;
    float diffuse;
    float specular;
    float shininess;
};
