#include "SkinnedModel.h"

SkinnedModel::SkinnedModel(const GLfloat* vertices, const GLsizeiptr numVertices) : Model(vertices, numVertices)
{
}

SkinnedModel::SkinnedModel(const char* path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate
        | aiProcess_OptimizeMeshes              // slouèení malých plošek
        | aiProcess_JoinIdenticalVertices       // NUTNÉ jinak hodnì duplikuje
        | aiProcess_Triangulate                 // prevod vsech ploch na trojuhelniky
        | aiProcess_CalcTangentSpace);

    /*if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Assimp error: " << importer.GetErrorString() << std::endl;
        return;
    }*/

    aiMesh* mesh = scene->mMeshes[0];

    int vertexCount = mesh->mNumVertices;
    GLfloat* vertices = new GLfloat[vertexCount * 8];
    int numVertices = 0;
    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
        int j = i * 8;
        vertices[j++] = mesh->mVertices[i].x;
        vertices[j++] = mesh->mVertices[i].y;
        vertices[j++] = mesh->mVertices[i].z;
        vertices[j++] = mesh->mNormals[i].x;
        vertices[j++] = mesh->mNormals[i].y;
        vertices[j++] = mesh->mNormals[i].z;

        vertices[j++] = mesh->mTextureCoords[0][i].x;
        vertices[j++] = mesh->mTextureCoords[0][i].y;

        numVertices += 8;
    }
    this->vbo_ = VertexBufferObject(vertices, vertexCount, GL_STATIC_DRAW);
    this->verticies_ = vertices;
    this->numVertices_ = vertexCount;

}

void SkinnedModel::Initialize()
{
    this->Bind();
    vao_.LinkVBO(vbo_, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (GLvoid*)0);
    vao_.LinkVBO(vbo_, 1, 3, GL_FLOAT, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    vao_.LinkVBO(vbo_, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    this->Unbind();
}
