# Computational Project
Part II Computational Project: Tidal Tails

## Required:

1. C++ compiler (GNU g++)
1. SDL2
1. OpenGL
1. cmake
  
## Todo:

1. Might not need FindOpenGL.cmake
1. Screenshot ability
1. Camera controls (left click (pan), right click (rotate), scroll button (zoom)
1. System init (start up arguments, N, distribution)
1. Console output and logs (can suppress?)
1. Integrator (RK4)
1. Stepping (forwards and backwards
1. Collisions
1. Window controls (q (restart, press twice),w (screenshot), s (pause/play), e (start/stop record),  a (rewind), d (forward))
1. Scale (G,mass,distance,time)

## Instructions to build project:

```bash
	cd {project-directory}
	cmake .
	make
```
## Documentation:

Project executable located in bin directory and is called main.
	
### License:

MIT License

Copyright (c) 2016 Jordan Osborn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

### Acknowledgements:

Files in cmake folder are used to help cmake locate the various libraries used by this project, these files were not created by me and thanks must go to their respective authors. License texts accompany each file at the top of each file's source code.

 
