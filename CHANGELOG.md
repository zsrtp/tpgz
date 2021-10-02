# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.4] - 2021-10-02

### Added:
- Initial Actor Spawner implementation, located within Scene menu. Supports spawning actor by Proc Name, with custom parameters and subtype.
- Experimental Stallord Phase 2 any% practice save
- Snowpeak Mountain Universal Map Displacement practice tool / All Dungeons practice save. (Note: Full All Dungeons UMD route saves not currently implemented)
- Coro Text Displacement practice tool
- Option to delete TPGZ settings
- Option to delete a selected Memfile

### Changed:
- Sword & Shield Skip practice save loads next to Midna trigger along with hugo
- 100% practice saves updated to Grove 2 Skip route
- Increased max Memfile slots from 9 to 20

### Fixed:
- Practice Save / Memfile loading stability fixes
- Memfiles saving wrong roomNo
- Link position updating when loading an empty memfile
- Some 100% save specials loading at incorrect time
- Clear dungeon flags button


## [0.3] - 2021-03-08

### Added
- All Dungeons practice saves
- Set savefile spawn location tool (need to be in pause menu)
- Flag change logger (wip)
- Memory File saving / loading
- Setting to swap X/Y button equips when loading practice saves


## [0.2] - 2021-02-06

### Added
- Waterfall Sidehop savefile
- Quick scroll on some menus (DPAD-Right/Left)
- Saved events / minigame / dungeon bit flag records added
- Initial Wii support

### Changed
- Reworked temp flags menu into flag records menu
- Flag records / Memory editor menu cursor not line locked
- Tunic changer colors are less vibrant

### Fixed
- Temp flags now properly reset on Fan Tower and Palace 1 saves
- Practice save stability improvements
- Fifo queue works properly with warping menu


## [0.1] - 2020-12-29

### Added

- Initial re-release.

### Changed

- Fixed typos in Italian translation from [@lorenzo-arena](https://github.com/lorenzo-arena).
- Fixed typos in Indonesian translation from [@ekojs](https://github.com/ekojs).
