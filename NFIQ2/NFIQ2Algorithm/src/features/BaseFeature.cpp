#include <features/BaseFeature.h>
#include <nfiq2_interfacedefinitions.hpp>

#include <vector>

NFIQ::QualityFeatures::BaseFeature::BaseFeature() = default;

NFIQ::QualityFeatures::BaseFeature::~BaseFeature() = default;

NFIQ::QualityFeatureSpeed
NFIQ::QualityFeatures::BaseFeature::getSpeed() const
{
	return this->speedValue;
}

void
NFIQ::QualityFeatures::BaseFeature::setSpeed(
    const NFIQ::QualityFeatureSpeed &speedFeature)
{
	this->speedValue = speedFeature;
}
