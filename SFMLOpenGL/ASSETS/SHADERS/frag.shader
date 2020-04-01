#version 400

uniform sampler2D f_texture;

in vec4 color;
in vec2 uv;

out vec4 fColor;

void main() {
	fColor = texture2D(f_texture, uv);
	//fColor = vec4( 1.0f, 0.0f, 0.0f, 1.0f );
};