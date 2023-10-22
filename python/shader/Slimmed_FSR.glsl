// GLSL Source : https://www.shadertoy.com/view/ftsXzM\
// Doesn't use gl_FragCoord, this will prevent multiple image

#version 330

in vec2 uv;
uniform sampler2D iChannel0;
out vec4 fragColor;

void main() {
   vec2 iChannelResolution = textureSize(iChannel0, 0);
   vec2 iResolution = textureSize(iChannel0, 0);
   vec2 fragCoord = gl_FragCoord.xy;

   vec3 col = texture(iChannel0, uv).xyz;
   // CAS algorithm
   float max_g = col.y;
   float min_g = col.y;
   vec4 uvoff = vec4(1,0,1,-1)/iChannelResolution.xxyy;
   vec3 colw;
   vec3 col1 = texture(iChannel0, uv+uvoff.yw).xyz;
   max_g = max(max_g, col1.y);
   min_g = min(min_g, col1.y);
   colw = col1;
   col1 = texture(iChannel0, uv+uvoff.xy).xyz;
   max_g = max(max_g, col1.y);
   min_g = min(min_g, col1.y);
   colw += col1;
   col1 = texture(iChannel0, uv+uvoff.yz).xyz;
   max_g = max(max_g, col1.y);
   min_g = min(min_g, col1.y);
   colw += col1;
   col1 = texture(iChannel0, uv-uvoff.xy).xyz;
   max_g = max(max_g, col1.y);
   min_g = min(min_g, col1.y);
   colw += col1;
   float d_min_g = min_g;
   float d_max_g = 1.-max_g;
   float A;
   if (d_max_g < d_min_g) {
      A = d_max_g / max_g;
   } else {
      A = d_min_g / max_g;
   }

   A = sqrt(A);

   vec3 col_out = (col + colw * A) / (1.+4.*A);
	fragColor =  vec4(col_out,1.0);
}