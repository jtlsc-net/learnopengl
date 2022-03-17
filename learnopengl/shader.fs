#version 330 core
out vec4 FragColor;
in vec3 ourColor;
float near = 0.1; 
float far  = 100.0;
uniform int showDepth;
// taken from https://learnopengl.com/Advanced-OpenGL/Depth-testing
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main()
{
    if (showDepth == 1) {
        float depth = LinearizeDepth(gl_FragCoord.z) / far; // divide by far for demonstration
        FragColor = vec4(vec3(depth), 1.0);
    }
    else {
        FragColor = vec4(ourColor, 1.0);
    }
}