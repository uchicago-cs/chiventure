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
directory inside `src/` (e.g., `src/ui/`, `src/wdl`, etc.). Each component's
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


## Git branches

In general, we will be following Vincent Driessen's [git flow](https://nvie.com/posts/a-successful-git-branching-model/) model of branching. Please take a few minutes to read that article in full.

There are a few modifications we will be making to Vincent's model:
* As you read the article, whenever you see "merge to `master`", mentally replace that with "pull request to `master`".
* We will not have release or hotfix branches.
* Rather than one `dev` branch, each team will have their own: `actions/dev`, `checkpointing/dev`, `cli/dev`, `state/dev`, `ui/dev`, and `wdl/dev`.
    * __Note:__ there is no hierarchy with branches; using `/` in branch names is just a convenient way to organize things.
* Feature branches will be named similarly to the `dev` branches. For example, if some people from UI are working on a map view, the branch for that code might be `ui/map-view`. When that work is complete, they would send a PR to the `ui/dev` branch, that would only need review from a teammate. When the work is in a polished state and lives on `ui/dev`, they would send a PR to `master`.


