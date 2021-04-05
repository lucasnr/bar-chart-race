# bar-chart-race

## A Bar Chart Program To Display Data In A Race-like Model

A bar chart is a data visualization technique that is often employed to present categorical data. In this assignment, one bar chart may be composed of up to 15 bars. A bar is represented by a horizontal rectangle whose length corresponds to the data value it represents.

## How To Build

To create a build of this program, on the base directory of the project run the following commands:

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

Note: Be sure to have POSIX threads, otherwise this might not run as intended or not even compile at all.

## How To Run

Once you have builded the executable of the program, to play it, you can simply run:

```shell
bcr [<options>] <input_data_file>
	Bar Chart Race options:
	-b  <num> Max # of bars in a single chart.
		Valid range is [1,15]. Default values is 5.
	-f  <num> Animation speed in fps (frames per second).
		Valid range is [1,24]. Default value is 24.
```

You can use any of the files present at the `data` directory.

Author: Lucas do Nascimento Ribeiro
