# Unit51
#### A simple first person shooter game made using unreal engine 4 in C++. 
 
#### Assets used to make the game are:
 - Starter content included with every project.
 - Military Weapons silver by Adia Entertainment

The game has 2 difficulty options. When hard difficulty is chosen the enemy spawns more projectiles. 

The enemies' movement is based on a sin function. There are other ways to implement the same behaviour like using lerp. Tick event is used to change position according to the sin function every frame.

FTimerHandle is used for delay to make player weapon and enemies shoot projectiles continuously.  
