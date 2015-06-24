# Symphony Toolbox for Scilab

A toolbox that provides mixed integer linear programming tools in Scilab through the Symphony library

Tested with Symphony 5.5.6 and Scilab 5.5.2

## To install:
1. Download and install the Symphony library. Instructions can be found [here](https://projects.coin-or.org/SYMPHONY/ "SYMPHONY development home page")
2. Clone this (Symphony Toolbox for Scilab) repository on your computer
3. In Scilab, change the working directory to the root directory of the
   this (Symphony Toolbox for Scilab) repository.
4. If you have installed Symphony for the whole system (in /usr/), run `exec
   builder.sce`. If no errors occur, then the toolbox has been compiled
   successfully.
5. If you have installed Symphony locally just for a single user (in /home/),
   then first edit builder.sce and change the LINKER_FLAGS variable as
   explained in the comment there. Then run `exec builder.sce1`.

## To use:
1. In Scilab, change the working directory to the root directory of the
   repository
2. Run `exec loader.sce`
3. The library is now ready for use.

## Help:
For help on the available functions, you should also run `exec
help/addchapter.sce` after running `exec loader.sce`. Now you will be able to
access the help files in the normal way.

