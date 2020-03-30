#include <RcppArmadilloExtensions/sample.h>
#include <RcppParallel.h>
using namespace arma;

#include <convert_seed.h> //For dqrng::convert_seed
#include <R_randgen.h> //For dqrng::R_random_int

vec generateVector(const int m){
  mat noiseMatrix=randn(m,2);

  vec sampleSpace=linspace(1,4,4); //Vector of length 4, the values being 1 through 4
  vec noiseVector=Rcpp::RcppArmadillo::sample(sampleSpace,m,true);

  vec toReturn=noiseMatrix.col(0)+noiseMatrix.col(1)+noiseVector;
  return toReturn;
}

struct RandomFill:public RcppParallel::Worker{
  RcppParallel::RMatrix<double> outputRM;
  const int m;
  uint64_t seed;

  RandomFill(Rcpp::NumericMatrix outputRcpp,const uint64_t seed)
    :outputRM(outputRcpp),m(outputRcpp.nrow()),seed(seed){};

  void operator()(std::size_t begin,std::size_t end){
    for (std::size_t colIndex=begin;colIndex<end;colIndex++) {
      vec newColumn=generateVector(m);
      for (int obsIndex=0;obsIndex<m;obsIndex++){ //Fill the column in output.
        outputRM(obsIndex,colIndex)=newColumn(obsIndex);
      }
    }
  }
};

//[[Rcpp::export]]
Rcpp::NumericMatrix parallel_random_matrix(const int m,const int n,Rcpp::Nullable<Rcpp::IntegerVector> seed=R_NilValue){
  uint64_t _seed;
  if (seed.isNotNull()){
    _seed=dqrng::convert_seed<uint64_t>(seed.as());
  }
  else{ //Get a seed from R's RNG in case the user did not provide one
    _seed=dqrng::convert_seed<uint64_t>(Rcpp::IntegerVector(2,dqrng::R_random_int));
  }

  Rcpp::NumericMatrix outputRcpp(m,n);
  RandomFill randomFill(outputRcpp,_seed);
  RcppParallel::parallelFor(0,n,randomFill);
  return outputRcpp;
}

