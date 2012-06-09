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

##Recommendations
* Default seed 12345678 already offers a beautiful landscape
* You should not go in negatives coordinates, because destucking is buggy (F3 to se your coordinates)
* You should not put an high view distance, otherwise your graphic card will sweat :D
* At startup, let the game load a few chunks before mining for the first time

##Contributing
Any contribution, no matter the form or amount, is greatly appreciated. Feel free to make suggestions on the [forum](http://www.runicorbs.net/forums)!

##Changelog
###v0.0.6 (comming soon)
```
(basic multiplayer, saving)
```
###v0.0.5 (Jun 9 2012)
```
(project rename, many performance and code improvments, OBJ loader, charge, and many more)
+ Renamed project into "The Runic Orbs"
+ Fast functions for expansive math operations (cos, sin...)
+ Most windows are centered as they are displayed
+ New "TORCH" block which doesn't produce light yet
+ Basic light occlusion for blocks
+ World seed is now taken into account for chunk generation and is displayed with F3
+ Chunks are generated in separate threads (no FPS drop when exploring anymore)
+ Great speed improvment by computing chunk geometry in another thread
+ Basic log system (not in a file yet)
+ New OBJ (Wavefront) 3D models loader and renderer
+ Cube blocks can have a multiple faced textures
+ Added a GRASS layer in terrain generation
+ Inventories now have a charge, and the player can see it thanks to a charge bar at screen
+ Official website is displayed in a frame in the Home dialog, along with a link.
+ Console in the server widget, which displays server log
+ Closing the game window brings you back to the home menu
+ Added credits tab in option dialog
+ Window size at startup can be configured in options
+ Seed can be a string, which is then converted to an integer in options
* You can't place a block where there is already on placed
* Chunk are generated and rendered only when in the view distanre (no useless chunk generation anymore)
* Player spawns randomly in positives (and thus not buggy) chunks
* Reduced chunk size from 24 to 20 for speed
* Changed "bilinear" texture filtering by "mipmaps" and made it default
* Tweaked some GUIs
* Fixed bug of inaccessible blocks in negative chunks
* Walk velocity is not direction dependant anymore
* You can't jump trought blocks anymore
* Reduced jump force
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
