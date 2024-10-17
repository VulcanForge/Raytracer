#pragma once

#include <string>
#include <vector>

#include <glm/vec3.hpp>

#include "Shape.h"

extern std::vector<glm::vec3> lightSources;
extern std::vector<ShapePtr> shapes;

void ReadFromFile (const std::string& filename);
