#include <mutex>
#include <cmath>
#include <atomic>
#include <thread>
#include <vector>
#include <iostream>

#define MAX 1000000

char* nums;
std::mutex mux[MAX];

int isPrime(int num) 
{
  int prime = 1;
  for(int i = 2; i < sqrt(num); i++)
  {
    if(num%i == 0)
    {
      prime = 0;
      break;
    }
  } 
  return prime;
}

void calc_primes(int id)
{
  //std::cout << "Hi!" << std::endl;
  for(int i = 3; i < MAX; i++)
  {
    if(i%2==0)
      continue;

    std::unique_lock<std::mutex> lck(mux[i],std::defer_lock);
    if(lck.try_lock())
    {
      //std::cout << "Thread " << id << " got lock on " << i << std::endl;
      if(nums[i] != 2) 
      {
        //std::cout << "Thread " << id << " Number taken" << std::endl;
        lck.unlock();
        continue;
      }

      nums[i] = isPrime(i);
      lck.unlock();
      // for(int  j = 0; j < MAX/i; j++) {
      //   int mult = j*i;
      //   std::unique_lock<std::mutex> lck(mux[mult],std::defer_lock);
      //   if(lck.try_lock())
      //   {
      //     nums[mult] = 0;
      //     lck.unlock();
      //   }
      //   else
      //   {
      //     //std::cout <<"Thread " << id << ": Lock 2 failed" << std::endl;
      //     continue;
      //   }
      // }
    }
    else
    {
      //std::cout <<"Thread " << id << ": Lock failed moving to next" << std::endl;
      continue;
    }
  }
}

const char* BoolToString(bool b)
{
  return b ? "true" : "false";
}

void print_results() 
{
  std::cout << "1" << std::endl;
  std::cout << "2" << std::endl;
  for(int i=3;i<MAX;i++)
  {
    if(nums[i] == 1)
      std::cout << i << std::endl;
  }
}

int main(int argc, char* argv[]) 
{
  nums = new char[MAX];
  std::fill_n(nums, MAX, 2);
  int num_threads;
  if(argc < 2)
    num_threads = 4;
  else
    num_threads = atoi(argv[1]);

  std::cout << num_threads << " threads" << std::endl;
  std::cout << "Finding primes <= " << MAX << std::endl;

  std::vector<std::thread> threads;
  for (int i = 0; i < num_threads; i++) {
      threads.emplace_back(calc_primes, i);
  }

  for (auto &thread : threads) thread.join();

  //print_results();

  return 0;
}