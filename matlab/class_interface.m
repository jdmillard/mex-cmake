% CLASS_INTERFACE Example MATLAB class wrapper to an underlying C++ class
% "class_interface_mex" is the name of the .mex file in the same directory
% The "mexFunction" is always what is executed in C++ by Matlab API design
% The inputs to class_interface_mex are then the inputs to mexFunction
% in the form of the "prhs" array (see class_interface_mex.cpp).
% The values of these inputs are evaluated by mexFunction to perform C++
% class operations then return results in the form of the "plhs" array.

classdef class_interface < handle
    properties (SetAccess = private, Hidden = false)
        objectHandle; % Handle to the underlying C++ class instance
    end
    methods
        %% Constructor - Create a new C++ class instance 
        function this = class_interface(varargin)
            this.objectHandle = class_interface_mex('new', varargin{:});
        end
        
        %% Destructor - Destroy the C++ class instance
        function delete(this)
            class_interface_mex('delete', this.objectHandle);
        end

        %% Train - an example class method call
        function varargout = train(this, varargin)
            [varargout{1:nargout}] = class_interface_mex('train', this.objectHandle, varargin{:});
        end

        %% Test - another example class method call
        function varargout = test(this, varargin)
            [varargout{1:nargout}] = class_interface_mex('test', this.objectHandle, varargin{:});
        end
    end
end