# EndlessRunner
I wasn't entirely sure about what exactly was to be made, so it ended up being a horrible two lane subway surfers clone

## Bugs/Missing features
- There is no GUI, for highscores, main menu or health
- I am not entirely sure if highscores are saved as I didn't wanna stress about testing it before the deadline
- The collisions are **REAL** wonky, and currently don't know why, maybe just moving trigger boxes is wrong.
- There are sometimes tiny gaps between Platforms, not entirely sure why, but I have an idea for how to fix.

## The rest
I don't really know if I would personally say that I have used C++ effectively, mainly because it is being used as a scripting language and there ain't all that much to do effectively. But, the important parts of the code are all in the GameMode file, where the spawning is happening for both obstacles and platforms.

I am trying spawning in two different ways, as the platforms are all spawned and then also subsequently moved from the GameMode script, whilst the obstacles are spawned in the  GameMode script and then move themselves through tick. The main reason for moving the platforms in the GameMode script is to mitigate gaps between platforms using the fact that I know that all platforms have moved before I spawn a new one, which isn't really all that important for the obstacles.

There are a lot of parts that should be moved later on, such as an extra health field in the playercontroller that should either be moved to a playerstate or just use the inbuilt playerstate health. I am probably also gonna be moving the savegame code from the playercontroller to static methods in MySaveGame, also in said code there are some objects that should be destroyed instead of leaving them for the GC.

I should probably also make sure that all files are either in Private/ or directly in source/endlessrunner, since they are placed how they are only through me forgetting to click on private when creating new classes.

There should also be some comments added, but well, that can come with moving around the code.

I guess there is a tiny reusability aspect with platforms not being locked to any specific size instead being checked during runtime, but that might also be a bit slow for the few upsides.

I did also copy a method **GASP** for getting the length of an object between movingobstacle and myplatform, which I guess could be done through inheritance instead, but since there is currently so little overlap between the two it felt like it would overcomplicate things for only a tiny benifit.
