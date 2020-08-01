## Compiling

1. Clone this repo and do a `git submodule update --init --recursive` to pull down the correct
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

4. Download Romhack [here](https://github.com/hallcristobal/Romhack-C). This will be used for adding the compiled source code into the ISO.

5. Browse to the directory where you cloned your code and run:
```
make
```

6. After the build succeeds, run:
```
romhack build --raw
```

7. The built ISO will now be in a build/ folder in the same directory as the source code.

8. If you want to compile alternative fonts, place your font in external/fonts/fonts/ and replace the following command in the Makefile:

```rust
cargo run -I fonts/your_font.ttf -S 18.0 -N Your_Font_Name -O build
```

Then run *make*
