## MEX and CMake Workspace Example

This workspace demonstrates CMake and MEX compilation using C++ classes. In Matlab, the result is persistent objects.

The following compilation methods (MEX and CMake) are entirely independent. One is not required for the other. The purpose is to provide an example showing that the two can coexist in the same workspace. This allows the same code base to used for both.

### For MEX
1. Navigate to the `matlab` subdirectory
```
cd /path/to/repo/matlab/
```
1. From Matlab command:
```
build
```
Alternatively, from the terminal (not required):
```
matlab -nojvm < testingmex.m
```
TODO: notes about using the script+mex file to instantiate the class and mention an example script


### For CMake
1. Navigate
1. ... TODO


- for CMake, headers will be such that it never requires the mex api
-
