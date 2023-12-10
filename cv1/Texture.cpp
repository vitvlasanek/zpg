#include "Texture.h"

Texture::Texture(string path)
{
	this->textureId_ = SOIL_load_OGL_texture(
		path.c_str(),
		SOIL_LOAD_RGBA,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);
}

void Texture::Render(Shader* shader)
{
	glUniform1d(shader->GetUniformLocation("texture"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->textureId_);
}


