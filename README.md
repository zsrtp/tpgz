## tpgz - The Twilight Princess Practice ROM

<p align="center">
  <img src="./res/giphy.gif?raw=true" />
</p>

## Usage

You will need to Twilight Princess ISO; Currently only the US version is supported.

Download the lastest release [here]()

Unzip the contents into a folder and run the `romhack-patcher.exe`

1. Select the associated patch file

2. Select the TP ISO

3. Click Apply

- You will be asked to select a save directory for the newly patched ISO

After giving the ISO a name, the patcher will freeze briefly while generating the ISO.

You can now load the generated ISO in Dolphin or a homebrew loader such as [Nintendont]()

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