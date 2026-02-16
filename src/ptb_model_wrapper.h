#ifndef RUN_PTB_MODEL_H_
#define RUN_PTB_MODEL_H_

// Links to local installation if both git repos are in the same directory:
#if defined __has_include
#  if __has_include ("../../ptb-between-herd-model-public/PTBinraeR/inst/include/para_tb_model.h")
#    include "../../ptb-between-herd-model-public/PTBinraeR/inst/include/para_tb_model.h"
#  endif
#endif
// NOTE: comment out the above if you want to compile against the release version of the underlying R package

// Linking to PTBinraeR package (header guards will filter it out if above is used instead):
#include <para_tb_model.h>

#include <Rcpp.h>

template <auto s_cts>
class PtbModelWrapper
{
private:
  
  para_tb_model::ParametersT<s_cts>& m_params = para_tb_model::ParametersT<s_cts>::getInstance();
  para_tb_model::ModelT<s_cts> m_model {};
  
public:
  
  // Dirty hack to make sure we only have 1 instance at a time:
  static int s_instances;
  
  PtbModelWrapper()
  {
    if (s_instances > 0) Rcpp::stop("We can only have 1 instance of the PTB model at a time");
    s_instances++;    
  }
  
  void setParameters( int const runsNb, double const calfExposure, double const cullingRateIh, 
                      int const seed, double const testSensitivityItIl, double const testSensitivityIm,
                      double const testSensitivityIh, double const testSpecificity,
                      int const startGrazing, int const endGrazing,
                      double const ageAtWeaning, double const ageAtGrazing,
                      double const ageYoungHeifer, double const ageHeifer,
                      double const ageAtFirstCalving, bool const noInfection, 
                      std::string const initIn, std::string const in_out_dir
                    )
  {
    
    m_params.runsNb = runsNb;
    m_params.dontInfect = noInfection;
    m_params.defaultCalfExpo = calfExposure;
    
    if (cullingRateIh > 0.0384615){  //6 months => 1/(52/2) = 0.0384615
        m_params.areDetectedIhCulledEarlier = true;
        m_params.cullingProbaOfDetectedIh = 1.0 - std::exp(-cullingRateIh);   //1 month => 1/(52/12) = 0.230769
    }
    
    m_params.dataPath = in_out_dir;
    m_params.resultsPath = in_out_dir;
    
    m_params.isRewiringAllowed = false;
    
    if (seed == 0){
        m_params.gen.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    } else {
        m_params.gen.seed(seed);
    }
    
    m_params._testSensitivityIt = testSensitivityItIl;
    m_params._testSensitivityIl = testSensitivityIm;
    m_params._testSensitivityIm = testSensitivityIh;
    m_params._testSensitivityIh = testSpecificity;
    m_params._startGrazing = startGrazing;
    m_params._endGrazing = endGrazing;
    m_params._ageWeaning = ageAtWeaning;
    m_params._ageGrazing = ageAtGrazing;
    m_params._ageYoungHeifer = ageYoungHeifer;
    m_params._ageHeifer = ageHeifer;
    m_params._ageFirstCalving = ageAtFirstCalving;
    
    if (m_params.dontInfect){
        m_params.propOfHerdsToInfect = 0;
    } else { //then option '-p' or '-i' or '-d' will be used
        m_params.vHerdPropPerStatus.clear();
    }
    if (initIn != ""){
        m_params.doLoadingOfInitialInfection = true;
        m_params.initInFile = initIn;
    }
    
    m_params.updateAfterSetting();

  }
  
  void loadFiles()
  {
    m_model.loadDemography();
    m_model.loadMovements();
    if (m_params.doLoadingOfInitialInfection){
        m_model.loadInitialInfection();
    }
    m_model.loadInitPrevMatrix();
  }
  
  void runModel()
  {
    m_model.run();
  }
  
  // Obey the Rule of Five
  PtbModelWrapper(const PtbModelWrapper& other) = delete;
  PtbModelWrapper& operator=(const PtbModelWrapper& other) = delete;
  PtbModelWrapper(PtbModelWrapper&& other) = delete;
  PtbModelWrapper& operator=(PtbModelWrapper&& other) = delete;
  // NOTE: this class is currently not safe to copy - moving should be OK, but we don't need to
    
  ~PtbModelWrapper()
  {
    para_tb_model::MetapopT<s_cts>::kill();
    para_tb_model::ParametersT<s_cts>::kill();
    s_instances--;
  }
  
};

#endif // RUN_PTB_MODEL_H_
