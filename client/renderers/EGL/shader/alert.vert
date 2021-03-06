#version 300 es

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

uniform vec2 screen;
uniform vec2 size;
uniform vec4 color;

out highp vec2 uv;
out highp vec4 c;

void main()
{
  gl_Position.xyz = vertexPosition_modelspace;
  gl_Position.w   = 1.0;
  gl_Position.xy *= screen.xy * size.xy;

  uv = vertexUV;
  c  = color;
}
