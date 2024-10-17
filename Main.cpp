#include <iostream>
#include <memory>

#include <GL/glew.h>

#include "GLFW/glfw3.h"

#include "Image.h"
#include "ObjectManager.h"
#include "Ray.h"
#include "Sphere.h"

int main ()
{
    unsigned int width = 1920;
    unsigned int height = 1080;
    float widthf = (float)width;
    float heightf = (float)height;
    std::unique_ptr<std::vector<unsigned char>> rgb = std::make_unique<std::vector<unsigned char>> (3 * width * height, (unsigned char)0);
    ReadFromFile ("Objects/objects.txt");

    for (unsigned int j = 0; j < height; ++j)
        for (unsigned int i = 0; i < width; ++i)
        {
            glm::vec3 direction {(i - .5f * widthf) / heightf, j / heightf - .5f, -1.f};
            Ray pixelRay {{}, direction};
            std::optional<size_t> nearestShapeIndex;
            std::optional<float> leastIntercept;

            for (size_t k = 0; k < shapes.size (); ++k)
            {
                std::optional<float> intercept = shapes[k]->NearestIntersection (pixelRay);

                if (intercept.has_value ())
                    if (!leastIntercept.has_value () || intercept.value () < leastIntercept.value ())
                    {
                        nearestShapeIndex = k;
                        leastIntercept = intercept;
                    }
            }

            if (leastIntercept.has_value ())
            {
                glm::vec3 p = leastIntercept.value () * direction;
                glm::vec3 colour = shapes[nearestShapeIndex.value ()]->ColourAt (p);
                (*rgb)[3 * j * width + 3 * i] = (unsigned char)(colour.r * 255);
                (*rgb)[3 * j * width + 3 * i + 1] = (unsigned char)(colour.g * 255);
                (*rgb)[3 * j * width + 3 * i + 2] = (unsigned char)(colour.b * 255);
            }
        }

    GLFWwindow* window;
    glfwInit ();
    window = glfwCreateWindow (width, height, "Ray Tracer", nullptr, nullptr);
    glfwMakeContextCurrent (window);
    glewInit ();

    Image image {width, height, std::move (rgb)};
    //image.SaveToPNG ("Output/sphere.png");

    image.Render ();
    glfwSwapBuffers (window);

    while (!glfwWindowShouldClose (window))
        glfwWaitEvents ();

    glfwDestroyWindow (window);
}
