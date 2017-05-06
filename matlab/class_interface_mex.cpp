#include <iostream>
#include "mex.h"
#include "class_handle.h"
#include "my_class.h"

/*
class dummy
{
public:
    double train(double inin);
    void test();
private:
};

double dummy::train(double inin)
{
  std::cout << "testing train guts (internal)" << std::endl;
  std::cout << inin << std::endl;
  return inin/2;
}

void dummy::test()
{
  std::cout << "testing test guts (internal)" << std::endl;
  return;
}

*/

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{

    // Get the command string
    char cmd[64];

	if (nrhs < 1 || mxGetString(prhs[0], cmd, sizeof(cmd)))
		mexErrMsgTxt("First input should be a command string less than 64 characters long.");

    // New
    if (!strcmp("new", cmd)) {
        // Check parameters
        if (nlhs != 1)
            mexErrMsgTxt("New: One output expected.");
        // Return a handle to a new C++ instance
        plhs[0] = convertPtr2Mat<my_class123>(new my_class123);
        return;
    }

    // Check there is a second input, which should be the class instance handle
    if (nrhs < 2)
		mexErrMsgTxt("Second input should be a class instance handle.");

    // Delete
    if (!strcmp("delete", cmd)) {
        // Destroy the C++ object
        destroyObject<my_class123>(prhs[1]);
        // Warn if other commands were ignored
        if (nlhs != 0 || nrhs != 2)
            mexWarnMsgTxt("Delete: Unexpected arguments ignored.");
        return;
    }

    // Get the class instance pointer from the second input
    my_class123 *my_class123_instance = convertMat2Ptr<my_class123>(prhs[1]);

    // Call the various class methods
    // Train
    if (!strcmp("train", cmd)) {
        std::cout << "train method hit from matlabbbb" << std::endl;
        // Check parameters
        if (nlhs < 0 || nrhs < 3)
            mexErrMsgTxt("Train: Unexpected arguments.");


        // get the input
        // get the pointer for the 3rd input
        double *a;
        a = mxGetPr(prhs[2]); // a is now a pointer to the third input
        std::cout << *a << std::endl;

        // define the output format
        plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
        // get the pointer for the output
        double *c;
        c = mxGetPr(plhs[0]);

        // write data to the memory location
        double outtt = my_class123_instance->train(*a);
        c[0] = outtt;
        // now the proper value of c is the dereferenced *c
        //std::cout << *c << std::endl;


        // test that I can instantiate an object from another cpp and .h source
        // and execute one of it's methods
        //std::cout << "ready" << std::endl;
        //my_class123 test123;
        //test123.test();

        return;
    }
    // Test
    if (!strcmp("test", cmd)) {
        // Check parameters
        if (nlhs < 0 || nrhs < 2)
            mexErrMsgTxt("Test: Unexpected arguments.");
        // Call the method
        my_class123_instance->test();
        return;
    }

    // Got here, so command not recognized
    mexErrMsgTxt("Command not recognized.");
}
