#include <iostream>
#include "mex.h"
#include "class_handle.h"
#include "my_class.h"

/*
 * The "mexFunction" is always what gets called by Matlab, the inputs seen
 * below is the standard convention. Depending on the input arguments, specific
 * actions are taken such as class instatiation, handle management, or method
 * calls. A script on the Matlab side manages some of the inputs. When
 * everything is functioning, the result is a Matlab shell class that runs the
 * C++ source code under the hood.
 */

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  // nhls   number of expected outputs
  // plhs   array to be populated by outputs (DATA BACK TO MATLAB)
  // nrhs   number of inputs
  // prhs   array poplulated by inputs (DATA FROM MATLAB)

  // get the command string
  // mxGetString (from API) will convert the first input prhs[0] to char
  char cmd[64];
  if (nrhs < 1 || mxGetString(prhs[0], cmd, sizeof(cmd)))
    mexErrMsgTxt("First input should be a command string less than 64 characters long.");


  // input from matlab requesting new object?
  if (!strcmp("new", cmd))
  {
    // check parameters
    if (nlhs != 1)
      mexErrMsgTxt("New: One output expected.");
    // return a handle to a new instance
    plhs[0] = convertPtr2Mat<my_class123>(new my_class123);
    return;
  }


  // if not requesting a new object, two inputs are expected (type and handle)
  if (nrhs < 2)
    mexErrMsgTxt("Second input should be a class instance handle.");


  // input from matlab requesting object deletion?
  if (!strcmp("delete", cmd))
  {
    // destroy the object
    destroyObject<my_class123>(prhs[1]);
    // warn if other commands were ignored
    if (nlhs != 0 || nrhs != 2)
      mexWarnMsgTxt("Delete: Unexpected arguments ignored.");
    return;
  }


  // get the class instance pointer from the second input
  // this has the effect of finding the already-instantiated class' memory
  // location, putting Matlab and C++ on the same page.
  my_class123 *my_class123_instance = convertMat2Ptr<my_class123>(prhs[1]);


  // input from matlab requesting "train" method call
  if (!strcmp("train", cmd)) {
    std::cout << "train method successfully hit from matlab" << std::endl;
    // check parameters
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
    c[0] = outtt; // this assigns the value to the memory where it will be
    // considered an output from matlab's perspective.
    // now the proper value of c is the dereferenced *c; display example:
    //std::cout << *c << std::endl;
    return;
  }


  // input from matlab requesting "test" method call
  if (!strcmp("test", cmd))
  {
    // check parameters
    if (nlhs < 0 || nrhs < 2)
      mexErrMsgTxt("Test: Unexpected arguments.");
    // call the method
    my_class123_instance->test();
    return;
  }

  // Got here, so command not recognized
  mexErrMsgTxt("Command not recognized.");
}
