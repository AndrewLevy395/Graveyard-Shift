Dan Duff's SAUCER SHOOT Variation
Dan Duff (dfduff@wpi.edu)
10/24/19

Saucer Shoot game from Dragonfly tutorial, with an added variation.
The game.cpp is the main class file, with Objects defined as (with respective header files):
-Saucers (Saucers.cpp - enemies to destroy)
-Hero (Hero.cpp - player-controlled unit)
-Stars (Star.cpp - background image)
-Reticle (Reticle.cpp - Shows mouse location)
-Bullets (Bullet.cpp - projectile that destroys saucers, fired by player's Hero)

With event and meta objects:
-GameOver(GameOver.cpp - Played when game ends)
-GameStart(GameStart.cpp - Played after Dragonfly splash screen)
-Explosion(Explosion.cpp - Shown after Saucer iteracts with a Bullet object)
-Nuke(Nuke.cpp - destroys all Saucers)

--------------------------------------------------------------------

(Loading the File into Visual Studio can be done by selecting the saucer-shoot.sln file in the vs-2019/ directory). 

To build (via Dragonfly Tutorial README):

0) Setup development environment for Windows, Linux or MacOS.
See http://dragonfly.wpi.edu/engine/index.html#setup for details.

1) Build, as appropriate for the platform (e.g., "make" on Linux or
Mac, F7 on Windows from Visual Studio).

2) Run game, as appropriate for the platform (e.g., "./game" on
Linux or Mac, F5 on Windows from Visual Studio)

--------------------------------------------------------------------

Directories:

sounds/ - contains the sound files used in Saucer shoot
sprites/ - contains the sprite files used in Saucer shoot
vs-2019/ - contains Visual Studio solution files (Microsoft Windows), as well as all additional source code outside of game.cpp

--------------------------------------------------------------------

