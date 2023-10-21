#version 330

uniform sampler2D image;
in vec2 uv;
out vec4 out_color;

void main() {
    // Get the Red, green, blue values from the image
    float red = texture(image, uv).r;
    // Offset green and blue
    float green = texture(image, uv).g;
    float blue = texture(image, uv).b;
    float alpha = texture(image, uv).a;
    
    out_color = vec4(red, green, blue, alpha);
}