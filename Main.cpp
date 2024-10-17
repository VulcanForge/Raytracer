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
    unsigned int width = 1600;
    unsigned int height = 900;
    float widthf = (float)width;
    float heightf = (float)height;
    std::unique_ptr<std::vector<unsigned char>> rgb = std::make_unique<std::vector<unsigned char>> (3 * width * height, (unsigned char)0);
    ReadFromFile ("Objects/objects.txt");

    for (unsigned int j = 0; j < height; ++j)
        for (unsigned int i = 0; i < width; ++i)
        {
            glm::vec3 direction {(i - .5f * widthf) / heightf, j / heightf - .5f, -1.f};
            Ray pixelRay {{}, direction};
            size_t nearestShapeIndex = SIZE_MAX;
            float leastIntercept = -1.f;

            for (size_t k = 0; k < shapes.size (); ++k)
            {
                float intercept = shapes[k]->NearestIntersection (pixelRay);

                if (intercept != -1.f)
                    if (leastIntercept == -1.f || intercept < leastIntercept)
                    {
                        nearestShapeIndex = k;
                        leastIntercept = intercept;
                    }
            }

            if (nearestShapeIndex != SIZE_MAX)
            {
                glm::vec3 point = leastIntercept * direction;
                glm::vec3 colour = shapes[nearestShapeIndex]->ColourAt (point);
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
