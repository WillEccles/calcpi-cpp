# calcpi-cpp
"Calculates" (read: guesstimates) Pi over a certain number of iterations (in parallel, if specified) using the Nilakantha series.

## Installing

If you prefer not to compile the program yourself, you can always try the unix binaries provided with [each release](https://github.com/WillEccles/calcpi-cpp/releases). These are updated to be the latest version of the program available. Make sure you read [the usage info](usage.md) before using it.

## Compiling

If you have GCC/G++ installed, you can simply use the Makefile included in the repository:

`$ make`

You can also use this to clean out the compiled output:

`$ make clean`

## Running

After compiling (the previous step), you can run `calcpi.o` from the command line. This takes a few arguments:

`calcpi [threads] [iterations] [decimal places]`

`threads`: How many threads should be used. It's highly recommended that you run this using as many threads as you can, so if you have a 4-core processor without Hyperthreading, you should run this with 4. If 0 is specified, it will use as many threads as it detects that it can, so if you have 4 cores it will use 4 threads.

`iterations`: How many iterations to do. This will be `ULONG_MAX` by default, so it's **HIGHLY** recommended that you run this with a number around 100 million.

`decimal places`: How many decimal places to show. It will show 10 by default. This can be set up to 50.

## Find a bug?

Go ahead and make an issue. I'll get around to it eventually. If you can, make a pull request as well. This makes my life easier, and gives you the satisfaction of doing something cool.
