## Python AMD's FSR/CAS implementation with modernGL Shaders

### Implemented Shaders
<ul>
    <li>AMD CAS  https://www.shadertoy.com/view/stXSWB</li>
    <li>AMD EASU  https://www.shadertoy.com/view/stXSWB</li>
    <li>Slimmed FSR  https://www.shadertoy.com/view/ftsXzM\</li>
</ul>


### ShaderToy Porting Guide

This porting guide is only for <b>Static</b> image, such as image processing or upscaling,

Does not support shaderToy animation with iTime or iMouse, for this one may refer to
https://www.youtube.com/watch?v=SGLvMc7BK2E where you need to manually pass the iTime and iMouse.

Note: The guide provided is using pyOpenGL.


For the boilerplate to load, perform shader, and save image can refer to this example.
https://github.com/moderngl/moderngl/blob/master/examples/image_shader_example.py

NOTE: This will cause CPU spike due to save image everytime it renders, 
and sometimes the output might be not complete (some images will be cut)

Need to comment out the save image code from the example.

### Common modernGL and ShaderToy

This is the list of the similar methods used by the boilerplate earlier, mostly just name change issue

If the shaderToy method does not exist here, may refer to port guide.

#### uv
No need to recalculate, with fragcord and resolution, can just use uv directly.
```
uv = in_uv
```

#### iChannel0
```
uniform sampler2D image; 
iChannel0 = image
```

#### fragColor
```
out vec4 out_color;
fragColor = out_color
```

### ShaderToy Port to modernGL

#### fragCoord
```
vec2 fragCoord = gl_FragCoord.xy
```

#### iChannelResolution
This is the size for your texture, note that we only handle one texture.
```
vec2 iChannelResolution = textureSize(iChannel0, 0);
```

#### iChannelResolution[0]
Note that shaderToy does have multiple channel, but for the example only have one, so we can replace it like
```
iChannelResolution[0] => iChannelResolution
```

#### iResolution
This is the system output resolution, either follow the original texture size,
or follow your screen resolution
```
vec2 iResolution = textureSize(iChannel0, 0);
vec2 iResolution = vec2(1920,1080)
```


    




