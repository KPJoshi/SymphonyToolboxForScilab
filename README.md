# Symphony Toolbox for Scilab

A toolbox that provides mixed integer linear programming tools in Scilab through the Symphony library

Tested with Symphony 5.5.6 and Scilab 5.5.2

## To install:
1. Download and install the Symphony library. Instructions can be found [here](https://projects.coin-or.org/SYMPHONY/ "SYMPHONY development home page")
2. Clone this repository on your computer
3. In Scilab, change the working directory to the root directory of the repository
4. Run `exec builder.sce`. If no errors occur, then the toolbox has been compiled successfully.

## To use:
1. In Scilab, change the working directory to the root directory of the repository
2. Run `exec loader.sce`
3. The library is now ready for use.

## Help:
For help on the available functions, you should also run `exec help/addchapter.sce` after running `exec loader.sce`. Now you will be able to access the help files in the normal way.
