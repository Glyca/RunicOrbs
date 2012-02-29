#Introduction
CrafTuX is a test project using OpenGL and Qt4. You are in a 3D world with randomly generated cubes, and you can fall thanks to the physic engine.

#Download
##Linux 64 bits
If you are on Linux, and 64 bits, there is a build for you at the [download section](https://github.com/Glycaa/CrafTuX/downloads).
You must have Qt librairies installed, since they are not provided in the zip.

#Building
In order to compile CraftTuX, you must have Qt and OpenGL development librairies installed. An easy way to do this is to download the [QtSDK](http://qt.nokia.com/downloads/).
Then download the source and open `CrafTuX.pro`, in QtCreator for example. You just have to click on compile :)

#Changelog
##v0.0.2 (Feb 29 2012)
```
(almost recoded from scratch with things removed)
[ADD] A whole new architecture created
[ADD] Got a reliable overpainting method working
[ADD] Camera is reliable, and now works without Quaternions
[ADD] You can walk in two directions (ex. FORWARD-LEFT)
[FIX] You can't fall into blocks anymore
[FIX] Simplified world generator a lot
[FIX] Code and debug warnings cleanup
```
##v0.0.1 (Feb 5 2012)
```
(very first version)
[ADD] Cuurent FPS are displayed in window title
[ADD] You fall thanks to the gravity
[ADD] Physic engine with forces, velocity, acceleration and fluid fiction
[ADD] Randomly generated cubes are drawn
```