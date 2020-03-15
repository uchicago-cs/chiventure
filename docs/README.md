# chiventure Documentation

* [Developer Guidelines](developer.md)
* [Actions Specification](actions.md)

## Building chiventure

chiventure uses CMake. To build, run
```
mkdir build
cd build
cmake ..
```

### Dependencies

chiventure depends on `protobuf-c`, `LibYAML` (`Yaml`), `Curses`, and `criterion`. `cmake ..` will warn if any of these are not installed with an error of the form "Could NOT find <library>"

See [dependencies.md](dependencies.md) for information on installing the dependencies
