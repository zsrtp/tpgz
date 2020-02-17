# <img src="./res/icon.gif" height="100" width="100" align="top"/>tpgz</h1>

<p align="center">
  <img src="./res/giphy.gif?raw=true" />
</p>

## Usage

You will need the **Twilight Princess ISO** -- currently only the US version is supported.

1. Download the lastest release [here]().

2. Unzip the contents into a folder and run the `romhack-patcher.exe`

3. Select the associated patch file and the TP ISO

<p align="center">
  <img src="./res/select_patch.png" />
</p>

3. Click apply

    * You will be asked to select a save directory for the newly patched ISO. After giving the ISO a name, the patcher will freeze briefly while generating the ISO.

4. You can now load the generated ISO in Dolphin emulator or on Wii in a homebrew loader such as [Nintendont](https://github.com/FIX94/Nintendont).

## Compiling

1. Clone this repo and do a `git submodule update --init` to pull down the correct
TP Bindings.

2. Copy your copy of Twilight Princess (Currently only NTSC-U) to the root folder
for this project, and rename it to `gz2e01.iso`.

    - You can choose not copy or rename it if you would prefer, just make sure that the lines in
    Romhack.toml match the iso path.
    ```Toml
    ...
    [src]
    iso = "<iso-path/file-name>"
    ...
    ```
3. Install devkitpro
    - Windows: Download [here](https://github.com/devkitPro/installer/releases)
    - MacOS/Linux: Read [this guide](https://devkitpro.org/wiki/Getting_Started)

4. Download Romhack [here](). This will be used for adding the compiled source code into the ISO.

5. Browse to the directory where you cloned your code and run:
```
make
```

6. After the build succeeds, run:
```
romhack build --raw
```

7. The built ISO will now be in a build/ folder in the same directory as the source code.

## Contributing

If you'd like to contribute, please feel free to fork this repo and send in a pull request. We will at minimum require that your PR passes a simple compile check that will trigger when the PR is submitted.