# Developer Guidelines

## Directory structure

**i.e., where to put your files**

The chiventure repository has three top-level directories:

- `src/`: Source code
- `docs/`: Documentation
- `games/`: Sample games

No other top-level directories can be created without prior discussion (ideally
by creating a GitHub issue that proposes the creation of a new top-level directory).

The project is divided into multiple *components*. Each component will have a
directory inside `src/` (e.g., `src/ui/`, `src/wdl/`, etc.). Each component's
directory *must* have the following subdirectories:

- `src/`: Source code
- `include/`: Header files exposing interfaces needed by other components
- `examples/`: Example code that is specific to this component.
- `tests/`: Unit tests for this component. 

The component directory must have a Makefile that generates a static library 
file with the same name as a component. For example, for the `cli` component:

- Directory: `src/cli/`
- Makefile: `src/cli/Makefile`
- Library: `src/cli/cli.a`

This library must then be linked from the top-level `Makefile`

## Component Overview

Below is a high-level description of each major component in the `/src/` directory.

#### WDL 

chiventure has a “World Description Language” format that provides the specification of a single game. The WDL component is responsible for defining this language, and for parsing it. Files use the extension `<filename>.wdl`

#### Game State

A game will have some state that chiventure needs to keep track of: rooms, objects in rooms, players, non-player characters, etc. This component models this state, and provides interfaces for simple manipulations of the state of the game (e.g., placing an object in the player’s inventory)

#### Action Management

During the game, a player will be able to perform actions (pushing, pulling, opening, closing, etc.) that will usually affect the state of the game in some way. This component is responsible for processing actions like “TAKE orb” (and checking whether it is possible to perform that action)

#### Checkpointing

As the state of the game changes, chiventure checkpoints the game so we can resume it at a later time. This component is responsible for defining a file format for saving the state of the game, and providing interfaces for saving/loading this state

#### CLI 

This component will be responsible for providing a command prompt, and parsing the commands entered by the user, and using the game state to validate some commands

#### UI

This component is responsible for any non-CLI elements of the user interface, such as visualizing a map of the game or displaying graphics associated with individual rooms

## Style

Your code must follow [this style guide](https://uchicago-cs.github.io/cmsc23300/style_guide.html) (used in CS 233, which also involves projects in C).

## Git branches

In general, we will be following Vincent Driessen's [git flow](https://nvie.com/posts/a-successful-git-branching-model/) model of branching. Please take a few minutes to read that article in full.

There are a few modifications we will be making to Vincent's model:

* As you read the article, whenever you see "merge to `master`", mentally replace that with "pull request to `master`".
* We will not have release or hotfix branches.
* Rather than one `dev` branch, each team will have their own: `actions/dev`, `checkpointing/dev`, `cli/dev`, `state/dev`, `ui/dev`, and `wdl/dev`.
    * __Note:__ there is no hierarchy with branches; using `/` in branch names is just a convenient way to organize things.
* Feature branches will be named similarly to the `dev` branches. For example, if some people from UI are working on a map view, the branch for that code might be `ui/map-view`. When that work is complete, they would send a PR to the `ui/dev` branch, that would only need review from a teammate. When the work is in a polished state and lives on `ui/dev`, they would send a PR to `master`.
* Never merge branches across teams. e.g., never merge another team's `dev` branch into your team's `dev` branch, or another team's feature branch into your `dev` branch. Syncing up with other teams must always happen through `master`: you can (and should) merge changes from `master` into your `dev` branch. So, if another team has work you'd like to use in your own code, you must wait until their code makes it into `master`.


