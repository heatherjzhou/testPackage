// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <RcppArmadillo.h>
#include <Rcpp.h>

using namespace Rcpp;

// myFastLM
arma::vec myFastLM(const arma::mat X, const arma::vec y);
RcppExport SEXP _testPackage_myFastLM(SEXP XSEXP, SEXP ySEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const arma::mat >::type X(XSEXP);
    Rcpp::traits::input_parameter< const arma::vec >::type y(ySEXP);
    rcpp_result_gen = Rcpp::wrap(myFastLM(X, y));
    return rcpp_result_gen;
END_RCPP
}
// parallel_random_matrix
Rcpp::NumericMatrix parallel_random_matrix(const int m, const int n, const int seed);
RcppExport SEXP _testPackage_parallel_random_matrix(SEXP mSEXP, SEXP nSEXP, SEXP seedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const int >::type m(mSEXP);
    Rcpp::traits::input_parameter< const int >::type n(nSEXP);
    Rcpp::traits::input_parameter< const int >::type seed(seedSEXP);
    rcpp_result_gen = Rcpp::wrap(parallel_random_matrix(m, n, seed));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_testPackage_myFastLM", (DL_FUNC) &_testPackage_myFastLM, 2},
    {"_testPackage_parallel_random_matrix", (DL_FUNC) &_testPackage_parallel_random_matrix, 3},
    {NULL, NULL, 0}
};

RcppExport void R_init_testPackage(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
