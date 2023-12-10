// --- Shader . cpp ---
# include "Shader.h"
# include "Camera.h"
Shader::Shader(Camera* c, const char * vertexFile, const char * fragmentFile) {

	this->cam_ = c;
	this->type_ = vertexFile;

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

	this->id_ = glCreateProgram();
	CompileErrors(id_, "PROGRAM", GL_COMPILE_STATUS);

	glAttachShader(id_, fragmentShader);
	glAttachShader(id_, vertexShader);
	glLinkProgram(id_);

	CompileErrors(id_, "PROGRAM", GL_LINK_STATUS);


}

Shader::Shader(const char* vertexFile, const char* fragmentFile) : Shader(nullptr, vertexFile, fragmentFile)
{
}

Shader::Shader(Camera* c) : Shader(c, "default.vert", "default.frag"){}

void Shader::Activate()
{
	glUseProgram(this->id_);
}

void Shader::Deactivate()
{
	glUseProgram(0);
}

void Shader::Delete()
{
	glDeleteProgram(this->id_);
}

void Shader::LightsCount(int n)
{
	glUniform1i(GetUniformLocation("numLights"), n);
}


void Shader::SetTexture(GLuint* texture)
{
}


void Shader::Update()
{
	this->Activate();
}

GLint Shader::GetUniformLocation(const string& name)
{
	//map iterator
	auto it = uniformLocations.find(name);

	//if found then return
	if (it != uniformLocations.end()) {
		return it->second;
	}

	GLint location = glGetUniformLocation(this->id_, name.c_str());
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
