#Shader Vertex
#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTex;

out vec2 texCoord;

void main()
{
	gl_Position = vec4(aPos, 1.0f);
	texCoord = vec2(aTex.x, aTex.y);
}

#Shader Fragment
#version 460 core

in vec2 texCoord;

uniform sampler2D tex0;

out vec4 FragColor;

void main()
{
	FragColor = texture(tex0, texCoord);
}