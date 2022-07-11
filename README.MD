

# Twilight Princess - Beta Quest
Inspired by The Legend of Zelda : Ocarina of Time Beta Quest, like him the goal of this mod is to randomize loading zones of the game

## Roadmap
|Name            |Description|Status|
|----------------|--------------|-------------------------------|
|Loading Room Randomizer|Loaded room's stage can be entirely random|✔️Implemented|
|Loading Stage Randomizer|Loaded stage can be entirely random|🔧In the works|
|Fix Soft-lock seed|Certains seed can make the game unwinnable|🔧Planned|

## Building
---
**Repository**

*You need to have git installed ([windows](https://git-scm.com/download/win))*

Open a CMD and navigate to where you want your code to be:
```
C:\>mkdir Code
C:\>cd Code
C:\Code>git clone https://github.com/Venodez/TP-BetaQuest.git
Cloning into REL
remote: Enumerating objects: 132, done.
remote: Counting objects: 100% (132/132), done.
remote: Compressing objects: 100% (87/87), done.
remote: Total 132 (delta 56), reused 98 (delta 29), pack-reused 0
Receiving objects: 100% (132/132), 1.24 MiB | 6.45 MiB/s, done.
Resolving deltas: 100% (56/56), done.
```
Download and upate libtp_rel
```
C:\Code>git submodule init
C:\Code>git submodule update --remote
```
Done.

**Dependencies**
  * DevkitPPC comes with [devkitPro](//github.com/devkitPro/installer/releases)
  * [Python3](//www.python.org/downloads) (should be added to PATH or you will likely need Makefile adjustments)
  * Optional: [Visual Studio Code](//code.visualstudio.com) with [GC Settings](//wiki.zeldatp.net/Dev:Visual_Studio_Code)

**Compiling**

*devkitPro comes with it
s own MSys2 shell, it is recommended to use it for compilation.

This is an example of how to build for the NTSC-U version of the Game
```
$ cd /c/Path/To/REL
$ make us
main.cpp
cxx.cpp
memory.cpp
patch.cpp
rel.cpp
tools.cpp
timer.cpp
console.cpp
restfpr_x.s
restgpr_x.s
linking ... Randomizer.us.elf
output ... Randomizer.us.rel
packing ... Randomizer.us.gci
```
The `Randomizer.us.gci` (other versions are: `jp` and `eu`) file is now containing our custom REL. Load it with the REL Loader cheat or a hacked save file that contains the loader, it can be found on the [rando](//rando.zeldatp.net) homepage.

---
This mod is powered by [libtp_rel](//github.com/zsrtp/libtp_rel) and licensed under [GPLv3](/LICENSE) | (C) [AECX](//github.com/AECX), [LunarSoap](//github.com/lunarsoap5), [Zephiles](//github.com/Zephiles)
