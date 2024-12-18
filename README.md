# Pacman + Map Editor

<b>Requirements:</b> Windows or Linux Environment
<br>
<br>
<b>Quick Install:</b>
<br>
1. Download the latest <b><a href="https://github.com/JJDOESIT/pacman/releases/tag/v1.0.0">pacman.zip</a></b> release for Windows or Linux
3. Extract the files
4. Run pacman.exe
    * If permissions are denied, run ```chmod 700 <path to pacman.exe>``` and try running again



<b>Build Yourself:</b>
<br>
1. Clone the repo or download the source code in a Linux environment
2.  Install the requirements: ```sudo apt-get install libsfml-dev``` and ```sudo apt-get install build-essential```
3. Run the makefile in command shell or IDE terminal
    - Note: Neccesary changes to install location of SFML might be required in the makefile
    - Note: Reinstallation of <b><a href="https://github.com/Tencent/rapidjson">RapidJSON</a></b> in lib/ might be neccessary

# Features

- This project features a playable Pacman game, as well as a fleshed out map editor + config editor to make the experience more customizable.
   - Each ghost has two modes <b>(scatter and chase)</b>. While scattering, the ghosts will target a designated target tile. While chasing, each ghost will implement its own unique <b>AI algorithm</b> to chase Pacman.
        - <b>Blinky:</b> Targets Pacman directly
        - <b>Pinky:</b> Targets 4 tiles ahead of Pacman's current direction
        - <b>Inky:</b> Targets Pacman directly until he is within an 8-tile radius, then switch back to scatter mode
        - <b>Clyde:</b> Targets the vector that is twice the distance between Blinky's position and Pacman's position
- Using WASD, the player can move Pacman throughout the map\
   <img src="https://github.com/JJDOESIT/pacman/assets/138625553/357a207d-e6d3-4e00-b956-1b3fe970f55f" width="400">

- One can create, edit, customize, and delete maps using the tile editor
   - Note: The max size of a map is 99x99.
   - Note: There are three tiles without a texture.
        1. Non-passable wall
        2. Ghost gate (non-passable for Pacman)
        3. Empty space (passable for all)
   <img src="https://github.com/JJDOESIT/pacman/assets/138625553/4ca9f7ae-540e-4ad1-b539-6065b0c280df" width="300">
   <img src="https://github.com/JJDOESIT/pacman/assets/138625553/d2a8091a-00ad-4574-b2d5-3746af669e69" width="300">

- Collect power pellets to earn points and eat ghosts!\
   <img src="https://github.com/JJDOESIT/pacman/assets/138625553/31a07626-63d4-40bb-8937-c83a737f56e9" width="300">

- The config editor can be used to customize the difficulty and game settings
   - Note: The ghost's escape tiles are determined by the placement of the gates. When creating custom maps, it is necessary to assign each ghost to a gate. This can be a one-to-one or many-to-one relationship. The ghost's AI algorithm uses these gates to determine when they have entered or exited the den.
   <img src="https://github.com/JJDOESIT/pacman/assets/138625553/6dd7332d-951f-4a08-81e0-0878603a4176" width="300">
   <img src="https://github.com/JJDOESIT/pacman/assets/138625553/350f27b4-ebe7-4e31-8390-d347a9178262" width="300">

