# Cube Wave

## Project image

<img width="1920" height="1080" alt="2026-09-22 16-43-51 GIF (1)" src="https://github.com/user-attachments/assets/94d26af7-481a-4183-8b32-5484105fb517" />

## Project description

This project is a C++ implementation of [Bees and Bombs](https://bsky.app/profile/beesandbombs.bsky.social)'s Cube Wave using raylib! Inspired by The Coding Train's video: [Coding Challenge 86: Cube Wave by Bees and Bombs](https://www.youtube.com/watch?v=H81Tdrmz2LA).

## Inspiration for this project

- Bees and Bombs [original Twitter/X post](https://x.com/beesandbombs/status/940639806522085376) (here is their [Bluesky account](https://bsky.app/profile/beesandbombs.bsky.social))
- [The Coding Train's video](https://www.youtube.com/watch?v=H81Tdrmz2LA)
- [The Coding Train's website's post](https://thecodingtrain.com/challenges/86-cube-wave-by-bees-and-bombs)

## Goals of this project

- ✅ Use/learn the basics of raylib's 3D capabilities
- ✅ Use CMake to create a standalone executable that will run Cube Wave
- ⚠️ Have a 2D GUI that tells the user about the controls of the program (manipulate the frequency of the wave, cube size, color pallets, etc.)

- ❌ EXTRA: Allow the user to click and drag to rotate the camera + have a camera reset button
    - ❌ Because the project is in orthographic view. Changing perspectives would "ruin" the visual design

## Download and install

### Windows

- Clone this repo **_or_** Download the file "cube-wave.exe" in this repo's root directory
- Run the file "cube-wave.exe"

#### Please Note:

- A console window may appear before and after the application runs. This is raylib's doing, I believe, and don't know if I can stop it from flashing a console window. Sorry, I know it looks weird.

### Mac

Try the [Windows](#windows) version. If it doesn't work, I'm unsure. Apologies.

### Linx

Try the [Windows](#windows) version. If it doesn't work, I'm unsure. Apologies.

## Controls

**Press the "ESC" key to exit the program**

## Project reflection

### General thoughts

I achieved the main goals of this project, save for a 2D GUI to tell the "player" the controls of the program. There are no controls other than quiting the program.

This project, as a whole, was fun. It was a good introduction to raylib's 3D functionality. Quick and simple.

### What I learned

- Raylib 3D mode
- Cube drawing
- Generating 3D vector positions
- Sometimes the simple way is the best way ([Occam's Razor](https://en.wikipedia.org/wiki/Occam%27s_razor))
- How to create my own map() function

### What I need more work on

- 3D (in general)
- Look for other learning resources (not ones I am currently using) when I get frustrated

### What I struggled with

- Generating 3D points based on a center point

### Improvements to this program

- Add a list of controls the player can show/hide
- Add controls to increase/decrease the speed at which the wave oscillates
- Add controls to increase/decrease the frequence of the wave
- Add controls to zoom the camera in/out
- Change colors, user set & color based on cube height
