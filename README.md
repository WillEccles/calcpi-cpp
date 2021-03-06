# calcpi-cpp
"Calculates" (read: guesstimates) Pi over a certain number of iterations (in parallel, if specified) using the Nilakantha series.

Now, you might wonder something along the lines of this: "Well that's cool and all, but why on Earth would I want to calculate Pi?" This is a good question. You might have a reason I have not heard of, but my reason was just to say I did, as well as to make a little fun program that took up a little of my time and gave me something to think about.

## Installing

It is highly recommended that you compile this yourself, as compiling it yourself is more likely to give you a working program. It will also make a program that is specifically tuned to your system, which the pre-compiled one is not.

For instructions on compiling by yourself, see **[Compiling](#compiling)**.

If you prefer not to compile the program yourself, you can always try the unix binaries provided with [each release](https://github.com/WillEccles/calcpi-cpp/releases). These are updated to be the latest version of the program available. Make sure you read [the usage info](usage.md) before using it.

## Compiling

If you compile this yourself using the instructions below, you will have the added advantage of including the `-march=native` flag, which will specify that the program should use the instruction set of your specific platform.

If you have GCC/G++ installed, you can simply use the Makefile included in the repository:

`$ make`

You can also use this to clean out the compiled output:

`$ make clean`

## Running

See [usage information](usage.md).

## Find a bug?

Go ahead and make an issue. I'll get around to it eventually. If you can, make a pull request as well. This makes my life easier, and gives you the satisfaction of doing something cool.
