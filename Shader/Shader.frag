#version 330 core
in vec2 texcordition;
in vec4 color;
out vec4 outcolor;
//uniform变量是全局变量，可以直接在片元着色器中使用，而不用通过顶点着色器；
//不过可以通过顶点着色器传输，但没有这个必要。
uniform vec4 ourcolor;
uniform sampler2D  texture1;
uniform sampler2D  texture2; 

void main()
{
   //outcolor=texture(texture2,texcordition) *ourcolor;
   outcolor=mix(texture(texture1, texcordition), texture(texture2, texcordition), 0.5);

}

