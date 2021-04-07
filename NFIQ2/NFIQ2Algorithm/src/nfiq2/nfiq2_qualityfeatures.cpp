#include "nfiq2_qualityfeatures_impl.h"

#include <list>
#include <string>
#include <vector>

std::vector<std::string>
NFIQ::QualityFeatures::getAllActionableIdentifiers()
{
	return NFIQ::QualityFeatures::Impl::getAllActionableIdentifiers();
}

std::vector<std::string>
NFIQ::QualityFeatures::getAllQualityFeatureIDs()
{
	return NFIQ::QualityFeatures::Impl::getAllQualityFeatureIDs();
}

std::vector<std::string>
NFIQ::QualityFeatures::getAllSpeedFeatureGroups()
{
	return NFIQ::QualityFeatures::Impl::getAllSpeedFeatureGroups();
}

std::vector<NFIQ::QualityFeatureData>
NFIQ::QualityFeatures::computeQualityFeatures(
    const NFIQ::FingerprintImageData &rawImage, bool bComputeActionableQuality,
    std::vector<NFIQ::ActionableQualityFeedback> &actionableQuality,
    bool bOutputSpeed, std::vector<NFIQ::QualityFeatureSpeed> &speedValues)
{
	return NFIQ::QualityFeatures::Impl::computeQualityFeatures(rawImage,
	    bComputeActionableQuality, actionableQuality, bOutputSpeed,
	    speedValues);
}

std::vector<std::shared_ptr<NFIQ::QualityFeatures::BaseFeature>>
NFIQ::QualityFeatures::computeQualityFeatureModules(
    const NFIQ::FingerprintImageData &rawImage)
{
	return NFIQ::QualityFeatures::Impl::computeQualityFeatureModules(
	    rawImage);
}

std::vector<NFIQ::ActionableQualityFeedback>
NFIQ::QualityFeatures::extractActionableQualityFeedback(
    const std::vector<std::shared_ptr<NFIQ::QualityFeatures::BaseFeature>>
	&modules)
{
	return NFIQ::QualityFeatures::Impl::extractActionableQualityFeedback(
	    modules);
}
