# bar-chart-race

## A bar chart program to display data in a race-like model

A bar chart is a data visualization technique that is often employed to present categorical data. In this assignment, one bar chart may be composed of up to 15 bars. A bar is represented by a horizontal rectangle whose length corresponds to the data value it represents.

## How To Build

To create a build of the game, on the base directory of the project run the following commands:

```shell
cmake -S ./ -B build
cmake --build build
```

### Windows and MinGW

If you are running this on a Windows machine and using MinGW as a compiler, you might want to use the following command instead. This will make sure you are using MinGW and prevent any futher issues that might occur.

```shell
cmake -S ./ -B build -G "MinGW Makefiles"
cmake --build build
```

Be aware that CMake uses a cache file, so if you are already using the proper Windows command and still facing issues on the build process, either delete the `CMakeCache.txt` file on the build directory or change your build directory to a new one.

## How To Run

Once you have builded the executable of the game, to play it, you can simply run:

```shell
./build/run filename.extension
```

Have in mind that this game needs a file do be able to run. The file lines follow this rules:

1. The initial wage
2. The number of rounds
3. The spots

You can use and/or see the example file named `example.dat` that is on the root directory

Author: Lucas do Nascimento Ribeiro
