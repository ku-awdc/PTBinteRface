#include <Rcpp.h>

#include "ptb_model_wrapper.h"

constexpr struct
{
  bool debug = true;
} cts;

using PtbModel = PtbModelWrapper<cts>;

// Dirty hack needed:
template<> int PtbModel::s_instances = 0;
bool havePtbModel() { return PtbModel::s_instances > 0; }

RCPP_MODULE(PTBinteRface_module){

	using namespace Rcpp;
  
  function("havePtbModel", &havePtbModel);
    
  class_<PtbModel>("PtbModel")
    .constructor()
    .method("setParameters", &PtbModel::setParameters)
    .method("loadFiles", &PtbModel::loadFiles)
    .method("runModel", &PtbModel::runModel)
  ;

}
