#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec3 FragPos;
in vec3 Normal;
in vec3 lightAdjusted;
float near = 0.1; 
float far  = 100.0;
vec3 ambient = vec3(0.1f);
float diffuseCoeff = 0.8;
float illumination = 1;
float specularStrength = 0.9;
vec3 lightPos = vec3(-40.0f, 40.0f, 40.0f);
uniform int showDepth;
uniform int shaderType;
uniform vec3 viewPos;
// taken from https://learnopengl.com/Advanced-OpenGL/Depth-testing
float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main()
{
    if (shaderType == 2) {
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        // vec3 lightDir = lightAdjusted;
        // vec3 lightDir = normalize(lightAdjusted - FragPos);
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = specularStrength * spec * vec3(1.0, 1.0, 1.0);
        float diffuseMax = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diffuseCoeff * illumination * diffuseMax * vec3(1.0, 1.0, 1.0);
        vec3 result = (ambient + diffuse + specular) * ourColor;
        FragColor = vec4(result, 1.0);
    }
    else {
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * ourColor;
        vec3 result = (ambient + diffuse) * ourColor;
        FragColor = vec4(result, 1.0);
    }
    if (showDepth == 1) {
        float depth = LinearizeDepth(gl_FragCoord.z) / far; // divide by far for demonstration
        FragColor = vec4(vec3(depth), 1.0);
    }
}