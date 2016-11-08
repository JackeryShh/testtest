#pragma  once 
#include "Shader.h"

Shader::Shader(const char* vertexsource_path, const char* fragmentsource_path)
{
	//注意ifstream与ofstream的区别  ifstream是硬盘文件到内存，也就是从文件中读文件到内存中；
	//而ofstream是将文件流输出到文件中，是从内存到硬盘文件的一种过程；具体看博客：http://blog.csdn.net/augusdi/article/details/8865378
	
	ifstream vertexShaderFile, fragmentShaderFile;
	vertexShaderFile.open(vertexsource_path);
	fragmentShaderFile.open(fragmentsource_path);
	stringstream str_vertexsource, str_fragmentsource;
	str_vertexsource << vertexShaderFile.rdbuf();
	str_fragmentsource << fragmentShaderFile.rdbuf();

	//从字符串流转换成字符串
	string vertexcode = str_vertexsource.str();
	string framentcode = str_fragmentsource.str();
	const char* char_vertexcode = vertexcode.c_str();
	const char* char_fragmentcode = framentcode.c_str();

	//创建并编译顶点着色器
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &char_vertexcode, nullptr);
	glCompileShader(vertexShader);

	//检查顶点着色器编译信息，如果又错误，则打印错误
	GLint vertex_success;
	char vertex_info[1024];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertex_success);
	if (!vertex_success)
	{
		//获取错误信息
		glGetShaderInfoLog(vertexShader, 1024, nullptr, vertex_info);
		cout << "顶点着色器错误，错误信息： " << vertex_info << endl;
	}


	//创建并编译片段着色器
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &char_fragmentcode, nullptr);
	glCompileShader(fragmentShader);

	//检查片段着色器，若有错误则输出错误信息
	GLint fragment_success;
	char  fragment_info[1024];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragment_success);
    if (!fragment_success)
    {
		glGetShaderInfoLog(fragmentShader, 1024, nullptr, fragment_info);
		cout << "片段着色器错误，错误信息为： " << fragment_info << endl;
    }
	
	//创建着色器程序，关联现有着色器并链接各个着色器
	ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, vertexShader);
	glAttachShader(ShaderProgram, fragmentShader);
	glLinkProgram(ShaderProgram);

	//检查链接着色器程序是否又错误，若有错误，则输出错误信息
	GLint ShaderProgram_success;
	char ShaderProgram_info[1024];
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &ShaderProgram_success);
	if (!ShaderProgram_success)
	{
		glGetProgramInfoLog(ShaderProgram, 1024,nullptr,ShaderProgram_info);
	}
	//删除已经绑定的着色器
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}


void Shader::ShaderProgramUse()
{
	glUseProgram(ShaderProgram);
}

Shader::~Shader()
{


}