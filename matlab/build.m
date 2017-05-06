% this script compiles the indicated source files below as well as related
% headers to produce a .mex binary which can be executed by Matlab.
% the resulting functionality is somewhat analogous to the CMakeLists.txt

clear all; %#ok<CLALL>

% "fullfile" pieces together strings into a full path
% "pwd" (obviously) returns a string of the working directory path
% "fileparts(pwd)" returns a string of the path one directory up

% include path
include = ['-I' fullfile(fileparts(pwd),'include')];

% specify source files
src1 = fullfile(pwd,'class_interface_mex.cpp');
src2 = fullfile(fileparts(pwd),'src','my_class.cpp');

% build
mex('-v', include, src1, src2);


% -----------------------
% eventually move below here to separate script
% -----------------------


% call the script that instantiates the matlab object
% this uses the .mex to create a matlab shell class
abc = class_interface;

% call a method with an input
abc.train(4.23467)

% TODO:
% test multiple instantiations with different data member values
