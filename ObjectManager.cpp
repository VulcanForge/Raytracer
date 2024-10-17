#include "ObjectManager.h"

#include <fstream>

#include "Sphere.h"
#include "Triangle.h"

std::vector<glm::vec3> lightSources;
std::vector<ShapePtr> shapes;

void ReadFromFile (const char* filename)
{
    std::ifstream reader (filename);
    char token[16];

    while (reader.get (token, 9, ' '))
    {
        if (strncmp (token, "light", 5) == 0)
        {
            glm::vec3 light;
            reader >> light.x >> light.y >> light.z;
            lightSources.push_back (light);
        }
        else if (strncmp (token, "sphere", 6) == 0)
        {
            Sphere sphere;
            LightProperties props;
            reader >> sphere.center.x >> sphere.center.y >> sphere.center.z
                >> sphere.radius
                >> props.colour.r >> props.colour.g >> props.colour.b
                >> props.diffuse >> props.specular >> props.shininess;
            sphere.lightProperties = props;
            shapes.emplace_back (std::make_unique<Sphere> (sphere));
        }
        else if (strncmp (token, "triangle", 8) == 0)
        {
            glm::vec3 a, b, c;
            reader >> a.x >> a.y >> a.z >> b.x >> b.y >> b.z >> c.x >> c.y >> c.z;
            Triangle triangle (a, b, c);
            LightProperties props;
            reader >> props.colour.r >> props.colour.g >> props.colour.b
                >> props.diffuse >> props.specular >> props.shininess;
            triangle.lightProperties = props;
            shapes.emplace_back (std::make_unique<Triangle> (triangle));
        }
        reader.get ();
    }
}
