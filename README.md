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

# Reference
Below are the links I used to implement repo.
- https://github.com/martinjaros/tm4c-gcc
- http://users.ece.utexas.edu/~valvano/arm/

# Version
1.0.0

# Todos
 - Add OpenOCD support.
 - CMSIS Support.
 
# License
- Use with ISC license:
- http://opensource.org/licenses/ISC
- **NOTE**: Please follow the terms on the refrences too :)

**Free Software, Hell Yeah! \m/**
