#version 330 core

uniform int testUniform;

out vec4 FragColor;

void main()
{
    // Set the output color of the fragment
    FragColor = vec4(1.0, 1.0, 1.0, 1.0) * float(testUniform);
}
