# Creating an ISO

_These instructions are for Windows.
Mac and Linux please see [BUILDING.md](../BUILDING.md)._

## Quick Overview

tpgz takes a Twilight Princess ISO and generates a new ISO with features that help you practice.
Play the new ISO on [Dolphin](https://dolphin-emu.org/) or a homebrewed Wii.

```
 <TP iso>   +   <patch file>   =>   <TPGZ iso>
     ^               ^                   ^
You provide       Provided            Created
```

## Instructions

The instructions are intentionally detailed to prevent confusion.
If you are having trouble, please check [Troubleshooting](#troubleshooting).

**You will need a Twilight Princess ISO.**
_(Only supports Gamecube version for now.)_

1. Download the latest release [here](https://github.com/zsrtp/tpgz/releases).
   _(Feel free to follow the release page instructions instead of these.)_

2. Unzip the downloaded file to create a new folder, then open that folder.<br>
   You should see something _similar_ to the following:

   - romhack.exe
   - tpgz.patch

3. Put a copy of your Twilight Princess ISO (GCN) in this folder.
   The ISO's filename is not important.<br>
   _Example:_

   - romhack.exe
   - tpgz.patch
   - Legend of Zelda, The - Twilight Princess (USA).iso

4. Copy the folder's path.
   _(Example: `C:\example\path`)_

5. Open cmd.

   - Press `<WindowsKey>+r` then type "cmd" into the popup and hit `<Enter>`.

6. Navigate to the above folder within cmd.

   - In cmd, enter the following and hit enter:<br>
     `cd <paste folder's path here>`

     _Example output:_

     ```
     C:\Users\Name>cd C:\Users\Name\Downloads\tpgz-folder

     C:\Users\Name\Downloads\tpgz-folder>
     ```

7. Run the following to create the tpgz ISO:<br>
   `romhack.exe apply <The-tpgz-patch>.patch <Your-ISO-name>.iso tpgz-patched.iso`

   - It is recommended that you type this out rather than copy-paste to avoid some common mistakes.
   - Type 'romhack.exe apply'.
     - _Note that you can use `<Tab>` to auto-complete files in the current folder.
       Typing "rom" then hitting `<Tab>` should change "rom" to "romhack.exe".
       You can hit `<Tab>` multiple times to cycle through available options.
       "apply" is not a filename so you will have to type it out._
   - Add the patch file's name.
     - _Type "tpgz", then hit `<Tab>.`
       This will auto-complete to the patch's filename._
   - Add your ISO's name.

     - _It is strongly recommended that you use `<Tab>` to auto-complete the ISO's filename.
       This will add necessary quotes if your filename has spaces.<br>
       Correct: "My TP ISO.iso"<br>
       Incorrect: My TP ISO.iso_

   - Add a filename for the new ISO.
     - Use "tpgz-patched.iso" or any other name ending in ".iso".
   - Press `<Enter>` after you have finished entering the command.
     - This will generate the new ISO.
       It may take a few minutes to complete.

8. Load the new ISO in
   [Dolphin emulator](https://dolphin-emu.org/) or a Wii using a homebrew loader such as [Nintendont](https://github.com/FIX94/Nintendont).

9. Use L+R+dpadDown to open the features menu in game.

## Troubleshooting

### How do I know my ISO is correct?

You need a **Gamecube ISO**.

Correct MD5 hashes:<br>
NTSC-U GCN: **41deff9b1fd2831f48fbfa2dd1054e4d**  
NTSC-J GCN: **b130d78bb78cd63b501ddff210fde498**  
PAL GCN:    **798abb94d649f7d117514578b2abfae1**

Determine the MD5 hash of your ISO with the `md5sum` command.
If your command returns anything other than the above value, you either have the wrong ISO or your ISO was somehow modified.

```
C:\example\path>md5sum "My US Gamecube TP.iso"
41deff9b1fd2831f48fbfa2dd1054e4d *My US Gamecube TP.iso
```

### I get an "Unexpected Argument" error when I try to generate the ISO.

_Example:_

```
error: Found argument 'Zelda,' which wasn't expected, or isn't valid in this context
```

Your ISO likely has spaces in the filename and you do not have quotes around it.

'romhack.exe apply' expects 3 arguments (patch file, initial ISO, output filename):<br>
`romhack.exe apply [1] [2] [3]`

Correct:

```
romhack.exe apply tpgz-v0.1a.patch "Twilight Princess.iso" output.iso
                  ^                 ^                            ^
                 [1]               [2]                          [3]
```

Incorrect:

```
romhack.exe apply tpgz-v0.1a.patch Twilight Princess.iso output.iso
                  ^                 ^       ^        ^         ^
                 [1]               [2]     [3]      [4]       [5]
```

### The practice ISO loads using Nintendont, but my Gamecube controller doesn't work.

1. Start Nintendont.
2. Choose SD or USB as appropriate.
3. Press `B` to open Settings.
4. Set "Native Control" to "On".<br>
   _(Native Control is located in the left column near the bottom of the screen. It is separated from the other items.)_
