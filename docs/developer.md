# Developer Guidelines

## Directory structure

**i.e., where to put your files**

The chiventure repository has five top-level directories:

- `src/`: Source code
- `include/`: Shared include files
- `docs/`: Documentation
- `tests/`: Tests
- `games/`: Sample games

No other top-level directories can be created without prior discussion (ideally
by creating a GitHub issue that proposes the creation of a new top-level directory).

The project is divided into multiple *components*. Each component will have a
directory inside `src/` (e.g., `src/ui/`, `src/wdl/`, etc.). Each component's
directory *must* have the following subdirectories:

- `src/`: Source code
- `examples/`: Example code that is specific to this component.
- `sandbox/`: Used for experimenting with code in the early stages of a 
  component's development. This code can be merged into `dev` but is removed
  before merging to `master`. It should be removed permanently once a
  component matures (some of the code may be refactored into 
  examples in the `examples/` directory)
  
Any header file that exposes an interface that will be used by another component
**must** be placed in the top-level `include/` directory, inside a directory
for the component it belongs to (e.g., `include/ui/`)

We expect that all internal header files will be placed inside the component's
`src/` directory, but an `include/` directory can also be created inside
the component's directory it if helps to declutter the files in that component.  

The component directory must have a CMake file that generates a static library 
file with the same name as a component. For example, for the `cli` component:

- Directory: `src/cli/`
- CMake file: `src/cli/CMakeLists.txt`
- Target Library: `libcli.a`

This library must then be linked from the top-level CMake file.

## Component Overview

Below is a high-level description of each major component in the `/src/` directory.

#### WDL 

chiventure has a “World Description Language” format that provides the specification of a single game. The WDL component is responsible for defining this language, and for parsing it. Files use the extension `<filename>.wdl`

#### Game State

A game will have some state that chiventure needs to keep track of: rooms, objects in rooms, players, non-player characters, etc. This component models this state, and provides interfaces for simple manipulations of the state of the game (e.g., placing an object in the player’s inventory)

#### Action Management

During the game, a player will be able to perform actions (pushing, pulling, opening, closing, etc.) that will usually affect the state of the game in some way. This component is responsible for processing actions like “TAKE orb” (and checking whether it is possible to perform that action)

#### CLI 

This component will be responsible for providing a command prompt, and parsing the commands entered by the user, and using the game state to validate some commands

#### UI

This component is responsible for any non-CLI elements of the user interface, such as visualizing a map of the game or displaying graphics associated with individual rooms

## Style

Your code must follow the [Style Guide](https://uchicago-cs.github.io/dev-guide/style_guide_c.html) in the [UChicago CS Developer Guide](https://uchicago-cs.github.io/dev-guide) 

## Git branches

In general, we will be following Vincent Driessen's [git flow](https://nvie.com/posts/a-successful-git-branching-model/) model of branching. Please take a few minutes to read that article in full.

There are a few modifications we will be making to Vincent's model:

* The `master` and `dev` branches are protected in our repository. The only
  way to merge to them is via a pull request.
* Any new code must be contributed by creating a feature branch from `dev` and
  submitting a pull request from that branch into `dev`.
* Feature branches should target incremental improvements to chiventure with
  a single pull request at the end. They are not intended to be long-lived
  branches that are merged into `dev` multiple times.
* Feature branches should following the naming scheme `COMPONENT/DESCRIPTION`.
  For example, if some people from UI are working on a map view, the branch for
  that code might be `ui/map-view`. 
* Only the senior developers can create a release branch to merge code
  from `dev` into `master`.  
* You are allowed (and encouraged) to merge changes from `dev` into a
  feature branch you are working on (to pull in any new code you may need,
  and to resolve integration issues before submitting a pull request). This does not require a pull request and can be done with `git merge`.  
* Never merge a feature branch into another feature branch. If another
  team is working on a feature you need, you must wait until they merge
  it into `dev` (then, you can just merge those changes into your feature
  branch).


