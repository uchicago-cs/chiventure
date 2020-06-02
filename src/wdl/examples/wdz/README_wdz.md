# WDZ file format testing

## The `wdz` script

This is a shell script which automates the creation of the `.wdz` folder structure and the corresponding zipped `.wdz` archive.

Usage:

`./wdz [mode] [gamename]`

where
- `wdz init [gamename]` creates a skeleton directory structure for a wdz game with the provided gamename, and creates a corresponding skeleton .wdz archive with the same contents.
- `wdz update [gamename]` updates the zipped .wdz archive with new contents from the corresponding folder of the same game name.

Right now, the script generates a WDZ archive containing the JSON files for the player, rooms, items, actions, and global conditions. However, more JSON files to be included can be specified by appending to the variable "jsons" in the shell script.

The script uses the zip tool to create and update archives, specifically `/usr/bin/zip`.

