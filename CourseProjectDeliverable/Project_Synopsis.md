# Project Synopsis

## Issues/Concerns
* Room changing isn't implemented very well.
* Character ai falls short of what it should be.
* Collision detection is buggy.
* Game balancing isn't very good.
* Dungeon generation isn't as robust as it should be.
* Extendability of the project is difficult, due to dependency structure.
* Rolling was never implemented, it was supposed to be a core feature.

## Work Done

### Timesheets

Below is a compilation of hours worked on iterations and a total. Note that in here there are unrecorded hours for the time between iteration V and project submission.

|Iteration  |Roman Bureacov | Riley Hopper |Kyler McLees   |
|:---------:|:-------------:|:------------:|:-------------:|
|I          | 7h 35m        |     16h      | 7h            |
|II         | 14h 30m       |    6h 30m    | 9h            |
|III        | 16h 50m       |   22h 41m    | 8h 30m        |
|IV         | 8h 15m        |     13h      | 9h 20m        |
|V          | 4h            |     67h      | 37h 10mm      |
|TOTAL      | 51h 10m       |   125h 11m   | 71h           |

### Roman Bureacov

I develoepd the engine code, specifically `Bitz`, whose job is to take in events and process them so that characters may move around, attack, and interact with their environment.

### Riley Hopper
I worked on most of the backend, I'd say like 80-90% of the backend of the project, here are the classes I created:
 * Dungeon.
 * Room.
 * DataBase Manager.
 * NPC.
 * Player.
 * The Observer pattern.
 * Point struct.

These are all major parts of the backend, it was a lot of code, I also worked on these classes:
* View.
* Bitz.
* AbstractCharacter.
* Clock.
* Hibox.

I was the person that linked the messy backend together this was pretty awful to be honest. but I got it done, I created and worked on the test files:
* DungeonRoomTestFile.
* NPCTestFile.
* DataBaseTestFile.
* ObserverTestFile.
* EngineMovementTestFile.
* PlayerTestFile.

Other things that I did were:
* Create the sprite sheets.
* Create the presentation(Awful as it was).
* Clean up the build system.
* Create music(Sadly it didn't end up in the game).
* I also made the exe statically linking everything and posted it to itch.io.


### Kyler McLees

I developed the View, music, and helped to debug other files. I helped create the presentation slides, srs, and was at the group meetings.

# Closing Notes

## Roman Bureacov

What made this project particularly difficult is the lack of abstraction that Java typically has, and finding and learning a different library. I could only say I wish I dedicated more time on this project.

## Riley Hopper

This project was hell, C++ is one of the most, obtuse difficult, languages to work with. Just getting the build system to work was awful, not to mention the esoteric bugs that would just popup, like how am I suppose to debug a SEGFUALT when all the program tells me is what the assembly registers are up to. Its all awful, I poured hours into this project just look at my time sheet, using this project to learn C++ was the worst idea I ever thought, it was a mistake. Laying that on choosing to do GUI was a mistake, it was way too much work just to get one version of SDL in here it took us hours, Cmake is rough. I just feel like crap about it all, everyone else's project looked great and this one was work, and it isn't that good. I worked till there was nothing left in me and did more, this project has felt like an on coming car, and you just can't get out of the way. I am glad I have a way better understanding of this language, I can say I can make project in it now, but this was horrible. I loved your class Tom you're a great professor, you work hard for your students, and it shows, thankyou for helping us out, but if any of your students in the future want to do C++ try to stop them, warn them do what you can, this is a cautionary tale.

## Kyler McLees

This was my first project that had GUI, and SDL was certainly a choice. Especially SDL3, which is newer and had less
documentation. I think for the language we chose we absolutely needed to treat this as is if was a part-time job. By the time
we realized just how little we had it was nearly presentation time. I spent more time refactoring the view than I should have 
realistically put up with. Most of the project to me felt like a continuous loop of put in 3-5 hours into something just to find 
a simpler solution that would've taken 10 minutes. A lot of our time was meetings without significant progress, and division of 
labor was certainly unbalanced. By the time I realized that so much work had to be done, there was too much entangled classes
to pour through and still have the time to deliver. 

## Extra Credit
* Gui.
* Real Time Movement.
* The Use Of C++.
* Executable.
* Itch.IO download.
* 

Link: https://riley-hopper.itch.io/incarus