
#pragma once

#include <glm/vec3.hpp>   // glm::vec3
#include <glm/vec4.hpp>   // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp>

namespace Objects3d
{
    class Camera
    {
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 300.f);

    public:
        Camera(float fov, float aspect)
        {
            projection = glm::perspective(glm::radians(fov), aspect, 0.1f, 300.f);
        }

        ~Camera()
        {
        }

        glm::mat4 camera(float translate, glm::vec2 const &rotate)
        {
            glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -translate));
            view = glm::rotate(view, rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
            view = glm::rotate(view, rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
            glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
            return projection * view * model;
        }
    };
}
