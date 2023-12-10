#pragma once
#include <GL/glew.h>

#include <vector>


using namespace std;

class VertexBufferObject
{
public:
	void SetData(const GLvoid* data, GLsizeiptr size, GLenum usage);
	void SetData(vector<GLfloat> data, GLenum usage);
	void SetData(vector<GLfloat> data);
	~VertexBufferObject();
	void Bind();
	
	void Unbind();
	void Delete();
private:
	GLuint id_;
};