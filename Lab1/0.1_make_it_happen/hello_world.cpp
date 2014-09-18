#include <iostream>

int main () {
  std::cout << "Hello, World!\n";
  int array[5];
  std::cout<< "Will fail? "<<array[6]<<std::endl;
  std::cout<<"Nope"<<std::endl;
}
