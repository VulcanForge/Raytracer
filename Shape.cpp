#include "Shape.h"

#include <glm/geometric.hpp>

#include "ObjectManager.h"

glm::vec3 Shape::ColourAt (const glm::vec3& point)
{
    glm::vec3 colourAt {};

    for (auto& light : lightSources)
    {
        glm::vec3 pointToLight = glm::normalize (light - point);
        glm::vec3 normal = NormalAt (point);
        //glm::vec3 pointToViewer = glm::normalize (-point);
        //glm::vec3 reflection = glm::normalize (2.f * glm::dot (pointToLight, normal) * normal - pointToLight);
        colourAt += fmaxf (0, lightProperties->diffuse * glm::dot (pointToLight, normal)) * lightProperties->colour;
        //colourAt += fmaxf (0, specular * pow (glm::dot (reflection, pointToViewer), shininess)) * colour;
        colourAt.r = fminf (colourAt.r, 1.f);
        colourAt.g = fminf (colourAt.g, 1.f);
        colourAt.b = fminf (colourAt.b, 1.f);
    }

    return colourAt;
}