# Computational Project
Part II Computational Project: Tidal Tails
Candidate Number: 6892V

## Required:

1. C++ compiler (C++11 compliant)
1. SDL2
1. OpenGL
1. GLEW
1. cmake
## Instructions to build and run project:

```bash
	cd {project-directory}
	cmake .
	make
	cd bin
	./main {command-line-arguments}
	bin/main
```
## Controls
1. Pan - WASD $(\uparrow \leftarrow \downarrow \rightarrow)$.
1. Zoom out/in - QE $(-+)$.
1. Take Screenshot - P (screenshots are automatically taken at 5.0s intervals (simulated system time)) (.tga file created, can be converted with convert\_png.sh script provided).
1. Start/Stop data logging to .csv - L.
1. Start/Pause/Unpause - SPACEBAR.
1. INTERACTIVE == true - left click, drag then release to create a massive particle with velocity proportional to length and direction of drag.

## Documentation:

Project executable (main) as well as plot.p and convert_png.sh located in bin directory.

Command line arguments: 5 arguments supplied (Eccentricity, $\theta_0$, Closest Approach, Rotation direction of central galaxy ($-1=\circlearrowright, 1=\circlearrowleft$), Perturbation orbit direction).

Command line arguments: 4 arguments supplied (Eccentricity, $\theta_0$, Closest Approach, TESTING (1 = true, 0 = false))

Command line arguments:1 argument supplied (INTERACTIVE (1 = true, 0 = false))

Other combinations result in a default simulation being carried out.

Logging Information: Each time step is output to a new line in the data file so that each line has the format t,{x1,y1,z1},{x2,y2,z2},...,{xN,yN,zN}. A Python script could easily be created to carry out text processing on this data file to extract all of the particle's positions at a specific time. The extracted positions could then be written to a text file in a plot friendly format i.e. x1,y2 {newline} x2,y2 etc. and then plotted (matplotlib) all within the same script. This script was not created as it was felt that the screenshots provided sufficient graphical information.
	