#Welcome to the world of The Runic Orbs!
**The Runic Orbs** is a funny sandbox indie adventure game using C++, OpenGL and Qt4. It was originally created by [Glyca](https://github.com/Glyca/RunicOrbs).  
* **[Official website](http://www.runicorbs.net)**
* [Let's talk about it on the forums](http://www.runicorbs.net/forums)
* [Look at the wiki](https://github.com/Glyca/RunicOrbs/wiki)
* [View or create an issue](https://github.com/Glyca/RunicOrbs/issues)
* [You think it deserves a donation?](http://www.runicorbs.net/donate/)

##Downloads
Check for builds at the [download section](https://github.com/Glyca/RunicOrbs/downloads).
You must have Qt libraries installed (or in DLLs next to the executable for Windows), since they are not provided in the zip.

##Contributing
Any contribution, no matter the form or amount, is greatly appreciated. Feel free to make suggestions on the [forum](http://www.runicorbs.net/forums)!

##Changelog
###v0.0.5 (not released yet)
```

```
###v0.0.4 (April 1 2012)
```
(not an April fool!)
[ADD] Configurable view distance
[ADD] French translation
[ADD] Textures
[ADD] Configurable texture filtering
[ADD] Reticule for better picking
[ADD] A beginning of event system (client to server and vice versa)
[ADD] Block destruction
[ADD] Block placement
[ADD] Smooth shading and anti-aliasing are now configurable
[ADD] Only visible faces are rendered (huge speed increase)
[ADD] Basic inventory system of 8 slots
[ADD] Started creation of server join/host guis
[FIX] Decreased chunk size a little bit (will be increased later)
[FIX] Camera is now at eye level and not at feet level
[FIX] Default key map is better for french
[FIX] Jump and walking are not FPS dependant anymore
[FIX] You are not stuck when you fall at low FPS thanks to destucking
[FIX] Removed useless lighting system until a real implementation
[BUG] At the boundary between negative chunks, there is some ghost blocks (unbreakable, breaks physic...)
```
###v0.0.3 (March 7 2012)
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
[ADD] Collisions. You can't go through blocks anymore
[FIX] Compilable on Windows since OpenGL 1.5 and higher functions are loaded
```
###v0.0.2 (Feb 29 2012)
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
###v0.0.1 (Feb 5 2012)
```
(very first version)
[ADD] Current FPS are displayed in window title
[ADD] You fall thanks to the gravity
[ADD] Physic engine with forces, velocity, acceleration and fluid fiction
[ADD] Randomly generated cubes are drawn
```
