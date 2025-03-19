#Shader Vertex
#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTex;

out vec2 texCoord;
out vec3 color;


void main()
{
	gl_Position = vec4(aPos, 1.0f);
	color = aColor;
	texCoord = vec2(aTex.x,aTex.y);
}

#Shader Fragment
#version 460 core

in vec2 texCoord;
in vec3 color;

uniform sampler2D tex0;
uniform sampler2D tex1;

uniform float mixValue;

out vec4 FragColor;

void main()
{
	FragColor = mix(texture(tex0,texCoord), texture(tex1,texCoord), mixValue);
	//FragColor1 = texture(tex1,texCoord2);
}