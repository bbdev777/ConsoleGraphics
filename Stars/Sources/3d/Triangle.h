#pragma once

#include <functional>
#include <glm/vec3.hpp>

namespace Objects3d
{
    void FillTriangle(glm::vec3 p1, 
            glm::vec3 p2, 
            glm::vec3 p3,
            std::function<void(glm::vec3 p)> onPoint);
}
