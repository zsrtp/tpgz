# Overview

This is an overview of the **TPGZ** project from a development perspective. It will be separated by the following sections:

- [Folder Structure](#folder-structure)
- [Compilation Pipeline](#compilation-pipeline)
- [REL Support](#rel-support)
- [Main Components](#main-components)
  - [Main module](#main-module)
  - [Handlers](#handlers)
  - [Settings](#settings)
  - [Menus](#menus)
- [IDE setup](#ide-setup)
  - [Tasks](#tasks)
  - [Dev Container](#dev-container)

---

## Folder Structure

The repository structure is separated like so:

- `/.devcontainer`: Used to setup the dev container allowing a standardized development environment. More details in the section [*IDE Setup*](#ide-setup).
- `/.github/workflows`: Contains the configuration of the different workflows used to check the good quality of the code. This is not a folder you should usually need to interact with.
- `.vscode`: Contains the configuration files for **VSCode**. More details in the section [*IDE Setup*](#ide-setup).
- `bin`: Contains the executable binaries and scripts that are used by the compilation pipeline. More details in the section [*Compilation pipeline*](#compilation-pipeline).
- `build_...`: User created. Rquired in order to build the project. More details in *Compilation Pipeline* and [*IDE Setup*](#ide-setup).
- `cmake`: Contains **CMake** scripts used in the compilation pipeline to import libraries, tools, configurations, ..., from outside the project. More details in [*Compilation pipeline*](#compilation-pipeline).
- `common`: Contains the code samples that are reused between modules.
- `docs`: Contains useful documentation files.
- `external`: Contains libraries that the project links against, as well as scripts useful during development.
- `external/gcn_c`: Contains DolphinOS bindings that can be used to interface with the game's code.
- `external/libtp_c`: Contains bindings that are specific for Twilight Princess that can be used to interface with the game's code.
- `external/misc`: Contains scripts useful during development (for example, generating save files metadata, or converting an image/font into our custom file format).
- `isos`: User created. Contains the dump of each version of the game provided by the user. They must comply with the folling mapping depending on the version of the game:
  - `GCN_NTSCU` -> `GZ2E01.iso`
  - `GCN_PAL` -> `GZ2P01.iso`
  - `GCN_NTSCJ` -> `GZ2J01.iso`
  - `WII_NTSCU_10` -> `RZDE01.iso`
  - `WII_NTSCU_12` -> `RZDE01_2.iso`
  - `WII_PAL` -> `RZDP01.iso`
- `modules`: Each folder contains a module compiled independently and which produce a dynamically relocatable module (REL) which can be loaded and unloaded as needed. More details in the section [*REL Support*](#rel-support).
- `modules/boot`: This is the main module of the project. It is the first loaded, and is never removed. More details in the section [*Main module*](#main-module).
- `modules/init`: This module contains all the initialization code, which is all the code that is only ran when initially loading **TPGZ**, and then never ran again.
- `modules/features`: Contains the modules handling the various features of **TPGZ**.
- `modules/menus`: Contains the modules handling the various menus of **TPGZ**.
- `res`: Non-code resources used by **TPGZ**.
- `res/bin`: Binary data which is injected into the game.
- `res/fonts`: The fonts used to display text in **TPGZ**. They were made from TrueType fonts converted into a custom font format using the script found at `external/misc/font2fnt.py`.
- `res/icons`: The original pictures that were used to generate the textures in `res/tex`.
- `res/map`: The files that contain the mapping between the symbols name and their address in the game. They are used in the compilation pipeline to link the modules against the game.
- `res/save_files`: The files that contains the data to load into the questlog of the game, as well as some metadata on how to load them.
- `res/save_files_wii`: Wii specific save files. Although GC's questlog data and Wii's are intercompatible, Wii any% saves were made using a different route, requiring a different set of saves.
- `res/stage_info`: Metadata containing the information on where it is possible to warp.
- `res/tex`: The texture files which are used by **TPGZ**.
- `src`: Because the parcher we are using cannot handle to not inject a static library into the DOL of the game, we have to provide a minimal library that contains almost nothing. It will be fixed in the future.
- `patch.asm.in`: Template of a configuration file for the patcher that will be converted into `patch.asm` in the build folder after CMake replaces the required fileds. It will contain addresses to patch values into.
- `RomHack.toml.in`: Template of a configuration file for the patcher that will be converted into `RomHack.toml` in the build folder after CMake replaces the required fields. It will contain what files to inject into the game, as well as how to patch it.

---

## Compilation Pipeline

We will first review the big picture of how the Compilation Pipeline works before looking at how to use it.

### How it works

**TPGZ** uses **CMake** as a project configurator. This allows for the choice between two different generators: *Ninja* and *Makefile*.

// TODO

### How to use

Before we can compile the project, we need to configure the build folder for a specific **Platform** and **Region**.<br>
We first need to make a folder in the root of the repo which will contain all the generated files.

```sh
mkdir build
```

> If you use **VSCode**, it is recommended to name the build folder using the following mapping (based on the version of the game you build for):
>
> - `GCN_NTSCU` -> `build_gcn_ntscu`
> - `GCN_PAL` -> `build_gcn_pal`
> - `GCN_NTSCJ` -> `build_gcn_ntscj`
> - `WII_NTSCU_10` -> `build_wii_ntscu_10`
> - `WII_NTSCU_12` -> `build_wii_ntscu_12`
> - `WII_PAL` -> `build_wii_pal`
>
> This is to keep compatibility with **VSCode**'s tasks. More details in the section [IDE Setup](#ide-setup).

Once the build folder exists, go into it and configure the folder with the command:

```sh
cmake .. -DPLATFORM="<Platform>" -DREGION="<Region>" -N "<Generator>"
```

Where `<Platform>` is one of `GCN`, `WII`; `<Region>` is one of `NTSCU`, `NTSCJ`, `PAL` for the `GCN` platform, and one of `NTSCU_10`, `NTSCU_12`, `PAL` for the `WII` platform; `<Generator>` is one of `Ninja`, `Unix Makefiles`.

Once the build folder is configured, you can run `ninja` or `make` depending on the generator you chose to build the project.

There are special target that can be provided to the generator command to get either a patched ISO or a patch file.<br>
The available targets are:

- **`all`, or no target**: builds the all the modules and the dummy static library, and the build folder is ready to run the patcher in.
- **`iso`**: builds the project and generate a patched ISO.
- **`patch`**: builds the project and generate a patch file.

## REL Support

// TODO

### Main Components

// TODO

### Main module

// TODO

### Handlers

// TODO

### Settings

// TODO

### Menus

// TODO

## IDE setup

### Tasks

A few **VSCode** tasks are provided to ease the build process a little bit. The available tasks are:

- ***Setup***: Makes a build folder for the given version (if it doesn't exits), and configures it as a build folder for that version.
- ***Clean***: Removes all the generated files from the given build folder.
- ***Build***: Builds the project. It makes the build folder ready to be used with the patcher.
- ***Generate ISO***: Builds the project and generates a patched ISO. The built version's dump must be in the `isos` folder with the right name. See the section [Folder Structure](#folder-structure) for more details.
- ***Generate patch***: Builds the project and generates a patch file ready to distribute.
- ***Formatting***: Formats all the project's source files with the correct formatting.

### Dev Container

The folder `.devcontainer` contains configuration files that can be used by **VSCode**'s extention [**Remote Container**](https://code.visualstudio.com/docs/remote/containers) and with [***Docker***](https://www.docker.com/) installed on your system to make a development container that can provide a standardized environment that is guarentied to build the project.
