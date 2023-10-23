#include "ffx_cas.h"

in vec2 uv;
uniform sampler2D iChannel0;
out vec4 fragColor;


void main() {
    vec3 col = texture(iChannel0, uv).xyz;
    fragColor =  vec4(col_out,1.0);
}
