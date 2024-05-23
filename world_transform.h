#pragma once

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective, ...

using namespace glm;

class WorldTrans {
public:
    void SetScale(float scale);
    void SetRotation(float x, float y, float z);
    void SetPosition(vec3 position);

    void Rotate(float x, float y, float z);

    mat4 GetMatrix(void);

private:
    vec3 scale_    = vec3(1.0f);
    vec3 rotation_ = vec3(0.0f);
    vec3 pos_      = vec3(0.0f);
};