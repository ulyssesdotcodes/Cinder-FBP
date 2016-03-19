#version 330 core

uniform sampler2D tex;
uniform vec2 i_resolution;
uniform vec2 i_scale;
uniform vec2 i_pivot;

out vec4 fragColor;

void main()
{
	vec2 pos = gl_FragCoord.xy / i_resolution.xy;
	vec2 posPrime = (pos - i_pivot) * (1 / i_scale) + i_pivot;
	fragColor = vec4(texture2D(tex, posPrime).xyz, 1);
}
