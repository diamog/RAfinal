#include "my_num.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <ctime>
s_t nChoosek( s_t n, s_t k )
{
    if (k > n) return 0;
    if (k * 2 > n) k = n-k;
    if (k == 0) return 1;

    s_t result = n;
    for( s_t i = 2; i <= k; ++i ) {
        result *= (n-i+1);
        result /= i;
    }
    return result;
}
s_t myincreasingsseq(std::vector<store_t>& nums, std::vector<s_t>& indices) {
  std::vector<s_t> L;
  s_t max=1;
  s_t l = indices.size();
  for (unsigned int i=0;i<l;i++) {
    s_t temp = 1;
    for (unsigned int j=0;j<i;j++) {
      if (nums[indices[j]]<=nums[indices[i]])
        if (L[j]+1>temp)
          temp=L[j]+1;
    }
    if (temp>max)
      max=temp;
    L.push_back(temp);
  }
  return max;
}
/*
s_t longestIncreasingSubsequence(std::vector<s_t> nums, s_t* indices, s_t l) {
  //Algorithm taken from https://en.wikipedia.org/wiki/Longest_increasing_subsequence
  s_t* P = new s_t[l];
  s_t* M = new s_t[l+1];

  s_t L = 0;
  for (s_t i=0;i<l-1;i++) {
    // Binary search for the largest positive j ≤ L
    // such that array[M[j]] < array[i]
    s_t lo = 1;
    s_t hi = L;
    while (lo <= hi) {
      s_t mid = ceil((lo+hi)/2);
      if (nums[indices[M[mid]]] < nums[indices[i]])
        lo = mid+1;
      else
        hi = mid-1;
    }
    // After searching, lo is 1 greater than the
    // length of the longest prefix of array[i]
    s_t newL = lo;

    // The predecessor of array[i] is the last index of 
    // the subsequence of length newL-1
    P[i] = M[newL-1];
    M[newL] = i;

    if (newL > L)
      // If we found a subsequence longer than any we've
      // found yet, update L
      L = newL;
  }
  return L;
  
}
*/

bool testSubsequence(std::vector<store_t>& nums, s_t l, float alpha) {
  std::vector<s_t> indices;

  for (s_t i=0;i<l;i++) {
    indices.push_back(rand()%(nums.size()));
  }
  std::sort(indices.begin(),indices.end());
  s_t L = myincreasingsseq(nums,indices);
  return L>=ceil(alpha*l);
}

int main(int argc, char* argv[]) {
  srand(time(NULL));
  assert(argc>3);
  std::ifstream in_str(argv[1]);
  if (!in_str)
    throw 1;
  float alpha = atof(argv[2]);
  s_t l = atoi(argv[3]);
  double pstar=0;
  std::clock_t start_ps = std::clock();
  for (s_t i =ceil(alpha*l);i<=l;i++) {
    pstar+=nChoosek(l,i)*pow(alpha,i)*pow(1-alpha,l-i);
  }
  std::cout<<pstar<<'\n';
  std::cout<<"Computing p* took "<<(std::clock()-start_ps)/(double)CLOCKS_PER_SEC<<"seconds\n";

  std::clock_t start_reading = std::clock();
  s_t num;
  std::vector<store_t> numbers;
  while (in_str>>num) {
    numbers.push_back(num);
  }
  std::cout<<"Reading in numbers took "<<(std::clock()-start_reading)/(double)CLOCKS_PER_SEC<<"seconds\n";

  std::clock_t start_running = std::clock();
  unsigned int m = 100000;
  unsigned int worked=0;
  for (int i=0;i<m;i++) {
    worked+=testSubsequence(numbers,l,alpha);
  }
  double p = worked*1.0/m;
  std::cout<<p<<'\n';
  if (p>pstar) 
    std::cout<<"YES\n";
  else
    std::cout<<"NO\n";
  std::cout<<"Running algorithm took "<<(std::clock()-start_running)/(double)CLOCKS_PER_SEC<<"seconds\n";

  return 0;
}
