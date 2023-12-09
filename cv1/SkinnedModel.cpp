#include "SkinnedModel.h"

SkinnedModel::SkinnedModel(const GLfloat* vertices, const GLsizeiptr numVertices) : Model(vertices, numVertices)
{
}

SkinnedModel::SkinnedModel(const char* path)
{
    int count = 0;

    auto lm = LoadModel(path, count);
    this->verticies_ = lm.data();
    this->numVertices_ = count;
    vbo_ = VertexBufferObject(verticies_, numVertices_, GL_STATIC_DRAW);
}

void SkinnedModel::Initialize()
{
    this->Bind();
    vao_.LinkVBO(vbo_, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (GLvoid*)0);
    vao_.LinkVBO(vbo_, 1, 3, GL_FLOAT, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    vao_.LinkVBO(vbo_, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    this->Unbind();
}


vector<float> SkinnedModel::LoadModel(const char* fileName, int& count) {
    vector<float> data;
    count = 0;
    Assimp::Importer importer;
    unsigned int importOptions = aiProcess_Triangulate
        | aiProcess_OptimizeMeshes              // reduce the number of draw calls
        | aiProcess_JoinIdenticalVertices       // identifies and joins identical vertex data sets within all imported meshes
        | aiProcess_Triangulate                 // triangulates all faces of all meshes 
        | aiProcess_CalcTangentSpace;           // calculates the tangents and bitangents for the imported meshes

    const aiScene* scene = importer.ReadFile(fileName, importOptions);

    if (scene) {
        aiMesh* mesh = scene->mMeshes[0];//Only first mesh 
        printf("Triangles:%d \n", mesh->mNumFaces);
        count = mesh->mNumFaces * 3;

        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];

            for (unsigned int j = 0; j < 3; j++)
            {
                int id = face.mIndices[j];

                //Vertex position
                aiVector3D pos = mesh->mVertices[id];
                data.push_back(pos.x);
                data.push_back(pos.y);
                data.push_back(pos.z);

                //Vertex normal
                aiVector3D nor = mesh->mNormals[id];
                data.push_back(nor.x);
                data.push_back(nor.y);
                data.push_back(nor.z);

                //Vertex uv
                aiVector3D uv = mesh->mTextureCoords[0][id];
                data.push_back(uv.x);
                data.push_back(uv.y);

            }
        }
    }
    else {
        std::cout << "An error occurred while loading model." << std::endl;
        exit(EXIT_FAILURE);
    };

    return data;
}
