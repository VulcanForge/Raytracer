#pragma once

#include <memory>
#include <string>
#include <vector>

struct Image
{
    unsigned int width;
    unsigned int height;

    std::unique_ptr<std::vector<unsigned char>> rgb;

    Image (unsigned int width, unsigned int height, std::unique_ptr<std::vector<unsigned char>>&& rgb);

    void Render ();

    void SaveToPNG (const std::string& filename) const;
};
