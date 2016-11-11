### Usage:
`calcpi [threads] [iterations] [decimal points]`

`threads` specifies how many threads should be used during the calculation. If the number is less than or equal to 0, it uses as many as it thinks your system is capable of. I recommend setting this to 0 unless you need to be able to do other things.

`iterations` is how many iterations should be used during the calculation. Technically, the more you use, the more accurately it will guess Pi. The biggest this can be is `2<sup>64</sup> - 1`, which is *not* what you should use. I recommend making this something like 10 million, 100 million, or a billion, but if you want to be accurate to more decimal places, you can increase this number.

`decimal points` is the number of decimal points to display. This is 10 by default, and you can set it up to 50.

### Installation:
If you download the `calcpi` binary provided, it may not work if you aren't on unix. If it doesn't work (this is a possibility depending on your system), you can compile the code yourself using your preferred compiler. The provided binary was compiled on macOS 10.12 Sierra, 64-bit, using g++ (aliased to clang) using the following flags: `-std=c++14 -stdlib=libc++ -O3 -fwhole-program -s -DNDEBUG`

If this does not run for you and you have g++ installed, you can clone the repo and run `make`. If you do not have g++, you should look into how to use your preferred compiler to compile it. You'll need at least C++11 support.
