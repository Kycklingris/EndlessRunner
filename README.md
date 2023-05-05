# EndlessRunner
I wasn't entirely sure about what exactly was to be made, so it ended up being a horrible two lane subway surfers clone

## Bugs/Missing features
- There is no HUD.
- The right/bot side has the platforms slowly drift with larger holes between them.

## Bug fixes
- [Collisions](https://github.com/Kycklingris/EndlessRunner/commit/904b42fa065802e3f69ce0671d05bfb81fa3d595), the change that made a true difference was that I changed hitting a obstacle to use the hit event rather than started overlap. I did however also change the obstacles and I think at the time, the player to sweep rather than instantly move. That did however make it so that the player could get stuck in an obstacle having them all stack onto each other, as such it ended up being only the obstacles that sweep not the player.
- [Gaps between platforms](https://github.com/Kycklingris/EndlessRunner/commit/4757860841672a81c0733bbe2afe31bf52da3c3b), I changed it to store the last spawned platform and spawn the next using that instead of storing the current length of all combined platforms and spawning based on starting point + length.
- [Save Games](https://github.com/Kycklingris/EndlessRunner/commit/d742edfb404a3dae960c717f835c913645965568), I moved the loading/saving code to a more reusable location, and what fixed the problem I had, was making the highscores a UPROPERTY.

## New features
Now, I'm not sure if the new features should also be with a link to a diff, since it doesn't say that in the assignment but anyway. 
- A main menu, should have existed in the last version but wasn't done in time. It's just made using blueprints since doing UI in c++ when a fully functioning UI editor exists seems like it would overcomplicate things.
- Co-op was done with the "AI" player, in my case with what should be a 100% success rate. Spawning the platforms/obstacles for co-op is done somewhat badly as I just copied the spawning code to make it run twice [Spawning code](https://github.com/Kycklingris/EndlessRunner/commit/e2e0c02bc04b9ca1647d6cfa4f9e97df1419ea2d). 
- Moving the player to not be centered is unremarkable as it's just adding an offset based the location during beginplay. [Diff](https://github.com/Kycklingris/EndlessRunner/commit/e93135bf270cf5c6613b9770448b4a8a339e2274).
- The "AI" player is a inherited class from the player character that just has a trigger box sticking out, and when something enters it moves to the other path. I had previously moved health and score to a playerstate class, but since a non player character doesn't get a playerstate I had to move it back into the character script.
- The Obstacles getting destroyed when "dodging" obstacles was done by adding trigger boxes to the left and right side of the obstacle, which then using onbeginoverlap on the character calls a function on the gamemode to destroy a random obstacle on both "players" side. I did have to store all obstacle references in the gamemode to make it work, which isn't ideal as that means that when the obstacles go out of the designated area they have a call a function on the gamemode to remove itself. [Diff](https://github.com/Kycklingris/EndlessRunner/commit/1a0ed38044c9ffca7f25e1feadc5123d82dbd748).

## The rest
I did make sure that things were blueprint readable and the like as well, but other than that I don't think there were any more improvements [Diff](https://github.com/Kycklingris/EndlessRunner/commit/0670fb12464caa46c12e9b0c013e8deb38bc3363).
