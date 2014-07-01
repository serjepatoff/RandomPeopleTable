RandomPeopleTable
=================

This demo app is a showcase of using Qt, QTableView, sqlite, images in table cells, sorting by any column, row deletion, row insertion, multiple rows deletion, Qt resource system, OS X Bundling and dmg creation.

App was tested on:
* OS X 10.9 / XCode 5.1.1 command line tools / Qt 4.8.6
* Windows 7 x64 / VC++ 2010 Express command line / Qt 4.8.6

How to build
------------
```shell
git clone https://github.com/serjepatoff/RandomPeopleTable; cd RandomPeopleTable; qmake; make
```

If you build using VC++ toolchain, use nmake instead of make.

Of course you need Qt and your favourite C++ toolchain to be installed. 
In OS X, the easiest way to install Qt in one command is 

```shell
brew install qt
```

If you don't want to build app, take pre-built 64-bit dmg for OS X 10.7+ from this repo.