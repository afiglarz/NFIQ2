// Includes the core API calls to compute NFIQ2 Scores
#include <nfiq2.hpp>
// Include the API calls to compute NFIQ2 Quality Features
#include <nfiq2_qualityfeatures.hpp>
// OpenCV Matrix and Image parsing headers
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>

#include <iostream>
#include <memory>

void
printUsage()
{
	std::cout
	    << "example_api: usage: example_api [-h] modelInfoFile fingerPrintImage\n";
}

void
printHelp()
{
	std::cout
	    << "NFIQ 2 API Example\n\nThis is a sample program that "
	       "shows how to use the NFIQ 2 API on an image.\n\nThis command line "
	       "tool takes two arguments.\nThe first is the path to a NFIQ 2 "
	       "RandomForest model information file.\nThe second is the path to a "
	       "single fingerprint image.\n\nPlease provide arguments to the binary "
	       "in the designated order.\nEx: $ example_api nist_plain_tir.txt "
	       "fingerImage01.pgm\n";
}

int
main(int argc, char **argv)
{
	const std::string helpStr { "-h" };

	if (argc == 2 && helpStr.compare(argv[1]) == 0) {
		printHelp();
		return (EXIT_FAILURE);
	}

	if (argc != 3) {
		printUsage();
		return (EXIT_FAILURE);
	}

	// Note: NFIQ 2 only operates on images captured at a resolution of
	// 500 PPI. Unfortunately, the images contained within this repository
	// are encoded in PGM format, which does not encode resolution
	// information. ALWAYS make use of image libraries to decode image
	// resolution information and convert to PPI to avoid erroneous NFIQ 2
	// results.
	static const uint16_t PPI = 500;

	// To compute an NFIQ 2 score, you must load the RF model you wish to
	// use This segment loads the model information file that contains data
	// about the RF model.
	NFIQ::ModelInfo modelInfoObj {};
	try {
		modelInfoObj = NFIQ::ModelInfo(argv[1]);
	} catch (...) {
		std::cout
		    << "Could not parse model info file. "
		       "Ensure it is the first argument on the cmd line\n";
		printUsage();
		return (EXIT_FAILURE);
	}

	// This segment loads the model into memory so that it can be used to
	// generate a NFIQ 2 score.
	std::unique_ptr<NFIQ::NFIQ2Algorithm> model {};
	try {
		model.reset(new NFIQ::NFIQ2Algorithm(modelInfoObj));
	} catch (...) {
		std::cout
		    << "Could not initialize model from model info file\n";
		return (EXIT_FAILURE);
	}

	// Thos segment uses OpenCV to parse the fingerprint image passed
	// in on the command line.
	cv::Mat imgMat {};
	try {
		imgMat = cv::imread(argv[2], cv::IMREAD_GRAYSCALE);
	} catch (...) {
		std::cout
		    << "Could not parse image file. Ensure it is the second "
		       "argument on the cmd line\n";
		printUsage();
		return (EXIT_FAILURE);
	}

	// This constructs a FingerprintImageData object that stores the
	// relevant image information NFIQ 2 needs to compute a score.
	NFIQ::FingerprintImageData rawImage = NFIQ::FingerprintImageData(
	    imgMat.data, static_cast<uint32_t>(imgMat.total()),
	    static_cast<uint32_t>(imgMat.cols),
	    static_cast<uint32_t>(imgMat.rows), 0, PPI);

	// This segment calls the API and generates a NFIQ2Results object.
	// This contains all of the scores generated for an image by the
	// algorithm.
	NFIQ::NFIQ2Results results {};
	try {
		results = (*model).computeQualityFeaturesAndScore(rawImage);
	} catch (...) {
		std::cout << "Error in calculating quality score\n";
		return (EXIT_FAILURE);
	}

	// The output generated by this sample app is detailed in the
	// README file. The following code iterates through
	// the NFIQ2Results object, extracts scores, and prints them to
	// stdout.
	std::cout << "QualityScore: " << results.getScore() << "\n";

	// Actionable Feedback
	std::vector<std::string> actionableHeaders =
	    NFIQ::QualityFeatures::getAllActionableIdentifiers();
	std::vector<NFIQ::ActionableQualityFeedback> actionableResults =
	    results.getActionableQualityFeedback();

	for (size_t i = 0; i < actionableHeaders.size(); i++) {
		std::cout << actionableHeaders.at(i) << ": "
			  << actionableResults.at(i).actionableQualityValue
			  << "\n";
	}

	// Quality Feature Scores
	std::vector<std::string> featureHeaders =
	    NFIQ::QualityFeatures::getAllQualityFeatureIDs();
	std::vector<NFIQ::QualityFeatureData> featureResults =
	    results.getQualityFeatures();

	for (size_t i = 0; i < featureHeaders.size(); i++) {
		std::cout << featureHeaders.at(i) << ": "
			  << featureResults.at(i).featureDataDouble << "\n";
	}

	// Quality Feature Speeds
	std::vector<std::string> speedHeaders =
	    NFIQ::QualityFeatures::getAllSpeedFeatureGroups();
	std::vector<NFIQ::QualityFeatureSpeed> speedResults =
	    results.getQualityFeatureSpeed();

	for (size_t i = 0; i < speedHeaders.size(); i++) {
		std::cout << speedHeaders.at(i) << ": "
			  << speedResults.at(i).featureSpeed << "\n";
	}

	// Image Processed
	return (EXIT_SUCCESS);
}
