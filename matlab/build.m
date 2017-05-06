clear all; %#ok<CLALL>


% set include path
pathkk = ['-I' fullfile(fileparts(pwd),'include')];

% build
%mex('-v', pathkk, 'src/example.cpp')
%mex class_interface_mex.cpp my_class.cpp;
src1 = fullfile(pwd,'class_interface_mex.cpp');
src2 = fullfile(fileparts(pwd),'src','my_class.cpp');
mex('-v', pathkk, src1, src2);


% -----------------------
% eventually move below here to separate script
% -----------------------
 
% call the script that instantiates the matlab object
abc = class_interface;

% call a method with an input
abc.train(4.23467)

% TODO:
% test multiple instantiations with different data member values
