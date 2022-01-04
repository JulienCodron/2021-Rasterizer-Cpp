
# The Minimalist Windowing Library

Copyright (c) 2021 Université d'Artois  
Maintainer: [Tiago de Lima](mailto:tiago.delima@univ-artois.fr)

---

MinWin is a library created for the lab projects of the course Game Engine
Fundamentals--Mathematical Tools thought at Université d'Artois.  It is intend
to provide minimal windowing capabilities for the students to realise their lab
projects. With this library you can:

  - Open a window.

  - Handle keyboard inputs.

  - Render text.

  - Draw pixels.

And that is pretty much it!

Differently from other windowing libraries (e.g., SFML and GLUT), MinWin does
not draw lines, polygons, etc.. Apart from that, the interface of MinWin is very
similar to that of SFML.


## Dependencies

MinWin has been created using the Simple DirectMedia Layer 2.0 (SDL2) and one of
its extensions called SDL_ttf 2.0.  To be able to compile and use MinWin, you
need to install the SDL2 development libraries.  This should be a simple task.
If you use Ubuntu, then both SDL2 and SDL_ttf are on the list of available
packages under the names `libsdl2-dev` and `libsdl2-ttf-dev`, respectively.  (By
the way, you may have them installed already!)  If you do not use Ubuntu, SDL2
development libraries can be downloaded for free from [libsdl.org](https://libsdl.org),
and SDL_ttf can also be downloaded for free from [libsdl.org/projects/SDL_ttf](https://www.libsdl.org/projects/SDL_ttf/).  Be sure that in each case, you install the development
version (not the runtime version).


## Instructions


To compile MinWin, go to the main folder and type:

    make

It should generate a dynamically linked library file called `libminwin.so` (or
`libminwin.dylib` on Mac OS X) on the `bin` folder.

To test MinWin, generate the tester program by typing:

    make tester

It should generate the file `test_minwin` on the `bin` folder. After that, add
the path to the library to the `LD_LIBRARY_PATH`, so that the library loader can
find it, as follows:

    export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:<minwin>/bin

where `<minwin>` above is the path to the folder where the source code of MinWin
is located. Now, to lunch the tester, type:

    ./bin/test_minwin

If everything is OK, it will open a window entitled 'MinWin Test' showing some
text and some lines. You can close the window by clicking on the button quit or
pressing the 'ESC' key.

The files `test/test_minwin.h` and `test/test_minwin.cpp` are a good example of
how to use MinWin in your project.  In addition, folder `doc` contains a
documentation generated automatically by [Doxygen](http://www.doxygen.org/index.html).

To clean up type:

    make clean

It will remove all binaries and object files.


## Compiling your code with MinWin

To compile your source code with MinWin, you must give the option
`-I<minwin>/include` to the compiler and the options `-L<minwin>/bin` and
`-lminwin` to the loader, so that it can find the file `libminwin.so` (or
`libminwin.dylib`) at compile time.  For example, let your project consist of
the files:

    project.h
    project.cpp

You should type the following:

    g++ -c -o project.o project.cpp
    g++ -L<minwin>bin -o projet -lminwin

To run the executable file, you must set the environment variable `LD_LIBRARY_PAHT`,
as for the test above.  That is type:

    export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:<minwin>/bin

and then run your project as you would normally do:

    ./project

Have fun!

