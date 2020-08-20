# <a href="http://tehurn.com/tp" target="_blank" rel="noopener noreferrer"><img src="./res/icons/icon.jpg" height="36" width="36" align="top" style="padding-top:3px;"/></a> tpgz

Twilight Princess ROM hack to practice speedrunning.

- [Creating an ISO](./docs/CreatingAnIso.md) - Create your own practice ISO.

⚠️ tpgz is still in early development.<br>
If you have questions or need help, ask in the [#tools-dev](https://discord.gg/m2vmcyT) channel of the [TP Speedrunning Discord](https://discord.gg/tp).

## Features

Use L+R+dpadDown to open the main menu which contains the following options:

```
cheats menu:
- infinite air                  // Gives Link infinite air underwater
- infinite arrows               // Gives Link 99 arrows
- infinite bombs                // Gives Link 99 bombs in all bags
- infinite hearts               // Link will always have full hearts
- infinite oil                  // Gives Link infinite lantern oil
- infinite rupees               // Link will always have 1000 rupees
- infinite slingshot            // Gives Link 99 slingshot pellets
- invincible                    // Makes Link invincible (no hurtbox, but can still take fall damage and drown)
- invincible enemies*           // Makes some enemies invincible (infinite health)
- moon jump                     // Hold R+A to moon jump
- super clawshot (TBD)          // Clawshot is long and can grab most things (not implemented yet)
- super spinner (TBD)           // Spinner is very fast and can hover (not implemented yet)

flags menu:
- boss flag                     // Set the boss flag value. Press A to lock the value
- epona stolen                  // Toggle flag for Epona being stolen
- epona tamed                   // Toggle flag for Epona being tamed
- map warping                   // Toggle flag for having map warping
- midna charge                  // Toggle flag for Midna charge
- midna healthy                 // Toggle flag for Midna being healthy/sick
- midna on back                 // Toggle flag for Midna appearing on Wolf Link's back
- midna on z                    // Toggle flag for being able to use Midna
- transform/warp                // Toggle flag for transforming/warping
- wolf sense                    // Toggle flag for having wolf sense

inventory menu:
- item wheel                    // Can set the 24 item wheel slots to any item
- pause menu (TBD)              // Can modify the pause menu collection (not implemented yet)

memory menu:
- Add memory watches to the screen

practice menu:
- Load practice files* (supports popular Any% and 100% locations)

scene menu:
- disable bg music*             // Disables background and enemy music
- disable sfx                   // Disables sound effects (item, weather, etc.)
- freeze actors                 // Freezes actors
- freeze camera                 // Locks the camera in place
- hide actors                   // Hides actors
- hide hud                      // Hides the heads-up display
- time (hrs)                    // The current in-game hour
- time (mins)                   // The current in-game minutes

settings menu:
- log level                     // Changes log level for debugging
- drop shadows                  // Adds shadows to all font letters
- save card                     // Save settings to memory card
- load card                     // Load settings from memory card
- area reload behavior          // load area = Reload last area; load file = Reload last file

tools menu:
- area reload                   // Use L+R+Start+A to reload current area
- fast bonk recovery            // Reduces bonk animation significantly
- fast movement                 // Link's movement is much faster
- gorge checker                 // Use L+Z to warp to Kakariko Gorge
- input viewer                  // Show current inputs (buttons only for now)
- link debug info               // Show Link's position, angle, and speed
- no sinking in sand            // Link won't sink in sand
- roll checker                  // Frame counter for chaining rolls
- teleport                      // dpadUp to set, dpadDown to load
- timer                         // Frame timer: Z+A to start/stop, Z+B to reset
- link tunic color:             // Changes Link's tunic color (green, blue, red, orange, yellow, white, or cycle)

warping menu:
- warp to dungeons, towns, grottos, etc. (not implemented yet)
```

### Known Issues

```
- invincible enemies cheat can't be turned off once turned on
- disabled bg music tool may not always disable bg music
- loading practice files can crash in certain situations
```

### Planned Features

```
- free cam
- actor spawner
- frame advance
- collision viewer
- menu font selector
- lag counter & loading counter
```

## Contributing

We'd love for you to help out on `tpgz`! See [CONTRIBUTING.md](./CONTRIBUTING.md) for how to get started.

## Building

Tired of waiting for the next release? See [BUILDING.md](./BUILDING.md) to learn how to create local builds.
