#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>
#include <omp.h>

int main(){
  //variables for timing
  std::chrono::high_resolution_clock::time_point begin;
  std::chrono::high_resolution_clock::time_point end;

  //create vectors vectors
  int size = 1000 * 1000 * 200;
  
  std::vector< double >  vector0(0);
  std::vector< double >  vector1(0);

#pragma omp parallel num_threads(2)
  {
    //by reszing the vector the memory has to be newly allocated
    if(omp_get_thread_num() == 0){
      vector0.resize(size);
    } else {
      vector1.resize(size);
    }
  }

#pragma omp parallel num_threads(2)
  {
      //// this critical section is necessary since the timing would be messed up otherwise 
#pragma omp critical
      {
	begin = std::chrono::high_resolution_clock::now();
	
	//// the first thread will work on vector0 the second on vector1
	if(omp_get_thread_num() == 0){
	  std::fill(vector0.begin(),vector0.end(),4.4);
	} else {
	  std::fill(vector1.begin(),vector1.end(),3.3);
	}
	
	end = std::chrono::high_resolution_clock::now();
	
	std::cout << "Thread: " << omp_get_thread_num() << " on CPU: " << sched_getcpu() << "; Time (ms): " ;
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;

    }   
  } 
}

