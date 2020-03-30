#include <RcppArmadilloExtensions/sample.h>
#include <RcppParallel.h>
using namespace arma;

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
Rcpp::NumericMatrix parallel_random_matrix(const int m,const int n,const int seed){
  Rcpp::NumericMatrix outputRcpp(m,n);
  RandomFill randomFill(outputRcpp,seed);
  RcppParallel::parallelFor(0,n,randomFill);
  return outputRcpp;
}

