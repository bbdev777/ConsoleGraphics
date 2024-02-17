
#include "ConsoleApp.h"
#include "Camera.h"
#include "Triangle.h"

glm::vec3    Rotate(float angle, const glm::vec3& p)
{
    auto rotationMatrix = glm::rotate(glm::mat4(1.0), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0));
    return rotationMatrix * glm::vec4(p, 1.0f);
}

std::vector<glm::vec3>    TransformFace(float angle, const std::vector<glm::vec3>& face)
{
    std::vector<glm::vec3>  transformed;
    transformed.reserve(face.size());

    for (auto& item : face)
    {
        transformed.emplace_back(Rotate(angle, item));
    }

    return transformed;
}

void    RenderFace(const std::vector<glm::vec3>& face, ConsoleGraphics::Display &display)
{
    float   halfWidth = (float)display.GetWidth() / 2.0f;
    float   halfHeight = (float)display.GetHeight() / 2.0f;

    for (int i = 0, c = face.size() - 2; i < c; i++)
    {
        Objects3d::FillTriangle(face[i], 
                face[i + 1], 
                face[i + 2], 
                [&](glm::vec3 point)
        {
            display.SetCharAt((int)round(point.x) + halfWidth, (int)round(point.y) + halfHeight, '*', F_GREEN, 1);
        });    
        
    }
}

int main()
{
    ConsoleGraphics::ConsoleApp application;
    std::vector<glm::vec3>  face1{
        {0.0f, 0.0f, 10.0f},
        {0.0f, 5.0f, 10.0f},
        {10.0f, 0.0f, 10.0f},
        {10.0f, 5.0f, 10.0f},
    };
    
    float angle = 0.0f;

    return application.Run([&](double k, ConsoleGraphics::Display &display)
    {
        RenderFace(TransformFace(angle, face1), display);
        angle += 0.5;
    },
    10, true);
}
