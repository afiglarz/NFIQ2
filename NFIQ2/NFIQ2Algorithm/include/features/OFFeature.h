#ifndef OF_FEATURE_H
#define OF_FEATURE_H

#include <features/BaseFeature.h>
#include <nfiq2_fingerprintimagedata.hpp>
#include <nfiq2_interfacedefinitions.hpp>
#include <stdio.h>
#include <stdlib.h>

#include <list>
#include <string>
#include <vector>

/**
******************************************************************************
* @class OFFeature
* @brief NFIQ2 Orientation Flow Quality Feature
******************************************************************************/

namespace NFIQ { namespace QualityFeatures {

static double OFHISTLIMITS[9] = { 1.715e-2, 3.5e-2, 5.57e-2, 8.1e-2, 1.15e-1,
	1.718e-1, 2.569e-1, 4.758e-1, 7.48e-1 };

class OFFeature : public BaseFeature {
    public:
	OFFeature();
	virtual ~OFFeature();

	std::vector<NFIQ::QualityFeatureResult> computeFeatureData(
	    const NFIQ::FingerprintImageData &fingerprintImage) override;

	std::string getModuleName() const override;

	static std::vector<std::string> getAllFeatureIDs();
	static const std::string speedFeatureIDGroup;
	static const std::string moduleName;

    private:
	const int blocksize {
		16
	}; /*!< Processing is done in subblocks of this size. */
	const int slantedBlockSizeX {
		32
	}; /*!< Size of the rotated block in the x dimension
	    */
	const int slantedBlockSizeY {
		16
	}; /*!< Size of the rotated block in the y dimension
	    */
	const double threshold { .1 }; /*!< Threshold for differentiating
				foreground/background      blocks */
	const double angleMin { 4.0 }; /*!< Minimum angle change inclusion in
			       the quality measure */
};

}}

#endif

/******************************************************************************/
