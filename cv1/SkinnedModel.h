#pragma once
#include "Model.h"

using namespace std;
class SkinnedModel : public Model
{
public:
    SkinnedModel(const GLfloat* vertices, const GLsizeiptr numVertices);
    SkinnedModel(const char* path);
    void Initialize() override;
    vector<float> LoadModel(const char* fileName, int& count);
};

