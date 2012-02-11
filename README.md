#Introduction
CrafTuX is a test project using OpenGL and Qt4. You are in a 3D world with randomly generated cubes, and you can fall thanks to the physic engine.

#Building
##General
In order to compile CraftTuX, you must have Qt and OpenGL development librairies installed. An easy way to do this is to download the [QtSDK](http://qt.nokia.com/downloads/).
Then download the source and open CrafTuX.pro, in QtCreator for example. You just have to click on compile :)
##Linux
On Linux, you *may* have to include manually OpenGL librairies in the .pro file, such as

```Makefile
INCLUDEPATH += /usr/include/GL
LIBS += -L/usr/lib -lGL -lGLU
```

#Download
##Linux 64 bits
If you are on Linux, and 64 bits, there is a build for you at the [download section](https://github.com/Glycaa/CrafTuX/downloads).
You must have Qt librairies installed, since they are not provided in the zip.