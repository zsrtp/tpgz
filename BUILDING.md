# Building

## Compiling

1.  Clone the repo with `git clone https://github.com/hallcristobal/tpgz.git`

3)  In the root `tpgz` folder, run:

    ```
    git submodule update --init --recursive
    ```

4)  Copy your NTSC-U Twilight Princess ISO to the root `tpgz` folder, then rename it to `gz2e01.iso`.

5)  Install devkitpro.

    - Windows: Download [here](https://github.com/devkitPro/installer/releases)
    - MacOS/Linux: Read [this guide](https://devkitpro.org/wiki/Getting_Started)

6)  Download [Romhack-Compiler](https://github.com/hallcristobal/romhack-compiler/releases).
    This is used to add our compiled code into the ISO.<br>
    _(It is recommended that you add romhack.exe to your PATH.)_

7)  Run `make` in the root `tpgz` folder to compile the code.

8)  Run `romhack build --raw` to create a new ISO with our changes applied.<br>
    The new ISO is located at `build/tpgz.iso`.

## Using Patches

Patch files are a convenient way to share your changes with others.

- To create a patch, run:

  ```
  romhack build --raw --patch
  ```

  The new patch file is located at `build/tpgz.patch`.

- To apply a patch, run:

  ```
  romhack apply <example.patch> <ntsc-u-input.iso> <output.iso>
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
