# About

The build system presented here has the minimal possible set of files to get started with TM4C123GH6PM (ARM Cortex M4). TIVA C Launchpad board. The code was tested on Ubuntu 15.10 64 Bit machine.

# Prerequisite
In order to use the build system correctly you will need to have ARM GNU tool chain installed. Which can be found here: https://launchpad.net/gcc-arm-embedded .

# Usage
- Edit **main.c** under the folder **src**. 
- Add any of the new source (.c) files in (**src**) folder.
- Add header (.h) files in the **inc** folder.
- Please Modify the **PROJECT** and **ICDI** variables in the **Makefile** as per your needs or system configuration.
- Using the following will generate the binary file only!
``` 
$ make
```
- In order to upload the code to board use the following:
``` 
$ sudo make flash
```
- To clean the source code use:
``` 
$ make clean
```

# OpenOCD
OpenOCD can be used for debugging. To install OpenOCD (if you don't already have) use the following command:
```
$ sudo make setup_openocd
```
This shall install openocd into your system.

# Using OpenOCD
Once OpenOCD is installed, launch it using the following
```
$ sudo make openocd
```
The terminal may now be minimized as it needs to stay open but cannot be used for anything else.
In a new terminal window you can use:
```
$ make debug 
```

Once the **gdb** prompt appears use the following gdb commands.
```
(gdb) target extended-remote :3333
(gdb) monitor reset halt
(gdb) load
(gdb) monitor reset init
```
Set the break points as you like (using the usual gdb commands) and then use:
```
(gdb) continue
```
This shall start the execution of the code until the break point is hit. 

# Reference
Below are the links I used to implement repo.
- https://github.com/martinjaros/tm4c-gcc
- http://users.ece.utexas.edu/~valvano/arm/
- http://git.code.sf.net/p/openocd/code

# Version
1.0.0

# OpenOCD
OpenOCD can be used for debugging. To install OpenOCD (if you don't already have) use the following command:
```
$ sudo make setup_openocd
```
This shall install openocd into your system.

# Using OpenOCD
Once OpenOCD is installed, launch it using the following
```
$ sudo make openocd
```
The terminal may now be minimized as it needs to stay open but cannot be used for anything else.
In a new terminal window you can use:
```
$ make debug 
```

Once the **gdb** prompt appears use the following gdb commands.
```
(gdb) target extended-remote :3333
(gdb) monitor reset halt
(gdb) load
(gdb) monitor reset init
```
Set the break points as you like (using the usual gdb commands) and then use:
```
(gdb) continue
```
This shall start the execution of the code until the break point is hit. 

# Todos
 - CMSIS Support.
 
# License
- Use with ISC license:
- http://opensource.org/licenses/ISC
- **NOTE**: Please follow the terms on the refrences too :)

**Free Software, Hell Yeah! \m/**
