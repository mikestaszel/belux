# belux
Adventures in OS Development.

## Goals

* Learn about OS development.
* Break things and have fun.
* This technically isn't an operating system yet. It's missing memory management and processes.

## Non-goals

* No one should use this for anything.
* No one should expect this to ever actually be finished.

## Building

On Ubuntu:

    sudo apt install build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo qemu-system-i386 xorriso nasm

I followed this guide to build a cross-compiler: https://wiki.osdev.org/GCC_Cross-Compiler

Once you have that, you should be able to simply run:

    make

This will build the kernel binary.

To build an ISO, run:

    make iso

To run the operting system using QEMU, run:

    make run
