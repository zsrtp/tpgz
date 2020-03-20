# <img src="./res/icons/icon.jpg" height="42" width="45" align="top"/>tpgz</h1>

## About

tpgz is a rom hack of the game Twilight Princess geared towards enhancing practice and testing for speedrunning. 

<p align="center">
  <img src="./res/icons/giphy.gif?raw=true" />
</p>

The current build supports a wide variety of features including the following:

- RAM watch
- Dynamic cheat codes
- Warping menu
- Item and Equipment hacking menu
- Actor spawner (buggy currently)
- Custom font support
- Misc flag setting options
- Misc practice tools such as a timer, frame indicators for rolls, input viewer, etc.

More to come soon!

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