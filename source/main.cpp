#include<iostream>

#include "GL/glew.h"

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Shader.h"
#include "LoadTexture.h"
#include "Camera.h"

using namespace std;

GLfloat vertices[] = { 
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f };

// Positions all containers
glm::vec3 cubePositions[] = {
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(2.0f, 5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f, 3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f, 2.0f, -2.5f),
	glm::vec3(1.5f, 0.2f, -1.5f),
	glm::vec3(-1.3f, 1.0f, -1.5f)
};
//
//GLuint indices[] = {
//0,1,2,
//0,2,3
//};
//
//GLfloat vertices1[] = { 0.5, 0.5, 0.0,
//1.0, 0.5, 0.0,
//1.0, 1.0, 0.0 };

#if 0
const char* vertex_shader = "#version 330 core\n"
"layout(location = 0) in vec3 position;\n"
"layout(location = 1) in vec3 color;\n"
"uniform vec4 move;\n"
"out vec4 ourcolor;\n"
"void main()\n"
"{\n"
"gl_Position=vec4(position.x*move.x,position.y*move.x,position.z,1.0)+move;\n"
"ourcolor=vec4(color,1.0);\n"
"}\n\0";

const char* fragment_shader = "#version 330 core\n"
"out vec4 ver_color;\n"
"in vec4 ourcolor;"
"void main()\n"
"{\n"
"ver_color=ourcolor;"
"}\n\0";

//const char* fragment_shader1 = "#version 330 core\n"
//"out vec4 color;"
//"void main()\n"
//"{\n"
//"color=vec4(0.9,0.9,0.1,1.0);"
//"}\n\0";
#endif

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool    keys[1024];

// Light attributes
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame


int main()
{
   //初始化glfw库设置
	glfwInit();
	glfwWindowHint(GLFW_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_CORE_PROFILE,GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	GLFWwindow* windows=  glfwCreateWindow(640, 640, "test", NULL, nullptr);
	glfwMakeContextCurrent(windows);
	// Set the required callback functions
	glfwSetKeyCallback(windows, key_callback);
	glfwSetCursorPosCallback(windows, mouse_callback);
	glfwSetScrollCallback(windows, scroll_callback);

	// GLFW Options
	glfwSetInputMode(windows, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	

	glewExperimental = GL_TRUE;
	if (glewInit()!=GLEW_OK)
	{
		cout << "初始化glew失败" << endl;
	}

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);
	//创建VBO
	//GLuint VBO ,VBO1,EBO;
	//glGenBuffers(1, &VBO);
	//glGenBuffers(1, &VBO1);
	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//Shader test("C://Users//Thinkpad//Desktop//LearnOpenGL//Shader//Shader.vs","C://Users//Thinkpad//Desktop//LearnOpenGL//Shader//Shader.frag");
	// Build and compile our shader program
	Shader lightingShader("C://Users//Thinkpad//Desktop//LearnOpenGL//Shader//lighting.vs", "C://Users//Thinkpad//Desktop//LearnOpenGL//Shader//lighting.frag");
	Shader lampShader("C://Users//Thinkpad//Desktop//LearnOpenGL//Shader//lamp.vs", "C://Users//Thinkpad//Desktop//LearnOpenGL//Shader//lamp.frag");

#if 0
	//创建顶点着色器及编译顶点着色器
	GLint shadervertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shadervertex, 1, &vertex_shader, nullptr);
	glCompileShader(shadervertex);

	//检测顶点着色器是否成功
	GLint success;
	GLchar info[512];
	glGetShaderiv(shadervertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shadervertex, 512, nullptr, info);
		cout << "Error: Shader: Vertex: COMPILED FAILED" << info << endl;
	}

	//创建片元着色器并编译片元着色器
	GLint fragmentshader;
	fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, &fragment_shader, nullptr);
	glCompileShader(fragmentshader);

	//
	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentshader, 512, nullptr, info);
		cout << "Error:Shader:Fragment:COMPILED　FAILED" << info << endl;
	}

	//创建片元着色器并编译片元着色器
	//GLint fragmentshader1;
	//fragmentshader1 = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentshader1, 1, &fragment_shader1, nullptr);
	//glCompileShader(fragmentshader1);

	//
	//glGetShaderiv(fragmentshader1, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	glGetShaderInfoLog(fragmentshader1, 512, nullptr, info);
	//	cout << "Error:Shader:Fragment:COMPILED　FAILED" << info << endl;
	//}
	//创建程序对象
	GLuint ShaderProgram;
	ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, shadervertex);
	glAttachShader(ShaderProgram, fragmentshader);
	glLinkProgram(ShaderProgram);

	//创建程序对象
	//GLuint ShaderProgram1;
	//ShaderProgram1 = glCreateProgram();
	//glAttachShader(ShaderProgram1, shadervertex);
	//glAttachShader(ShaderProgram1, fragmentshader1);
	//glLinkProgram(ShaderProgram1);

	glDeleteShader(shadervertex);
	glDeleteShader(fragmentshader);
	//glDeleteShader(fragmentshader1);
	glGetProgramiv(ShaderProgram, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ShaderProgram, 512, nullptr, info);
		cout << "Error:" << info << endl;
	}
