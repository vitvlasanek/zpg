#pragma once
#include <SOIL.h>
#include <GL/glew.h>
#include <string>

#include "Shader.h"

using namespace std;

class Texture
{
public:
	Texture(string path);
	void Render(Shader* shader);
private:
	GLuint textureId_;
};

