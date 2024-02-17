
#include "Triangle.h"

namespace Objects3d
{
    void FillTriangle(glm::vec3 t0, glm::vec3 t1, glm::vec3 t2, std::function<void(glm::vec3 p)> onPoint)
    {
        if (t0.y == t1.y && t0.y == t2.y)
            return; // i dont care about degenerate triangles
        if (t0.y > t1.y)
            std::swap(t0, t1);
        if (t0.y > t2.y)
            std::swap(t0, t2);
        if (t1.y > t2.y)
            std::swap(t1, t2);

        float total_height = (t2.y - t0.y);
        for (float i = 0.0f; i <= total_height; i += 1.0f)
        {
            float   alpha = i / total_height;
            bool    second_half = i > t1.y - t0.y || t1.y == t0.y;
            float   segment_height = (second_half ? t2.y - t1.y : t1.y - t0.y);
            float   beta = (i - (second_half ? t1.y - t0.y : 0)) / (segment_height == 0.0 ? 0.000001 : segment_height);
            glm::vec3 A = t0 + (t2 - t0) * alpha;
            glm::vec3 B = second_half ? t1 + (t2 - t1) * beta : t0 + (t1 - t0) * beta;
            
            if (A.x > B.x)
                std::swap(A, B);
            
            for (float j = A.x; j <= B.x; j += 1.0f)
            {
                onPoint(glm::vec3(j, t0.y + i, 0.0f));
            }
        }
    }
}