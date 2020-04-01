#include <RcppArmadillo.h>
#include <RcppParallel.h>
using namespace arma;

#include <convert_seed.h> //For dqrng::convert_seed
#include <R_randgen.h> //For dqrng::R_random_int
#include <dqrng_distribution.h> //For dqrng::rng64_t, dqrng::generator, dqrng::xoroshiro128plus, and dqrng::normal_distribution

vec generateVector(const int n,dqrng::rng64_t rng){
  mat noiseMatrix(n,2);
  //Draw each entry from normal(0,1)
  dqrng::normal_distribution normal(0,1);
  noiseMatrix.imbue([&](){return normal(*rng);});

  vec noiseVector(n);
  //Draw each entry from (1,2,3,4) with replacement (equal probabilities)
  noiseVector.imbue([&](){return (*rng)(uint32_t(4))+1;});
  //cout<<noiseVector<<endl; //4.0000, 3.0000, 1.0000, 2.0000, 2.0000, ...

  vec toReturn=noiseMatrix.col(0)+noiseMatrix.col(1)+noiseVector;
  return toReturn;
}

struct RandomFill:public RcppParallel::Worker{
  RcppParallel::RMatrix<double> outputRM;
  const int m;
  const uint64_t seed;

  RandomFill(Rcpp::NumericMatrix outputRcpp,const uint64_t seed)
    :outputRM(outputRcpp),m(outputRcpp.nrow()),seed(seed){};

  void operator()(std::size_t begin,std::size_t end){
    dqrng::rng64_t rng=dqrng::generator<dqrng::xoroshiro128plus>(seed);
    rng->seed(seed,end);
    for (std::size_t colIndex=begin;colIndex<end;colIndex++) {
      vec newColumn=generateVector(m,rng);
      for (int obsIndex=0;obsIndex<m;obsIndex++){ //Fill the column in output.
        outputRM(obsIndex,colIndex)=newColumn(obsIndex);
      }
    }
  }
};

//[[Rcpp::export]]
Rcpp::NumericMatrix parallel_random_matrix(const int m,const int n,Rcpp::Nullable<Rcpp::IntegerVector> seedRaw){
  uint64_t seed;
  if (seedRaw.isNotNull()){
    seed=dqrng::convert_seed<uint64_t>(seedRaw.as()); //This stores the value of seedRaw in seed. Simply using "seed=seedRaw;" doesn't work.
  }
  else{ //Generate a seed if the user did not provide one
    seed=dqrng::convert_seed<uint64_t>(Rcpp::IntegerVector(2,dqrng::R_random_int));
  }

  Rcpp::NumericMatrix outputRcpp(m,n);
  RandomFill randomFill(outputRcpp,seed);
  RcppParallel::parallelFor(0,n,randomFill);
  return outputRcpp;
}

