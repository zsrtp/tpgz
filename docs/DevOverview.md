# Overview

This is an overview of the **TPGZ** project from a development perspective. It will be separated by the following sections:

- [Folder Structure](#folder-structure)
- [Compilation Pipeline](#compilation-pipeline)
  - [How it works](#how-it-works)
  - [How to use](#how-to-use)
- [REL Support](#rel-support)
  - [REL Code Examples](#rel-code-examples)
- [Main Components](#main-components)
  - [Main module](#main-module)
  - [Listeners](#listeners)
  - [Menus](#menus)
- [IDE setup](#ide-setup)
  - [Tasks](#tasks)
  - [Dev Container](#dev-container)

---

## Folder Structure

The repository structure is separated like so:

- `/.devcontainer/`: Used to setup the dev container allowing a standardized development environment. More details in the section [*IDE Setup*](#ide-setup).
- `/.github/workflows/`: Contains the configuration of the different workflows used to check the good quality of the code. This is not a folder you should usually need to interact with.
- `/.vscode/`: Contains the configuration files for **VSCode**. More details in the section [*IDE Setup*](#ide-setup).
- `/bin/`: Contains the executable binaries and scripts that are used by the compilation pipeline. More details in the section [*Compilation pipeline*](#compilation-pipeline).
- `/build_.../`: **User created**. Rquired in order to build the project. More details in [*Compilation Pipeline*](#compilation-pipeline) and [*IDE Setup*](#ide-setup).
- `/cmake/`: Contains **CMake** scripts used in the compilation pipeline to import libraries, tools, configurations, ..., from outside the project. More details in [*Compilation pipeline*](#compilation-pipeline).
- `/common/`: Contains the code samples that are reused between modules.
- `/docs/`: Contains useful documentation files.
- `/external/`: Contains libraries that the project links against, as well as scripts useful during development.
- `/external/gcn_c/`: Contains DolphinOS bindings that can be used to interface with the game's code.
- `/external/libtp_c/`: Contains bindings that are specific for Twilight Princess that can be used to interface with the game's code.
- `/external/misc/`: Contains scripts useful during development (for example, generating save files metadata, or converting an image/font into our custom file format).
- `/isos/`: **User created**. Contains the dump of each version of the game provided by the user. They must comply with the folling mapping depending on the version of the game:
  - `GCN_NTSCU` -> `GZ2E01.iso`
  - `GCN_PAL` -> `GZ2P01.iso`
  - `GCN_NTSCJ` -> `GZ2J01.iso`
  - `WII_NTSCU_10` -> `RZDE01.iso`
  - `WII_NTSCU_12` -> `RZDE01_2.iso`
  - `WII_NTSCJ` -> `RZDJ01.iso`
  - `WII_PAL` -> `RZDP01.iso`
- `/modules/`: Each folder contains a module compiled independently and which produce a dynamically relocatable module (REL) which can be loaded and unloaded as needed. More details in the section [*REL Support*](#rel-support).
- `/modules/boot/`: This is the main module of the project. It is the first loaded, and is never removed. More details in the section [*Main module*](#main-module).
- `/modules/init/`: This module contains all the initialization code, which is all the code that is only ran when initially loading **TPGZ**, and then never ran again.
- `/modules/features/`: Contains the modules handling the various features of **TPGZ**.
- `/modules/menus/`: Contains the modules handling the various menus of **TPGZ**.
- `/res/`: Non-code resources used by **TPGZ**.
- `/res/bin/`: Binary data which is injected into the game.
- `/res/fonts/`: The fonts used to display text in **TPGZ**. They were made from TrueType fonts converted into a custom font format using the script found at `external/misc/font2fnt.py`.
- `/res/icons/`: The original pictures that were used to generate the textures in `res/tex`.
- `/res/map/`: The files that contain the mapping between the symbols name and their address in the game. They are used in the compilation pipeline to link the modules against the game.
- `/res/proc_info/`: Metadata containing information on friendly name mappings for Proc IDs. Used by the actor list menu.
- `/res/save_files/`: The files that contains the data to load into the questlog of the game, as well as some metadata on how to load them.
- `/res/save_files_wii/`: Wii specific save files. Although GC's questlog data and Wii's are intercompatible, Wii any% saves were made using a different route, requiring a different set of saves.
- `/res/stage_info/`: Metadata containing the information on where it is possible to warp.
- `/res/tex/`: The texture files which are used by **TPGZ**.
- `/src/`: Because the parcher we are using cannot handle to not inject a static library into the DOL of the game, we have to provide a minimal library that contains almost nothing. It will be fixed in the future.
- `/patch.asm.in`: Template of a configuration file for the patcher that will be converted into `patch.asm` in the build folder after CMake replaces the required fileds. It will contain addresses to patch values into.
- `/RomHack.toml.in`: Template of a configuration file for the patcher that will be converted into `RomHack.toml` in the build folder after CMake replaces the required fields. It will contain what files to inject into the game, as well as how to patch it.

---

## Compilation Pipeline

We will first review the big picture of how the Compilation Pipeline works before looking at how to use it.

### How it works

**TPGZ** uses **CMake** as a project configurator. This allows for the choice between two different generators: *Ninja* and *Makefile*.

The first step of the pipeline is to import all the external libraries and cmake configuration files for the required tools. Based on the values of `PLATFORM` and `REGION` provided when configuring the build folder, cmake imports the data from the corresponding script under `cmake/`.<br>
We also import the various executables needed during compilation. For instance, we import the toolchain file `cmake/CheckDevkitPro.cmake` which defines how to compile the code into ELF and static libraries. This takes care of the compilation part of the pipeline.<br>
We also import scripts like `bin/elf2rel` (from the repo [**spm-rel-loader**](https://github.com/SeekyCt/spm-rel-loader/releases/tag/elf2rel-13-6-2022)) and `bin/relmapper.py` (from [**TP Rando**](https://github.com/lunarsoap5/Randomizer/tree/master/GameCube)) which are used to link the generated ELF files against the game and between themselves to produce REL modules.<br>
- `relmapper.py` takes in the compiled ELF modules and extract the address/offset mapping of the symbols into a list of those mappings (`.lst` file), which is then used to link other ELF modules against that module.<br>
- `elf2rel` takes an ELF module and a `.lst` mapping file and links the module against the file to produce a REL module.

The next step is to configure the files used by the patcher. There are two of them: `RomHack.toml` and `patch.asm`.

- `RomHack.toml` is the main configuration file used by the patcher to know what file to inject, and in which place; How to inject the main code; What file contains the assembly patching instructions; And some metadata about the project structure.
- `patch.asm` is a file referenced by `RomHack.toml` which contains a sequence of assembly patches. The main one is the bootloader, and three minor bug fixes to improve stability and enable debug features.

Once the patcher configuration files are setup, we start to setup the dummy library and all the modules to be compiled and build the dependency tree between all of them. This enables **CMake** to know which files to rebuild when some file has been touched.<br>
We also add two custom targets to build a patched ISO, as well as one to build a patch file. See the section [How to use](#how-to-use) for more details.

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
> - `WII_NTSCJ` -> `build_wii_ntscj`
> - `WII_PAL` -> `build_wii_pal`
>
> This is to keep compatibility with **VSCode**'s tasks. More details in the section [IDE Setup](#ide-setup).

Once the build folder exists, go into it and configure the folder with the command:

```sh
cmake .. -DPLATFORM="<Platform>" -DREGION="<Region>" -N "<Generator>"
```

Where `<Platform>` is one of `GCN`, `WII`; `<Region>` is one of `NTSCU`, `NTSCJ`, `PAL` for the `GCN` platform, and one of `NTSCU_10`, `NTSCU_12`, `NTSCJ`, `PAL` for the `WII` platform; `<Generator>` is one of `Ninja` or `Unix Makefiles`.

> If you're using **VSCode**, you can instead run the *Setup* task. But it is not required, as any other build task will call the *Setup* task before.

Once the build folder is configured, you can run `ninja` or `make` depending on the generator you chose to build the project.

There are special target that can be provided to the generator command to get either a patched ISO or a patch file.<br>
The available targets are:

- **`all`, or no target**: builds the all the modules and the dummy static library, and the build folder is ready to run the patcher in.
- **`iso`**: builds the project and generate a patched ISO.
- **`patch`**: builds the project and generate a patch file.

## REL Support

**TPGZ** supports dynamically loading and unloading relocatable modules (REL). A REL module is a binary file that contains executable code, as well as data on how to link the module against other modules already loaded.<br>
There are two ways to load a REL module: Normally, or Fixed.

- The normal way will allocate space for both the code, and the uninitialized data (BSS area), and also some space for the relocation data. We then call `OSLink` on the data to apply the relocations using the relocation data from already loaded modules. This replaces the correct address of each symbol from outside of the module in the right place. We then keep the relocation data in place for the next modules that will get loaded.
  > If a REL references something that isn't currently linked, the addresses to those references will be set to `0x00000000`. However, the assembly that get that address would be modified after the appropriate REL gets linked, and the cache for the entire text section of the rel  with the modified assembly would be cleared.

- The fixed way will first allocate space for the code and the relocation data. Then we call `OSLinkFixed` to link against the already loaded modules and the game's DOL. Then, we resize the allocated data to free the part that held the relocation data (excepted the part that holds the relocation against other RELs) and let it be repurposed. The BSS area is allocated and initialized after that.

### REL Code Examples

To extract code into a separate module, we first have to make a folder under the `modules` directory. It must contain the following hierarchy structure:

```
+-+ modules/example/
  +-+ include/
  | +-+ main.h
  +-+ src/
  | +-+ main.cpp
  +-+ CMakeLists.txt
```

> The file `CMakeFiles.txt` is identical for all modules.

Here is the basic file content for a module:

```c++
// main.h
#pragma once

namespace tpgz::modules {
/**
 * @brief This function will be called once, right after
 *        the module has been loaded and linked.
 */
void main();
/**
 * @brief This function will be called once, right before
 *        the module will be unlinked and unloaded.
 */
void exit();
}  // namespace tpgz::modules
```

```c++
// main.cpp
#include <main.h>

namespace tpgz::modules {
void main() {}
void exit() {}
}  // namespace tpgz::modules
```

> The function `main` will be run right after loading the module, and `exit` will be right before unloading. They are a good place to setup your module.<br>
> Once compiled, the module will be available to load under the path `/tpgz/rels/...` (here it would be under `/tpgz/rels/example.rel`).

**TPGZ** provides a class to handle loading and unloading modules.

```c++
#include <utils/rels.h>

// ...

auto* example = new tpgz::dyn::GZModule("/tpgz/rels/example.rel");
// When loading the module, we also call its `main()` function.
example->loadFixed(/* negativeAlignment = */ true);

// When we don't need the module anymore, we unload it.
// Before unloading a module, its `exit()` method is automatically called.
example->close(); // This line is optional if you delete the GZModule object.
                  // But we keep it here for demonstration purposes.
delete example;
```

> You will typically load RELs from the main module (see [Main Module](#main-module) for more details), although it is possible to load a module from an other module.

## Main Components

Here, we list how some of the main components of **TPGZ** work.

### Main Module

**TPGZ** loads into the game using a bootloader that is patched into the game statically. This bootloader launches the `boot` module, which stays loaded for as long as the console is on. This module has many purposes:

- Hooking into the game's code.
- Holding global data that is access by all the sub modules.
- Providing [Lsiteners](#Listeners) for sub modules to hook into. 
- Handling REL modules loading.

> Currently, the main module also contains the majority of the code for the features. But in the long term, all the features that are not required to be in the main module will be extracted into sub modules.

When sub modules reference a symbol (static variable/function) from the main module, the symbol might need to be forced to not be "optimised away" by the linker, which may be the case when the symbol is only used in sub modules without ever being referenced in the main module. To that end, there are preprocessor macros defined in `common/rels/include/defines.h` (`KEEP_VAR` and `KEEP_FUNC`) which can be used to tell the linker to keep the symbol in the final binary.

### Listeners

A listener is an object which stores callback functions which get called at specific events. Existing listener are:

- **DrawListener**: This listener calls its callbacks when the `draw` hook is called.
- **PreLoopListener**: This listener calls its callbacks right before the game loop starts it next iteration.
- **PostLoopListener**: This listener calls its callbacks right after the game loop finishes its current iteration.

#### Listener examples

```c++
// This is an example for using a listener
#include "font.h"
#include "events/draw_listener.h"

// This is a function we want to run in the drawing thread.
void renderMe() {
    GZ_drawText("This text will be rendered in green", 50.f, 50.f,
                /* color = */ 0x00FF00FF, /* shadow = */ true);
}

// ...

// We can register a function to be called in the draw thread in this way.
g_drawListener.addListener(renderMe);

// If we want to stop the function from being called, we can remove it.
g_drawListener.removeListener(renderMe);
```

```c++
// This is an example for how to define a handler

// example_listener.h
#include "events/listener_base.h"

typedef void (ExampleCallback_t)(void*, float);

typedef events::ListenerBase<ExampleCallback_t> ExampleListener;

ExampleListener g_exampleListener;


// somewhere_else.cpp
#include "example_listener.h"
#include "controller.h"

void called_when_pressing_A(void* ptr, float x);

// ...

// We can register a function to call back when we need to.
g_exampleListener.addListener(called_when_pressing_A);

// ...

void called_every_gameloop() {
    // Some data we want to pass to the callbacks
    void* ptr = ...;
    float x = ...;

    if (GZ_getButtonStatus() == CButton::A) {
        // Here, we will call all the registered functions.
        g_exampleListener.dispatchAll(ptr, x);
    }
}

void called_when_pressing_A(void* ptr, float x) {
    // Do something...
}
```

### Menus

All the menus in **TPGZ** are dynamically loaded. They have their own folder `/modules/menus/` where they are defined. Every menu is setup on the premise that they will be loaded and handled by the **Menu Manager** (`MenuMgr`).<br>
The **Menu Manager** handles the loading and unloading of the menus, as well as which menu to display. Every time we open a sub menu, the current menu is unloaded, but its **State** is kept on a stack. When we leave a sub menu, we pop its **State** from the stack and load the previous one.<br>
A **Menu State** is constituted of a menu ID, a pointer to some data we want to keep between loads (as long as the state is on the stack), and some callbacks for specific events.

The callbacks that are kept in the state are called *Lifecycle hooks*.

- `createHook`: This callback is run when we load the menu for the first time. It's a good place to initialize the persistent data you want to keep between loads.
- `loadHook`: This callback is run every time the menu is loaded into memory. It's a good place to register some listeners (for example, a draw listener to render the menu).
- `unloadHook`: This callback is run every time the menu is unloaded from memory. It's a good place to unregister your listeners.
- `deleteHook`: This callback is run once before getting ride of the menu state. It's a good place to free the persistent data you allocated.

Lifecycle hooks should be set/unset in the main/exit functions of the menu's module.

The menu manager also provides a way to keep data permanently for each menu. It is called *Permanent Data*. This data will always be available for the given menu and will never be freed by the **MenuMgr**. (Since permanent data is never freed, it is recommended to avoid keeping large amount of data in there.)

> You can look at the Tools Menu (`/modules/menus/menu_tools/`) as an example of a typical menu implementation.

## IDE setup

You can use any IDE to code for **TPGZ**, but the project has some facilities to help with development on **VSCode**.

### Tasks

A few **VSCode** tasks are provided to ease the build process a little bit. The available tasks are:

- ***Setup***: Makes a build folder for the given version (if it doesn't exits), and configures it as a build folder for that version.
- ***Clean***: Removes all the generated files from the given build folder.
- ***Build***: Builds the project. It makes the build folder ready to be used with the patcher.
- ***Generate ISO***: Builds the project and generates a patched ISO. The built version's dump must be in the `isos` folder with the right name. See the section [Folder Structure](#folder-structure) for more details.
- ***Generate patch***: Builds the project and generates a patch file ready to distribute.
- ***Formatting***: Formats all the project's source files with the correct formatting.

> It is not required to run the *Setup* task, as all the build tasks will run it before themselves.

### Dev Container

The folder `.devcontainer` contains configuration files that can be used by **VSCode**'s extension [**Remote Container**](https://code.visualstudio.com/docs/remote/containers) and with [***Docker***](https://www.docker.com/) installed on your system to make a development container that can provide a standardized environment that is guaranteed to build the project.
