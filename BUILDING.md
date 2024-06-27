# Building

## Compiling

1.  Clone the repo locally.

```bash
git clone https://github.com/zsrtp/tpgz.git
```

2.  In the root `tpgz` folder, run:

```bash
git submodule update --init --recursive
```

3.  Copy your Twilight Princess ISO into the `isos` folder. You will need to rename the ISO based on which platform and region you're building for.

    | Game Version | ISO Name   |
    |--------------|------------|
    | Gamecube USA | GZ2E01.iso |
    | Gamecube PAL | GZ2P01.iso |
    | Gamecube JPN | GZ2J01.iso |
    | Wii USA 1.0  | RZDE01.iso |
    | Wii PAL      | RZDP01.iso |

4.  Install devkitpro.

    - Windows: Download [here](https://github.com/devkitPro/installer/releases)
    - MacOS/Linux: Read [this guide](https://devkitpro.org/wiki/Getting_Started)

5.  Download the latest [Romhack-Compiler](https://github.com/zsrtp/romhack-compiler/releases).
    
    - This is used to add our compiled code into the ISO.
    - It is recommended that you add romhack.exe to your PATH.
    - (For compiling the GameCube version, ensure you download the `-gc` version)

6. Create a `build` directory and navigate to it
    ```bash
    mkdir build
    cd build/
    ```

7. Configure CMake from the `build` directory
    ```bash
    #Example:
    cmake .. -D PLATFORM=GCN -D REGION=NTSCU
    ```

    - Supported values for PLATFORM are `GCN` and `WII`
    - Supported values for REGION are `NTSCU`, `NTSCU_10`, `NTSCJ` and `PAL`
    - If you don't set these, the default values of `GCN` and `NTSCU` will be assumed when building.

8.  Run `make` in the `build` directory to compile the code.

8.  Run `romhack build --raw` to create a new ISO with our changes applied.

    - The new ISO is located at `build/tpgz.iso`.

## Using Patches

Patch files are a convenient way to share your changes with others.

- To create a patch, run:

  ```
  romhack build --raw --patch
  ```

  The new patch file is located at `build/tpgz.patch`.

- To apply a patch, run:

  ```
  romhack apply <example.patch> <input.iso> <output.iso>
  ```

  Your patched ISO will be named \<output.iso>.

## Fonts

To compile alternative fonts:

1. Place your font in `external/fonts/fonts/`

2. Replace the following command in the Makefile:

   ```rust
   cargo run -I fonts/your_font.ttf -S 18.0 -N Your_Font_Name -O build
   ```

3. Run `make font`