#Introduction
CrafTuX is a test project using OpenGL and Qt4. You are in a 3D world with randomly generated cubes, and you can fall thanks to the physic engine.

#Download
##Linux 64 bits
If you are on Linux, and 64 bits, there is a build for you at the [download section](https://github.com/Glycaa/CrafTuX/downloads).
You must have Qt librairies installed, since they are not provided in the zip.

#Building
In order to compile CraftTuX, you must have Qt and OpenGL development librairies installed. An easy way to do this is to download the [QtSDK](http://qt.nokia.com/downloads/).
Then download the source and open `CrafTuX.pro`, in QtCreator for example. You just have to click on compile :)

#Contributing
Any contribution, no matter the form or amount, is greatly appreciated. Feel free to make suggestions!

#Changelog
##v0.0.4 (not released yet)
```
[ADD] Textures
```
##v0.0.3 (March 7 2012)
```
(the biggest step forward for the moment)
[ADD] Jump
[ADD] New drawing method using VBOs. (decreases CPU usage by 90% for just a few chunks)
[ADD] Blocks now have colors
[ADD] New terrain generation method (experimental, using Perlin noise)
[ADD] Chunks are now loaded at a good distance from the player, avoiding him to await the generation
[ADD] The game can be paused and resumed properly
[ADD] Game have a persistent, customizable configuration for FPS (and almost the seed)
[ADD] Lighting. Shapes are more visible
[ADD] Collisions. You cant't go throught blocks anymore
[FIX] Compilable on Windows since OpenGL 1.5 and higher functions are loaded
```
##v0.0.2 (Feb 29 2012)
```
(almost recoded from scratch with things removed)
[ADD] A whole new architecture created
[ADD] Got a reliable overpainting method working
[ADD] Camera is reliable, and now works without Quaternions
[ADD] You can walk in two directions (ex. FORWARD-LEFT)
[ADD] You can't fall into blocks anymore
[FIX] Simplified world generator a lot
[FIX] Code and debug warnings cleanup
```
##v0.0.1 (Feb 5 2012)
```
(very first version)
[ADD] Current FPS are displayed in window title
[ADD] You fall thanks to the gravity
[ADD] Physic engine with forces, velocity, acceleration and fluid fiction
[ADD] Randomly generated cubes are drawn
```
