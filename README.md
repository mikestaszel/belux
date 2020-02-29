# belux
Adventures in OS Development.

## Goals

* Learn about OS development.
* Break things and have fun.

## Non-goals

* No one should use this for anything.
* No one should expect this to ever be finished.

## Acknowledgements

A lot of code was taken from multiple sources:

* [James Molloy's Kernel Development Tutorials](http://www.jamesmolloy.co.uk/tutorial_html/)
* [cstack](https://github.com/cstack/osdev)
* [encounter](https://github.com/encounter/osdev)
* [OSDev Wiki](https://wiki.osdev.org/Expanded_Main_Page)

## Building

On Ubuntu:

    sudo apt install build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo qemu-system-i386 xorriso nasm

Follow [this guide](https://wiki.osdev.org/GCC_Cross-Compiler) to build a cross-compiler.

Once you have that, you should be able to simply run:

    make

This will build the kernel binary.

To run the operting system using QEMU, run:

    make run

## Other Notes

For every commit in here there were probably 5 discarded attempts and false-starts. I'm glad I got as far as I did. 
This project helped me finally get through Tanenbaum's "Operating Systems Design and Implementation" book.

I think my next steps will be to look into [xv6](https://pdos.csail.mit.edu/6.828/2019/xv6.html) and/or 
[MINIX 3](https://www.minix3.org/).
