#pragma once
#include "Model.h"
class SkinnedModel : public Model
{
public:
    SkinnedModel(const GLfloat* vertices, const GLsizeiptr numVertices);
    SkinnedModel(const char* path);
    void Initialize() override;
};

