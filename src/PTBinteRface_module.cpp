#include <Rcpp.h>
#include <para_tb_model.h>

int test()
{
  return 1;
}

RCPP_MODULE(PTBinteRface_module){

	using namespace Rcpp;

  function("test", &test);
  
}
