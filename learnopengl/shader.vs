#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 nPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform int shaderType;
out vec3 ourColor;
out vec3 FragPos;
out vec3 Normal;
out vec3 lightAdjusted;
vec3 lightPos = vec3(-100.0f, 100.0f, 100.0f);
float diffuseCoeff = 0.8;
float illumination = 1;
void main()
{
	if(shaderType == 1) { // FragPos and Normal output default vals
		//lightPos = vec3(model * vec4(lightPos, 1.0));
		vec3 norm = normalize(vec3(model * vec4(nPos, 1.0)));
		vec3 pos = vec3(model * vec4(aPos, 1.0));
		vec3 lightDir = normalize(lightPos - pos);
		float diffuseMax = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diffuseCoeff * illumination * diffuseMax * vec3(1.0f);
		ourColor = (vec3(0.1) + diffuse) * vec3(0.0, 0.8, 0.3);
		FragPos = vec3(0.0, 0.0, 0.0);
		Normal = vec3(0.0, 0.0, 0.0);
		lightAdjusted = vec3(0.0f);
	}
	else if(shaderType == 2) { // FragPos and Normal output actual vals
		ourColor = vec3(0.0, 0.8, 0.3);
		FragPos = vec3(model * vec4(aPos, 1.0));
		// Normal = normalize(vec3(model * vec4(nPos, 1.0)));
		Normal = nPos;
		lightAdjusted = vec3(model * vec4(lightPos, 1.0));
	}
	else{ // FragPos and Normal output default vals
		ourColor = vec3(0.0, 0.8, 0.3);
		FragPos = vec3(model * vec4(aPos, 1.0));
		Normal = vec3(model * vec4(nPos, 1.0));
		lightAdjusted = vec3(0.0f);
		// lightAdjusted = vec3(model * vec4(lightPos, 1.0));
	}
	gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}