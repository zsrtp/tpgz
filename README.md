# <img src="./res/icons/icon.jpg" height="42" width="45" align="top"/>tpgz</h1>

## About

tpgz is a rom hack of the game Twilight Princess geared towards enhancing practice and testing for speedrunning. 

<p align="center">
  <img src="./res/icons/giphy.gif?raw=true" />
</p>

FEATURES:

```
inventory menu:
- item wheel                    // can set the 24 item wheel slots to any item
- pause menu                    // can set pause menu items (not implemented yet)

cheat menu:
- invincible                    // link has no hurtbox, but can still take fall damage and drown
- invincible enemies            // all enemies have infinite health
- infinite hearts               // link always has maximum hearts
- infinite air                  // link can't drown
- infinite oil                  // link always has maximum lantern oil
- infinite bombs                // gives link 99 bombs in all bomb bags
- infinite rupees               // link will always have 1000 rupees
- infinite arrows               // gives link 99 arrows
- infinite slingshot pellets    // gives link 99 slingshot pellets
- moon jump                     // hold R+A to moon jump
- teleport                      // dpad+up to set, dpad+down to load 
- no sinking in sand            // link won't sink in sand
- area reload                   // use L+R+Start+A to reload current area
- fast movement                 // link's movement is much faster
- fast bonk recovery            // reduces bonk animation significantly
- super clawshot                // clawshot is long and can grab most things
- super spinner                 // spinner is very fast and can hover (not implemented yet)

warping menu:
- not implemented yet

memory menu:
- not implemented yet

practice menu:
- jump directly into a practice save (currently only any% saves exist)

tools menu:
- input viewer                  // show current inputs (buttons only for now)
- timer                         // frame timer - Z+A to start/stop, Z+B to reset
- roll check                    // frame counter for chaining rolls
- gorge void indicator          // use L + Z to warp to to kak gorge
- freeze actors                 // freezes actors
- hide actors                   // hides actors (except link/epona)
- disabled bg music             // disables background and enemy music
- disable sfx                   // disables item, weather, etc. sound effects
- freeze camera                 // locks the camera in place
- hide hud                      // hides the heads up display
- link tunic color              // changes link's tunic color

settings menu:
- log level                     // changes log level for debugging
- drop shadows                  // adds shadows to all font letters
- save card                     // save settings to memory card
- load card                     // load settings from memory card
- area reload behavior          // load area = reload last area, load file = reload last file
```

KNOWN BUGS:

```
- invicible enemies cheat can't be turned off once turned on
- super clawshot cheat is only partially functional
- disabled bg music tool may not always disable bg music
- loading practice files can crash in certain situations
```


PLANNED FEATURES:

```
- free cam
- actor spawner
- frame advance
- collision viewer
- menu font selector
- lag counter & loading counter
```

## Download / Usage

You will need the **Twilight Princess ISO** -- currently only the US version is supported.

1. Download the latest release [here](https://github.com/hallcristobal/tpgz/releases).

2. Unzip the contents into a folder and run the `romhack-patcher.exe`

3. Select the associated patch file and the Twilight Princess ISO

4. Click apply

    * You will be asked to select a save directory for the newly patched ISO. After giving the ISO a name, the patcher will freeze briefly while generating the ISO.

5. You can now load the generated ISO in Dolphin emulator or in a Wii in a homebrew loader such as [Nintendont](https://github.com/FIX94/Nintendont).

## Project structure
```
tpgz
├───.github
│   └───workflows         // github action(s) used to test code compilation
├───external              // external libraries and programs consumed by tpgz
│   ├───fonts             // small rust program to generate raw bytes and c code for utilizing true-type fonts in game
│   │   ├───fonts         // ttf files
│   │   └───src           // source code for fonts
│   ├───gcn_c             // game independent gamecube apis to link to
│   │   ├───include       // header files for gcn_c
│   │   └───src           // source code for gcn_c
│   └───libtp_c           // game bindings for twilight princess
│       ├───.github
│       │   └───workflows // github action(s) used to test code compilation
│       ├───include       // header files for libtp_c
│       └───src           // source code for libtp_c
├───include               // header files for tpgz
│   └───fonts             // individual font properties such as width, height, glyphs, etc.
├───res                   // external resources to be consumed
│   └───save_files        // raw quest log bytes to be injected at compile time
└───src                   // source code for tpgz
    └───fonts             // raw bytes for fonts
```

## Building
See [BUILDING](./BUILDING.md).

## Contributing
See [CONTRIBUTING](./CONTRIBUTING.md).