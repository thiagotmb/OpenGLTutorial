#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec3 color;

out vec4 vertexColor;

void main(){
    
    
    gl_Position = vec4(position.x,position.y,0.0f,1.0f);
    vertexColor = vec4(color, 1.0f);
    
}