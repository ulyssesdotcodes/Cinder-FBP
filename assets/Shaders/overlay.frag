#version 330 core

uniform sampler2D tex1;
uniform sampler2D tex2;
uniform vec2 i_resolution;

out vec4 fragColor;

void main()
{
	vec2 pos = gl_FragCoord.xy / i_resolution.xy;
	fragColor = vec4(texture2D(tex1, pos).xyz + texture2D(tex2, pos).xyz, 1);
}
