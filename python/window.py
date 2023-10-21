import os

import moderngl_window as mglw


class Window(mglw.WindowConfig):
    gl_version = (3, 3)
    title = "ModernGL Window"
    window_size = (1280, 720)
    aspect_ratio = 16 / 9
    resizable = True
