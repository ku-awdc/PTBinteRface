#include <Rcpp.h>
#include <para_tb_model.h>

int runPTBmodel()
{
  /* content of main.cpp from underlying package
  
    TCLAP::CmdLine cmd("Simulate bovine paratuberculosis (PTB) spread between dairy herds in a region. It is data-driven and mechanistic.\nSee README for more information.", ' ', "0.1");
    TCLAP::ValueArg<int> iRunsNbArg("r", "runsNb", "number of repetitions (default=1)", false, 1, "int");
    //years nb?
    TCLAP::ValueArg<float> iCalfExposureArg("e", "calfExposure", "calf rearing improvement is defined as a reduced exposure to the general environment by varying parameter from 1.0 to 0.35 (default=1.0)", false, 1.0, "float");
    TCLAP::ValueArg<float> iCullingRateIhArg("k", "cullingRateIh", "culling rate of detected Ih animals (default=1/26.)", false, 0.0384615, "float");
    //same for Im?
    //+ prop?
    TCLAP::ValueArg<std::string> iOutDirectoryPathArg("o", "outDirectoryPath", "relative folder path to write all output files (default='../results/')", false, "../results/", "string");
    TCLAP::ValueArg<std::string> iInitInFilePathArg("i", "initInFilePath", "if not empty, then load initial 'infection' from this file: 1 line = 1 infected herd with id, nbInfectedAnimals, prevalence and repetitionNum refering to a line in 'initCondFileName' (default='')", false, "", "string");
    TCLAP::ValueArg<float> iTestSensitivityItIlArg("", "testSensitivityItIl", "test sensitivity of low positive animals. (default=0.15)", false, 0.15, "float");
    TCLAP::ValueArg<float> iTestSensitivityImArg("", "testSensitivityIm", "test sensitivity of moderately positive animals. (default=0.47)", false, 0.47, "float");
    TCLAP::ValueArg<float> iTestSensitivityIhArg("", "testSensitivityIh", "test sensitivity of highly positive animals. (default=0.71)", false, 0.71, "float");
    TCLAP::ValueArg<float> iTestSpecificityArg("", "testSpecificity", "test specificity. (default=1.0)", false, 1.0, "float");
    //test frequency
    //TCLAP::ValueArg<float> iProbaToPurchaseSArg("v", "probaToPurchaseS", "probability to purchase a susceptible animal for AAA herds (used with herd history (see -q), default=1.0)", false, 1.0, "float");
    //cmd.add(iProbaToPurchaseSArg);
   // TCLAP::SwitchArg iUsePurchaseProba("f", "usePurchaseProba", "a fixed probability to purchase a susceptible animal will be used (see -v), instead of the prevalence in the source herd (used with herd history)", cmd, false);
    TCLAP::ValueArg<float> iStartGrazingArg("", "startGrazing", "Grazing start week (from 0 to 51, default=14, beginning of April)", false, 14, "int");
    TCLAP::ValueArg<float> iEndGrazingArg("", "endGrazing", "Grazing end week (from 0 to 51, default=46, mid November)", false, 46, "int");
    TCLAP::ValueArg<float> iAgeAtWeaningArg("", "ageAtWeaning", "From this age, in terms of number of weeks, the animal is weaned (default=10)", false, 10, "int");
    TCLAP::ValueArg<float> iAgeAtGrazingArg("", "ageAtGrazing", "From this age, in terms of number of weeks, the animal can go outside during grazing period (default=26)", false, 26, "int");
    TCLAP::ValueArg<float> iAgeYoungHeiferArg("", "ageYoungHeifer", "From this age, in terms of number of weeks, the animal is considered to be a young heifer (default=52, one year old)", false, 52, "int");
    TCLAP::ValueArg<float> iAgeHeiferArg("", "ageHeifer", "From this age, in terms of number of weeks, the animal is considered to be a heifer, starts reproduction (default=91)", false, 91, "int");
    TCLAP::ValueArg<float> iAgeAtFirstCalvingArg("", "ageAtFirstCalving", "From this age, in terms of number of weeks, the animal is considered to be a cow, calves for the first time (default=130)", false, 130, "int");
    cmd.add(iAgeAtWeaningArg);
    cmd.add(iAgeAtGrazingArg);
    cmd.add(iAgeYoungHeiferArg);
    cmd.add(iAgeHeiferArg);
    cmd.add(iAgeAtFirstCalvingArg);
    cmd.add(iStartGrazingArg);
    cmd.add(iEndGrazingArg);
    cmd.add(iTestSensitivityItIlArg);
    cmd.add(iTestSensitivityImArg);
    cmd.add(iTestSensitivityIhArg);
    cmd.add(iTestSpecificityArg);
    cmd.add(iInitInFilePathArg);
    cmd.add(iOutDirectoryPathArg);
    cmd.add(iCullingRateIhArg);
    cmd.add(iCalfExposureArg);
    TCLAP::SwitchArg iNoInfection("n", "noInfection", "all herds will be initialized without infected animals, so no PTB spread", cmd, false);
    cmd.add(iRunsNbArg);
    cmd.parse(argc, argv);

	ParametersT<false>& iParams = ParametersT<false>::getInstance();
    iParams.runsNb = iRunsNbArg.getValue();
    iParams.dontInfect = iNoInfection.getValue();
    iParams.defaultCalfExpo = iCalfExposureArg.getValue();
    if (iCullingRateIhArg.getValue() > 0.0384615){  //6 months => 1/(52/2) = 0.0384615
        iParams.areDetectedIhCulledEarlier = true;
        iParams.cullingProbaOfDetectedIh = 1 - std::exp(-(iCullingRateIhArg.getValue()));   //1 month => 1/(52/12) = 0.230769
    }
    iParams.resultsPath = iOutDirectoryPathArg.getValue();
    iParams.isRewiringAllowed = false;
//    iParams.usePurchaseProba = iUsePurchaseProba.getValue();
//    iParams.probaToPurchaseS = iProbaToPurchaseSArg.getValue();
    int seed = 0;
    if (seed == 0){
        iParams.gen.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    } else {
        iParams.gen.seed(seed);
    }

    iParams._testSensitivityIt = iTestSensitivityItIlArg.getValue();
    iParams._testSensitivityIl = iTestSensitivityItIlArg.getValue();
    iParams._testSensitivityIm = iTestSensitivityImArg.getValue();
    iParams._testSensitivityIh = iTestSensitivityIhArg.getValue();
    iParams._startGrazing = iStartGrazingArg.getValue();
    iParams._endGrazing = iEndGrazingArg.getValue();
    iParams._ageWeaning = iAgeAtWeaningArg.getValue();
    iParams._ageGrazing = iAgeAtGrazingArg.getValue();
    iParams._ageYoungHeifer = iAgeYoungHeiferArg.getValue();
    iParams._ageHeifer = iAgeHeiferArg.getValue();
    iParams._ageFirstCalving = iAgeAtFirstCalvingArg.getValue();

    if (iParams.dontInfect){
        iParams.propOfHerdsToInfect = 0;
    } else { //then option '-p' or '-i' or '-d' will be used
        iParams.vHerdPropPerStatus.clear();
    }
    if (iInitInFilePathArg.getValue() != ""){
        iParams.doLoadingOfInitialInfection = true;
        iParams.initInFile = iInitInFilePathArg.getValue();
    }
    iParams.updateAfterSetting();

    ModelT<false> iModel = ModelT<false>();
    iModel.loadDemography();
    iModel.loadMovements();
    if (iParams.doLoadingOfInitialInfection){
        iModel.loadInitialInfection();
    }
    iModel.loadInitPrevMatrix();
    iModel.run();

    MetapopT<false>::kill();
    ParametersT<false>::kill();
  */

    return 1;
  
}

RCPP_MODULE(PTBinteRface_module){

	using namespace Rcpp;

  function("runPTBmodel", &runPTBmodel);
  
}
