#include <cassert>
#include <cstdlib>
#include "MersenneTwister.h"
#include <iostream>
#include <ctime>
#include <cmath>
#include <algorithm>
#include "my_num.h"
#include <mpi.h>
void phi() {
  static int num=0;
  //  std::cout<<"hi"<<num++<<std::endl;
}
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
int findTarget(std::vector<s_t> ends,s_t& index) {
  for (unsigned int i=0;i<ends.size();i++) {
    if (index<ends[i]) {
      if (i==0)
        return i+1;
      index-=ends[i-1];
      return i+1;
    }
  }
  return ends.size();
}
s_t myincreasingsseq(std::vector<store_t>& nums) {
  std::vector<s_t> L;
  s_t max=1;
  s_t l = nums.size();
  for (unsigned int i=0;i<l;i++) {
    s_t temp = 1;
    for (unsigned int j=0;j<i;j++) {
      if (nums[j]<=nums[i])
        if (L[j]+1>temp)
          temp=L[j]+1;
    }
    if (temp>max)
      max=temp;
    L.push_back(temp);
  }
  return max;
}

bool testSubsequence(std::vector<s_t>& ends, s_t l, float alpha) {
  std::vector<s_t> indices;
  s_t last = ends[ends.size()-1];
  phi();
  for (s_t i=0;i<l;i++) {
    indices.push_back(rand()%(last));
  }
  phi();
  std::sort(indices.begin(),indices.end());
  phi();
  std::vector<store_t> nums(l);
  for (unsigned int i=0;i<l;i++) {
    int target = findTarget(ends,indices[i]);
    //    std::cout<<target<<' '<<indices[i]<<std::endl;
    long long int num = indices[i];
    int err = MPI_Send(&num,1,MPI_LONG_LONG,target,0,MPI_COMM_WORLD);
    //    std::cout<<err<<std::endl;
    MPI_Recv(&(nums[i]),1,MPI_UNSIGNED_SHORT,target,MPI_ANY_TAG,MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    phi();
  }
  phi();
  s_t L = myincreasingsseq(nums);
  phi();
  return L>=ceil(alpha*l);
}


int main(int argc,char* argv[]) {
  MPI_Init(&argc,&argv);
  int rank,size;
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  srand(time(NULL));
  assert(argc>=3);

  //Input
  s_t N = pow(2,atoi(argv[1]));
  double alpha_in = atof(argv[2]);
  s_t N_sorted = ceil(alpha_in*N);
  s_t N_spernode = N_sorted/(size-1)+1;
  s_t N_unsorted = N-N_sorted;

  //List of integers on part (none on part 0)
  std::vector<store_t> numbers;

  //Create list of unsorted elements
  MTRand rand;
  if (!rank) {

    s_t** indices = new s_t*[size-1];
    std::vector<s_t> sizes(size-1,0);
    for (int i=0;i<size-1;i++) {
      indices[i] = new s_t[(int)(N_unsorted/(size-1)*2)];
    }

    for (s_t i=0;i<N_unsorted;i++) {
      s_t num = floor(rand.rand53()*(N_sorted+1));
      int target = num/N_spernode;
      assert(target<size-1);
      sizes[target]++;
      assert(sizes[target]<=N_unsorted/(size-1)*1.3);
      indices[target][sizes[target]-1]=num;
    }
    std::vector<MPI_Request> reqs(3*(size-1));
    std::vector<s_t> ends(size-1);
    ends[0] = N_spernode+sizes[0];
    for (int i=0;i<size-1;i++) {
      if (i!=0)
        ends[i]=ends[i-1]+sizes[i]+N_spernode;
      MPI_Isend(&sizes[i],1,MPI_UNSIGNED_LONG_LONG,i+1,0,MPI_COMM_WORLD,&(reqs[2*i]));
      MPI_Isend(&(indices[i][0]),sizes[i],MPI_UNSIGNED_LONG_LONG,i+1,2,MPI_COMM_WORLD,&(reqs[2*i+2]));
    }
    for (int i=0;i<size-1;i++)
      delete [] indices[i];
    delete [] indices;


  
    //continuously run tests until finished
    float alpha;
    unsigned int l;
    std::cout<<"Input l(0 to end): ";
    std::cin>>l;
    while (l!=0) {
      std::cout<<"Input alpha: ";
      std::cin>>alpha;
    
      //Calculate p*
      double pstar=0;
      std::clock_t start_ps = std::clock();
      for (s_t i =ceil(alpha*l);i<=l;i++) {
        pstar+=nChoosek(l,i)*pow(alpha,i)*pow(1-alpha,l-i);
      }
      std::cout<<"p* = "<<pstar<<'\n';
      std::cout<<"Computing p* took "<<(std::clock()-start_ps)/(double)CLOCKS_PER_SEC
               <<"seconds\n";

      //Run the test
      std::clock_t start_running = std::clock();
      unsigned int m = 100000;
      unsigned int worked=0;
      phi();
      for (unsigned int i=0;i<m;i++) {
        std::cout<<"Starting "<<i<<'\n';
        worked+=testSubsequence(ends,l,alpha);
        phi();
      }
      double p = worked*1.0/m;
      std::cout<<"p = "<<p<<'\n';
      std::cout<<"p-p* = "<<p-pstar<<'\n';
      if (p>pstar) 
        std::cout<<"YES\n";
      else
        std::cout<<"NO\n";
      std::cout<<"Running algorithm took "<<(std::clock()-start_running)/(double)CLOCKS_PER_SEC<<"seconds\n";
  
      //refresh for another run
      std::cout<<"Input l(0 to end): ";
      std::cin>>l;
    }

    for (int i=1;i<size;i++){
      long long int n1=-1;
      MPI_Send(&n1,1,MPI_LONG_LONG,i,0,MPI_COMM_WORLD);
    }
  
  }
  else {
    s_t size;
    MPI_Recv(&size,1,MPI_UNSIGNED_LONG_LONG,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    s_t* indices = new s_t[size];
    MPI_Recv(indices,size,MPI_UNSIGNED_LONG_LONG,0,2,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    std::sort(indices,indices+size);
    
    //Create alpha_in sorted list
    s_t cur=0;
    for (s_t i=(rank-1)*N_spernode;i<rank*N_spernode;i++) {
      while (cur<size&&indices[cur]<i) {
        numbers.push_back((store_t)rand.randInt(log(N_sorted)+1));
        cur++;
      }
      numbers.push_back((int)log(i+1));
    }
    while (cur<size) {
      numbers.push_back((store_t)rand.randInt(log(N_sorted)+1));
      cur++;
    }
    delete [] indices;

    while (true) {
      long long int num=0;
      int err =MPI_Recv(&num,1,MPI_LONG_LONG,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      //      std::cout<<rank<<": "<<err<<std::endl;
      //      std::cout<<num<<std::endl;
      if (num==-1)
        break;
      if (num>=(long long int)numbers.size())
        printf("%lld has been requested off of part %d but size is %lu\n",num,rank,numbers.size());
      phi();
      MPI_Send(&(numbers[num]),1,MPI_UNSIGNED_SHORT,0,0,MPI_COMM_WORLD);
    }
  }
  MPI_Finalize();
  return 0;
}
