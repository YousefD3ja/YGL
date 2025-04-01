#Shader Vertex
#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTex;

out vec2 texCoord;

uniform	mat4 projection;
uniform	mat4 view;
uniform	mat4 model;
uniform	mat4 ChunkModel;


void main()
{
	gl_Position = projection * view * ChunkModel * model * vec4(aPos, 1.0f);
	texCoord = vec2(aTex.x,aTex.y);
}

#Shader Fragment
#version 460 core

in vec2 texCoord;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;

uniform float mixValue;

out vec4 FragColor;

void main()
{
	FragColor = texture(tex0,texCoord);
	//FragColor1 = texture(tex1,texCoord2);
}