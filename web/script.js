

const vert = `
precision highp float;
attribute vec2 position;

void main() {
  gl_Position = vec4(position, 0, 1.0);
}
`;

const frag = `
precision highp float;

uniform float width;
uniform float height;
uniform float texWidth;
uniform float texHeight;
const float sharpness =10000.0;
uniform sampler2D iChannel0;


vec4 getPixel(vec2 pos) {
	vec2 coord = (pos + .5) / vec2(width, height);
	coord.y = 1.0 - coord.y;
	return texture2D(iChannel0, coord);
}


void main() {

  vec3 a = getPixel(gl_FragCoord.xy + vec2(-1.0,-1.0)).rgb;
  vec3 b = getPixel(gl_FragCoord.xy + vec2( 0.0,-1.0)).rgb;
  vec3 c = getPixel(gl_FragCoord.xy + vec2( 1.0,-1.0)).rgb;
  vec3 d = getPixel(gl_FragCoord.xy + vec2(-1.0, 0.0)).rgb;
  vec3 e = getPixel(gl_FragCoord.xy).rgb;
  vec3 f = getPixel(gl_FragCoord.xy + vec2( 1.0, 0.0)).rgb;
  vec3 g = getPixel(gl_FragCoord.xy + vec2(-1.0, 1.0)).rgb;
  vec3 h = getPixel(gl_FragCoord.xy + vec2( 0.0, 1.0)).rgb;
  vec3 i = getPixel(gl_FragCoord.xy + vec2( 1.0, 1.0)).rgb;;

  // Soft min and max.
  //  a b c             b
  //  d e f * 0.5  +  d e f * 0.5
  //  g h i             h
  // These are 2.0x bigger (factored out the extra multiply).

  vec3 mnRGB  = min(min(min(d,e),min(f,b)),h);
  vec3 mnRGB2 = min(min(min(mnRGB,a),min(g,c)),i);
  mnRGB += mnRGB2;

  vec3 mxRGB  = max(max(max(d,e),max(f,b)),h);
  vec3 mxRGB2 = max(max(max(mxRGB,a),max(g,c)),i);
  mxRGB += mxRGB2;

  // Smooth minimum distance to signal limit divided by smooth max.

  vec3 rcpMxRGB = vec3(1)/mxRGB;
  vec3 ampRGB = clamp((min(mnRGB,2.0-mxRGB) * rcpMxRGB),0.0,1.0);
  // Shaping amount of sharpening.
  ampRGB = inversesqrt(ampRGB);
  float peak = 8.0 - 3.0 * sharpness;
  vec3 wRGB = -vec3(1)/(ampRGB * peak);
  vec3 rcpWeightRGB = vec3(1)/(1.0 + 4.0 * wRGB);
  //                          0 w 0
  //  Filter shape:           w 1 w
  //                          0 w 0  

  vec3 window = (b + d) + (f + h);
  vec3 outColor = clamp((window * wRGB + e) * rcpWeightRGB,0.0,1.0);

  //gl_FragColor = vec4(outColor,getPixel(gl_FragCoord.xy).a);
  gl_FragColor = vec4(e,getPixel(gl_FragCoord.xy).a);
}
`;

const glea = new GLea({
  shaders: [GLea.fragmentShader(frag), GLea.vertexShader(vert)]}).create();

function loop(time) {
  const { gl, width, height } = glea;
  glea.clear();
  glea.uni('width', glea.width);
  glea.uni('height', glea.height);
  gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);
  requestAnimationFrame(loop);
}

function loadImage(url) {
  return new Promise((resolve, reject) => {
    const img = new Image();
    img.crossOrigin = 'Anonymous';
    img.src = url;
    img.onload = () => {
      resolve(img);
    };
    img.onerror = () => {
      reject(img);
    };
  });
}


async function setup() {
  const { gl } = glea;
  window.addEventListener('resize', () => {
    glea.resize();
  });
  image =  await loadImage('https://upload.wikimedia.org/wikipedia/en/7/7d/Lenna_%28test_image%29.png')
  
  camTexture = glea.createTexture(0);
  gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, image);
  glea.setActiveTexture(0, camTexture);
  loop(0);
}

setup();