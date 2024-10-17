#include "ObjectManager.h"

#include <fstream>

#include "LightProperties.h"
#include "Sphere.h"
#include "Triangle.h"

std::vector<glm::vec3> lightSources;
std::vector<ShapePtr> shapes;

void ReadFromFile (const std::string& filename)
{
    std::ifstream reader (filename);
    std::string token;

    while (std::getline (reader, token, ' '))
    {
        if (token == "light")
        {
            glm::vec3 light;
            reader >> light.x >> light.y >> light.z;
            lightSources.push_back (light);
        }
        else if (token == "sphere")
        {
            Sphere sphere;
            reader >> sphere.center.x >> sphere.center.y >> sphere.center.z
                >> sphere.radius;
            LightProperties props;
            reader >> props.colour.r >> props.colour.g >> props.colour.b
                >> props.diffuse >> props.specular >> props.shininess;
            sphere.lightProperties = props;
            shapes.emplace_back (std::make_unique<Sphere> (sphere));
        }
        else if (token == "triangle")
        {
            glm::vec3 a, b, c;
            reader >> a.x >> a.y >> a.z
                >> b.x >> b.y >> b.z
                >> c.x >> c.y >> c.z;
            Triangle triangle (a, b, c);
            LightProperties props;
            reader >> props.colour.r >> props.colour.g >> props.colour.b
                >> props.diffuse >> props.specular >> props.shininess;
            triangle.lightProperties = props;
            shapes.emplace_back (std::make_unique<Triangle> (triangle));
        }
        reader >> std::ws;
    }
}
