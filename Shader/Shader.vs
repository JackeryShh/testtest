#version 330 core

layout(location = 0) in vec3 vertexposition;
//vertexcolor是顶点的颜色，一般是默认的，在没有材质或者纹理状态下的颜色。
//如果有纹理颜色的话，这个颜色是没存在的必要，除非是需要将为与模型颜色做混合，
//在本例中排列顺序为顶点坐标，顶点颜色等，在模型中，
layout(location = 1) in vec3 vertexcolor;//顶点颜色
layout(location = 2) in vec2 texturecord;//纹理坐标 
out vec4 color;
uniform vec4 move;
//uniform vec4 ourcolor;
out vec2 texcordition;

uniform mat4 translate;

void main()
{
gl_Position=translate*vec4(vertexposition,1.0);
color=vec4(vertexcolor,1.0);//ourcolor;
texcordition=vec2(texturecord.x,1.0-texturecord.y);
}