#endif

	
	// First, set the container's VAO (and VBO)
	GLuint VBO, containerVAO;
	glGenVertexArrays(1, &containerVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(containerVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	// Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); // Note that we skip over the other data in our buffer object (we don't need the normals/textures, only positions).
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);



	//glGenVertexArrays(1, &VAO1);
	//glBindVertexArray(VAO1);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	////连接顶点属性
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
	//glEnableVertexAttribArray(0);
	//glBindVertexArray(0);

	//加载纹理1

	// Load textures
	GLuint diffuseMap, specularMap, emissionMap;
	glGenTextures(1, &diffuseMap);
	glGenTextures(1, &specularMap);
	glGenTextures(1, &emissionMap);
	int width, height;
	unsigned char* image;
	// Diffuse map

	LoadTexture loadtextre1("C://Users//Thinkpad//Desktop//LearnOpenGL//textures//container2.png");
	image = loadtextre1.Load_Image();
	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, *loadtextre1.width, *loadtextre1.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	// Specular map

	LoadTexture loadtextre2("C://Users//Thinkpad//Desktop//LearnOpenGL//textures//box.jpg");
	image = loadtextre2.Load_Image();
	glBindTexture(GL_TEXTURE_2D, specularMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, *loadtextre2.width, *loadtextre2.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);


	// Set texture units
	lightingShader.ShaderProgramUse();;
	glUniform1i(glGetUniformLocation(lightingShader.ShaderProgram, "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.ShaderProgram, "material.specular"), 1);
	
	//设置显示模型
	while (!glfwWindowShouldClose(windows))
	{
		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		do_movement();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.ShaderProgramUse();
		//GLint lightPosLoc = glGetUniformLocation(lightingShader.Program, "light.position");
		GLint lightDirLoc = glGetUniformLocation(lightingShader.ShaderProgram, "light.direction");
		GLint viewPosLoc = glGetUniformLocation(lightingShader.ShaderProgram, "viewPos");
		glUniform3f(lightDirLoc, -0.2f, -1.0f, -0.3f);
		glUniform3f(viewPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);
		// Set lights properties
		glUniform3f(glGetUniformLocation(lightingShader.ShaderProgram, "light.ambient"), 0.2f, 0.2f, 0.2f);
		glUniform3f(glGetUniformLocation(lightingShader.ShaderProgram, "light.diffuse"), 0.5f, 0.5f, 0.5f);
		glUniform3f(glGetUniformLocation(lightingShader.ShaderProgram, "light.specular"), 1.0f, 1.0f, 1.0f);
		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.ShaderProgram, "material.shininess"), 32.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(camera.Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.ShaderProgram, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.ShaderProgram, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.ShaderProgram, "projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		// Bind specular map
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);

		// Draw the container (using container's vertex attributes)
		/*glBindVertexArray(containerVAO);
		glm::mat4 model;
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);*/

		// Draw 10 containers with the same VAO and VBO information; only their world space coordinates differ
		glm::mat4 model;
		glBindVertexArray(containerVAO);
		for (GLuint i = 0; i < 10; i++)
		{
			model = glm::mat4();
			model = glm::translate(model, cubePositions[i]);
			GLfloat angle = 20.0f * i;
			model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);


		// A lamp object is a bit useless with a directional light since it has no origin.
		// 
		//// Also draw the lamp object, again binding the appropriate shader
		//lampShader.Use();
		//// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		//modelLoc = glGetUniformLocation(lampShader.Program, "model");
		//viewLoc  = glGetUniformLocation(lampShader.Program, "view");
		//projLoc  = glGetUniformLocation(lampShader.Program, "projection");
		//// Set matrices
		//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		//model = glm::mat4();
		//model = glm::translate(model, lightPos);
		//model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//// Draw the light object (using light's vertex attributes)
		//glBindVertexArray(lightVAO);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		//glBindVertexArray(0);


		// Swap the screen buffers
		glfwSwapBuffers(windows);
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	//glfwTerminate();
	return 0;
}
void key_callback(GLFWwindow* windows, int key, int skancode, int action, int mode)
{
	switch (action)
	{
	case GLFW_PRESS:

		switch (key)
		{
		case GLFW_KEY_1:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			//glLineWidth(1);//设置线宽
			cout << "线框模式" << endl;
			break;
		case GLFW_KEY_2:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			cout << "填充模式" << endl;
			break;

		case GLFW_KEY_ESCAPE:
			cout << "将退出程序" << endl;
			glfwTerminate();
			exit(-1);
			break;
		default:
			break;
		}
		break;
	default:
		//do nothing
		break;
	}
	

}

void do_movement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}