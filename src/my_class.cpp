#include "my_class.h"

double my_class123::train(double inin)
{
  std::cout << "testing across files guts" << std::endl;
  std::cout << inin << std::endl;
  return inin/2;
}

void my_class123::test()
{
  std::cout << "testing across files guts" << std::endl;
  return;
}
