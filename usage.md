### Usage:
`calcpi [threads] [iterations] [decimal points]`

`threads` specifies how many threads should be used during the calculation. If the number is less than or equal to 0, it uses as many as it thinks your system is capable of. I recommend setting this to 0 unless you need to be able to do other things.

`iterations` is how many iterations should be used during the calculation. Technically, the more you use, the more accurately it will guess Pi. The biggest this can be is `2<sup>64</sup> - 1`, which is *not* what you should use. I recommend making this something like 10 million, 100 million, or a billion, but if you want to be accurate to more decimal places, you can increase this number.

`decimal points` is the number of decimal points to display. This is 10 by default, and you can set it up to 50.

### Installation:
As of version 2.1.0, there will no longer be a binary supplied for releases. This is because it will be less efficient (if it works at all) on other processors, and you *should* compile this program yourself.

In order to compile this program, download the supplied source, then run `make` inside the extracted folder. This should supply you with a file called `calcpi.o` (or `calcpi.exe` if you use MinGW or similar). You can then run that according to the usage information above.

### Visual Studio Code

If you are on a system with GCC/G++ installed, you can use VS Code to compile and run tests. Open the repository folder in VS Code, then run your default build task. On Mac OS, this is Shift+Cmd+B by default. After this has compiled (hopefully without issues), you can open the tasks menu (Shift+Cmd+T on Mac OS) and run the program with three different iteration amounts: 1M (fast), 1B (medium), 1T (slow). This will automatically use all available cores.