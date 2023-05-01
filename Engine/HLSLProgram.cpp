#include "HLSLProgram.h"
#include "Error.h"
#include <fstream>
#include <vector>
using namespace std;

HLSLProgram::HLSLProgram():programID(0),vertexShaderID(0),fragmentShaderID(0), numAtribute(0) {
}

HLSLProgram::~HLSLProgram() {
}

void HLSLProgram::use() {
	glUseProgram(programID);
	for (int i = 0; i < numAtribute; i++)
		glEnableVertexAttribArray(i);
}
void HLSLProgram::unuse() {
	glUseProgram(0);
	for (int i = 0; i < numAtribute; i++)
		glDisableVertexAttribArray(i);
}
void HLSLProgram::addAtribute(const string attributeName) {
	glBindAttribLocation(programID, numAtribute++, attributeName.c_str());
}
void HLSLProgram::compileShaders(const string& vertexShaderFilePath, const string& fragmentShaderFilePath){
	programID = glCreateProgram();
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (vertexShaderID == 0) {
		fatalError("ERORR creating Vertex Shader");
	}
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (fragmentShaderID == 0) {
		fatalError("ERROR creating Fragment Shader");
	}
	compileShader(vertexShaderFilePath, vertexShaderID);
	compileShader(fragmentShaderFilePath, fragmentShaderID);
}
void HLSLProgram::compileShader(const string& shaderPath, GLuint id) {
	string filecontent = "";
	string line = "";
	ifstream shaderFile(shaderPath);
	if (shaderFile.fail()) {
		fatalError("Coul not open " + shaderPath);
	}
	while (getline(shaderFile, line)) {
		filecontent += line + "\n";
	}
	shaderFile.close();
	const char* contents = filecontent.c_str();
	glShaderSource(id, 1, &contents, nullptr);
	glCompileShader(id);
	GLint isCompiledd = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiledd);
	if (isCompiledd == GL_FALSE) {
		GLint maxLenght = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLenght);
		vector<GLchar> infolog(maxLenght);
		glGetShaderInfoLog(id, maxLenght, &maxLenght, &infolog[0]);
		fatalError("Shader could not compiled " + printf("%s", &(infolog[0])));
		glDeleteShader(id);
		return;
	}
}
void HLSLProgram::linkShader() {
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	GLint isLinked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);
		vector<GLchar> infolog(maxLength);
		glGetProgramInfoLog(programID, maxLength, &maxLength, &infolog[0]);
		glDeleteProgram(programID);
		fatalError("Shader couldn't link " + printf("%s", &(infolog[0])));
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
		return;
	}
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}