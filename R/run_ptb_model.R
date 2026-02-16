#' Wrapper function to run the Para TB model
#'
#' @param runsNb number of repetitions (default=1L)
#' @param calfExposure calf rearing improvement is defined as a reduced exposure to the general environment by varying parameter from 1.0 to 0.35 (default=1.0)
#' @param cullingRateIh culling rate of detected Ih animals (default=1.0/26.0)
#' @param testSensitivityItIl test sensitivity of low positive animals. (default=0.15)
#' @param testSensitivityIm test sensitivity of moderately positive animals. (default=0.47)
#' @param testSensitivityIh test sensitivity of highly positive animals. (default=0.71)
#' @param testSpecificity test specificity. (default=1.0)
#' @param startGrazing Grazing start week (from 0 to 51, default=14L, beginning of April)
#' @param endGrazing Grazing end week (from 0 to 51, default=46L, mid November)
#' @param ageAtWeaning From this age, in terms of number of weeks, the animal is weaned (default=10L)
#' @param ageAtGrazing From this age, in terms of number of weeks, the animal can go outside during grazing period (default=26L)
#' @param ageYoungHeifer From this age, in terms of number of weeks, the animal is considered to be a young heifer (default=52L, one year old)
#' @param ageHeifer From this age, in terms of number of weeks, the animal is considered to be a heifer, starts reproduction (default=91L)
#' @param ageAtFirstCalving From this age, in terms of number of weeks, the animal is considered to be a cow, calves for the first time (default=130L)
#' @param noInfection all herds will be initialized without infected animals, so no PTB spread (default=FALSE)
#' @param InitialInfection if not empty, then load initial 'infection' from this DF/tibble: 1 line = 1 infected herd with id, nbInfectedAnimals, prevalence and repetitionNum refering to a line in 'initCondFileName' (tibble/DF, default=0 rows)
#' @param BirthFemaleEvents a tibble/DF - see ?BirthFemaleEvents
#' @param CullingRates a tibble/DF - see ?CullingRates
#' @param Headcounts a tibble/DF - see ?Headcounts
#' @param Network a tibble/DF - see ?Network
#' @param seed the random number seed to use
#'
#' @import PTBinraeR
#' @importFrom readr write_tsv read_tsv
#' @importFrom rlang set_names
#' @importFrom methods new
#'
#' @description
#' This is a wrapper for the INRAE PTB model.  Note that (currently) this is a very thin wrapper; all RNG are C++ i.e. set.seed will have no effect.  Also there is no checking for interrupt signals...
#'
#' @returns a list of tibbles corresponding to the files output by the model
#'
#' @export
run_ptb_model <- function(runsNb = 1L, calfExposure = 1.0, cullingRateIh = 1.0/26.0, testSensitivityItIl = 0.15, testSensitivityIm = 0.47, testSensitivityIh = 0.71, testSpecificity = 1.0, startGrazing = 14L, endGrazing = 46L, ageAtWeaning = 10L, ageAtGrazing = 26L, ageYoungHeifer = 52L, ageHeifer = 91L, ageAtFirstCalving = 130L, noInfection = FALSE, InitialInfection = PTBinraeR::InitialInfection, BirthFemaleEvents = PTBinraeR::BirthFemaleEvents, CullingRates = PTBinraeR::CullingRates, Headcounts = PTBinraeR::Headcounts, Network = PTBinraeR::Network, seed = sample(.Machine$integer.max, 1)){

  # TODO: argument checking (using checkmate package)

  # Dirty hack to require singleton-ness:
  gc(); if(havePtbModel()) stop("You can only have 1 PTB model at a time")

  tmpdir <- tempfile(pattern="ptb_model_files", tmpdir = tempdir(check=TRUE))
  dir.create(tmpdir)
  on.exit({
    unlink(tmpdir, recursive = TRUE)
  })

  in_out_dir <- file.path(tmpdir, "in_out_dir/")
  dir.create(in_out_dir)

  # Note: the initInPath MUST be named like this for some reason:
  initInPath <- file.path(in_out_dir, "selectedInitScenarioForPrev_1to90.csv")
  write_tsv(InitialInfection, initInPath, col_names=FALSE)

  model <- new(PtbModel)

  # void setParameters( int const runsNb, double const calfExposure, double const cullingRateIh,
  #                     int const seed, double const testSensitivityItIl, double const testSensitivityIm,
  #                     double const testSensitivityIh, double const testSpecificity,
  #                     int const startGrazing, int const endGrazing,
  #                     double const ageAtWeaning, double const ageAtGrazing,
  #                     double const ageYoungHeifer, double const ageHeifer,
  #                     double const ageAtFirstCalving, bool const noInfection,
  #                     std::string const initIn, std::string const resultsPath
  # )
  model$setParameters(runsNb, calfExposure, cullingRateIh, seed,
                     testSensitivityItIl, testSensitivityIm,
                     testSensitivityIh, testSpecificity, startGrazing, endGrazing,
                     ageAtWeaning, ageAtGrazing, ageYoungHeifer, ageHeifer,
                     ageAtFirstCalving, noInfection, initInPath, in_out_dir)

  write_tsv(BirthFemaleEvents, file.path(in_out_dir, "BirthFemaleEvents_withId.csv"), col_names=FALSE)
  write_tsv(CullingRates, file.path(in_out_dir, "CullingRates_withId.csv"), col_names=FALSE)
  write_tsv(Headcounts, file.path(in_out_dir, "Headcounts_withId.csv"), col_names=FALSE)
  write_tsv(Network, file.path(in_out_dir, "Network_withId_and_breedType_coderace.csv"), col_names=FALSE)

  model$loadFiles()

  exfiles <- list.files(in_out_dir)

  model$runModel()

  ff <- list.files(in_out_dir)
  ff[!ff %in% exfiles] |>
    set_names() |>
    lapply(\(x) read_tsv(file.path(in_out_dir, x), col_names=FALSE, show_col_types = FALSE)) ->
    rv

  return(rv)
}
