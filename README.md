In The Gauntlet, a modern spin on the classic Asteroids game, you pilot a ship
through a perilous asteroid belt dodging and destroying asteroids and leaving
carnage and dust in your wake. Your goal is to reach the stargate on the other
side of the asteroid belt as quickly as you can while destroying as many
asteroids as possible. To protect you, your ship is equipped with energy
shields to withstand a few direct asteroid collisions as well as main and
secondary weapons to carve a path to victory. Don’t take too long to reach the
stargate though, it can only be held open for a short time so take advantage of
your ship’s thrusters to speed to the end.
Our entire game was written in C++ with OpenGL as our graphics library. As part
of our game project we developed our own general purpose Game Engine library.

Watch a demo here:

https://youtu.be/wViLcO2UIc8


Noteworthy Features:
- General Purpose Game Engine: We approached our game implementation by first 
creating a general purpose 3D game engine and then extending that engine to 
create our game. The game engine can be re-used for later games and supports 
many of the features listed here.
- Virtual Reality: Our game engine fully supports virtual reality game play out 
of the box using stereo graphics.
- Skybox: Our game engine supports the use of a skybox to create a textured 
environment and we used this feature in our game.
- Procedurally Generated Objects: The asteroids in our game are procedurally 
generated at runtime using a home-grown fractal algorithm that iteratively
subdivides and applies noise to a cube.
- Collision Detection: We used bounding spheres and a collision grid algorithm 
to detect collisions within the game map, this also improved our game’s efficiency.
- Health System: A generic health and damage system was implemented and used 
for the ship and asteroids. Asteroids that reach zero health will explode and 
spawn smaller asteroids. A ship with low health will sound a danger alarm and a
ship that reaches zero health will explode and trigger a game over event.
- Character Environment Interaction: Asteroids can be destroyed by the player 
and the player’s ship can be destroyed by the asteroids. Asteroids that collide
with each other will be deflected according to laws of motion. There is also a
stargate that the player reaches and goes through to win the game.
- Items: Depending on the difficulty level, several health packets are spawned 
in the map to recharge a ship that is low on health.
- Sound: Music and sound effects are used extensively throughout the game. As 
the player pilots the spacecraft, the engine's sound effect changes pitch and
volume to mimic a real engine. The volume of the sound emanating from the
stargate is dependent upon the player's distance from it.
- Difficulty Levels: There are 3 difficulty levels in our game -- easy, medium,
and hard. With increasing difficulty comes more asteroids and fewer health items.
- Score: We implemented a score system in our game that is dependent upon the
number of asteroids hit, the number of times the player runs into asteroids,
and the number of health items the player collects.
- Timer: There is a timer that the player has to beat or else they will lose.
As the time approaches zero, the background music increases tempo and pitch to
give a sense of urgency.
- HUD: We implemented a heads up display that included a health bar, a recharge
bar for secondary weapons, a timer, the score, and crosshairs for aiming.
- Multiple Ship Choices: We also included multiple ships that the player could
choose from, each with unique attributes and weapons.
- Weapons and Projectiles: All ships have both a primary weapon, and some have
a secondary weapon, that shoot self-illuminating projectiles. Each weapon has
unique recharge rates, projectile velocities, damage it can deal, sound effects,
and sprites.
- Animated Textures: Several of our textures were animated to create explosions,
force fields, projectiles, and HUD elements.
- Full Screen Mode: Our game supports full screen mode or windowed mode.
- Billboarding: We used billboarding to create animated textures including 
explosions, force fields, and rocket thrusters.
- Physically Based Motion: Asteroids use newtonian mechanics to simulate their
movement in space including basic collisions and rebound.
- Intuitive Controls: The player controls the ship using the keyboard keys WASD
for movement and Spacebar for boosting. Aiming and firing primary and secondary
weapons is controlled through mouse movement and left and right clicking.
- Unique Co-op Experience: A co-op game can be played when one player controls
the ship's movement with the keyboard and another player controls the aiming and
shooting with the mouse. Players must coordinate verbally to be effective. Since
the game is already highly intense for a single player, this mode generates a
great deal of excitement for the team as they yell commands to each other in the
same manner as a real flight crew.
- Engaging Gameplay: Gameplay was extensively tested to ensure balance and 
to players. The game provides an average of 30 seconds of intense gameplay
which is just enough to hook the player and make them want to play again. A
sense of urgency is inspired due to several game mechanics such as fast-paced
background music that intensifies as time runs low, the fact that the ship is
constantly moving forward, and a time limit which cannot be beat unless the
player uses boost. Since score is based on the quantity of asteroids destroyed
and the score is boldly displayed both during play and at game over, the player
is encouraged to shoot as many asteroids as possible instead of simply racing
to the finish.