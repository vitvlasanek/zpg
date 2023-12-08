// --- Shader . cpp ---
# include "Shader.h"
# include "Camera.h"
Shader::Shader(Camera* c, const char * vertexFile, const char * fragmentFile) {

	this->cam = c;

	string vertexCode = GetShaderCode(vertexFile);
	string fragmentCode = GetShaderCode(fragmentFile);
	
	const char * vertexSource = vertexCode.c_str();
	const char * fragmentSource = fragmentCode.c_str();


	//create and compile shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	CompileErrors(vertexShader, "VERTEX", GL_COMPILE_STATUS);


	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	CompileErrors(fragmentShader, "FRAGMENT", GL_COMPILE_STATUS);

	this->Id = glCreateProgram();
	CompileErrors(Id, "PROGRAM", GL_COMPILE_STATUS);

	glAttachShader(Id, fragmentShader);
	glAttachShader(Id, vertexShader);
	glLinkProgram(Id);

	CompileErrors(Id, "PROGRAM", GL_LINK_STATUS);


}

Shader::Shader(Camera* c) : Shader(c, "default.frag", "default.vert"){}


void Shader::Activate()
{
	glUseProgram(this->Id);
}

void Shader::Delete()
{
	glDeleteProgram(this->Id);
}

void Shader::SetLights(Light* lights, const int numLights)
{
	glUniform1i(GetUniformLocation("numLights"), numLights);

	for (int i = 0; i < numLights; i++)
	{
		glUniform3fv(GetUniformLocation("lights[" + to_string(i) + "].position"), 1, glm::value_ptr(lights[i].position));
		glUniform3fv(GetUniformLocation("lights[" + to_string(i) + "].color"), 1, glm::value_ptr(lights[i].color));
		glUniform3fv(GetUniformLocation("lights[" + to_string(i) + "].ambient"), 1, glm::value_ptr(lights[i].ambient));
		glUniform3fv(GetUniformLocation("lights[" + to_string(i) + "].diffuse"), 1, glm::value_ptr(lights[i].diffuse));
		glUniform3fv(GetUniformLocation("lights[" + to_string(i) + "].specular"), 1, glm::value_ptr(lights[i].specular));
	}
}

void Shader::SetCamera()
{
	glUniformMatrix4fv(GetUniformLocation("camMatrix"), 1, GL_FALSE, glm::value_ptr(this->cam->cameraMatrix));
	glUniform3fv(GetUniformLocation("viewPos"), 1, glm::value_ptr(this->cam->Position));
}

void Shader::SetModels()
{
	for (int i = 0; i < objects.size(); i++)
	{
		mat4 modelMatrix = objects[i]->GetModelMatrix();
		glUniformMatrix4fv(this->GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniform3fv(GetUniformLocation("objectColor"), 1, glm::value_ptr(objects[i]->color));
		objects[i]->Draw();
	}
}

void Shader::Update()
{
	cout << "Shader updated";
	this->SetCamera();
	this->SetModels();
}

GLint Shader::GetUniformLocation(const string& name)
{
	//map iterator
	auto it = uniformLocations.find(name);

	//if found then return
	if (it != uniformLocations.end()) {
		return it->second;
	}

	GLint location = glGetUniformLocation(this->Id, name.c_str());
	uniformLocations[name] = location;

	return location;
}


string Shader::GetShaderCode(const char* filename)
{
	ifstream stream(filename, ios::binary);
	if (stream)
	{
		string contents;
		stream.seekg(0, ios::end);
		contents.resize(stream.tellg());
		stream.seekg(0, ios::beg);
		stream.read(&contents[0], contents.size());
		stream.close();
		return contents;
	}

	throw errno;
}

void Shader::CompileErrors(GLuint shader, const char* type, GLenum pname)
{
	GLint status;

	if (type == "PROGRAM")
	{
		glGetProgramiv(shader, pname, &status);
		if (status == GL_FALSE)
		{
			GLint infoLogLength;
			glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
			GLchar* strInfoLog = new GLchar[infoLogLength + 1];
			glGetProgramInfoLog(shader, infoLogLength, NULL, strInfoLog);
			fprintf(stderr, "%s failure: %s\n", type, strInfoLog);
			delete[] strInfoLog;
		}
	}
	else
	{
		glGetShaderiv(shader, pname, &status);
		if (status == GL_FALSE)
		{
			GLint infoLogLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
			GLchar* strInfoLog = new GLchar[infoLogLength + 1];
			glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
			fprintf(stderr, "%s failure: %s\n", type, strInfoLog);
			delete[] strInfoLog;
		}
	}
}
