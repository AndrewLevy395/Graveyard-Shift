Graveyard Shift Alpha
Dan Duff (dfduff@wpi.edu)
Andrew Levy (amlevy@wpi.edu)
12/7/19

--------------------------------------------------------------------

(Loading the File into Visual Studio can be done by selecting the graveyard.sln file in the vs-2019/ directory). 

To build (via Tutorial README):

0) Setup development environment for Windows, Linux or MacOS.
See http://dragonfly.wpi.edu/engine/index.html#setup for details.

1) Build, as appropriate for the platform (e.g., "make" on Linux or
Mac, F7 on Windows from Visual Studio).

2) Run game, as appropriate for the platform (e.g., "./game" on
Linux or Mac, F5 on Windows from Visual Studio)

3) Play game with WASD and left click to shoot. Defeat all enemies and the final boss to win.
--------------------------------------------------------------------

The game.cpp is the main class file, with Objects defined as (with respective header files):
-Zombies (Zombies.cpp - enemies to destroy)
-Boss (Boss.cpp - final enemy)
-Hero (Hero.cpp - player-controlled unit)
-Tombstone (Tombstone.cpp - randomly generated terrain objects)
-Large Tombstone (LargeTombstone.cpp - large terrain object)
-Reticle (Reticle.cpp - Shows mouse location)
-Bullets (Bullet.cpp - projectile that destroys saucers, fired by player's Hero)

With event and meta objects:
-GameOver(GameOver.cpp - Played when game ends)
-GameStart(GameStart.cpp - Played after Dragonfly splash screen)
-Revolver(Revolver.cpp - Increaesed shooting speed)
-SpeedItem(SpeedItem.cpp - Randomly drops, increases player speed)
-DataMAnager(DataMAnager.cpp - Holds overall data that classes may need to draw from - singleton)

--------------------------------------------------------------------

Directories:

sounds/ - contains the sound files used in Graveyard Shift
sprites/ - contains the sprite files used in Graveyard Shift
vs-2019/ - contains Visual Studio solution files (Microsoft Windows), as well as all additional source code outside of game.cpp

--------------------------------------------------------------------

