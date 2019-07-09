// Version du GLSL

#version 450 core


// Entrées

layout(location =0)in vec3 in_Vertex;
layout(location =1)in vec3 in_Color;


// Uniform

layout(location =2) uniform mat4 projection;
layout(location =3) uniform mat4 modelview;


// Sortie

out vec3 color;


// Fonction main

void main()
{
    // Position finale du vertex en 3D

    gl_Position = projection * modelview * vec4(in_Vertex, 1.0);


    // Envoi de la couleur au Fragment Shader

    color = in_Color;
}
