#Shader Vertex
#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTex;
layout(location = 2) in vec2 aTex2;

out vec3 color;

out vec2 texCoord;
out vec2 texCoord2;

uniform float scale;

void main()
{

	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	color = aColor;
	texCoord = aTex;
	texCoord2 = aTex2;
}

#Shader Fragment
#version 460 core

in vec3 color;
in vec2 texCoord;
in vec2 texCoord2;

uniform sampler2D tex0;
uniform sampler2D tex1;

uniform vec4 color1;

out vec4 FragColor;
out vec4 FragColor1;

void main()
{
	FragColor = texture(tex0,texCoord) * vec4(color1);
	//FragColor1 = texture(tex1,texCoord2);
	FragColor1 = texture(tex1,texCoord2) * vec4(color1);
}