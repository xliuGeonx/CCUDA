#include <iostream>
#include "cuda_profiler_api.h"
using namespace std;  
  
extern "C" 
  int func();

int main()  
{  
  //cudaProfilerStart();
  func();  
  cudaProfilerStop();
  return 0;  
}  