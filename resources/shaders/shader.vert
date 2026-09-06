#version 330 core

uniform mat4 uProjection;
uniform mat4 uModel;

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTex;

out vec2 fTex;

void main() {
	fTex = aTex;
	gl_Position = uProjection * uModel * vec4(aPos, 0.0, 1.0);
}
