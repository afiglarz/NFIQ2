#ifndef QUALITYMAPFEATURES_H
#define QUALITYMAPFEATURES_H

#include <features/BaseFeature.h>
#include <nfiq2_fingerprintimagedata.hpp>
#include <nfiq2_interfacedefinitions.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <stdio.h>
#include <stdlib.h>

#include "ImgProcROIFeature.h"

#include <list>
#include <string>
#include <vector>

namespace NFIQ { namespace QualityFeatures {

#define LOW_FLOW_MAP_NO_DIRECTION 0
#define LOW_FLOW_MAP_LOW_FLOW 127
#define LOW_FLOW_MAP_HIGH_FLOW 255

class QualityMapFeatures : BaseFeature {
    public:
	QualityMapFeatures(bool bOutputSpeed,
	    std::vector<NFIQ::QualityFeatureSpeed> &speedValues,
	    const ImgProcROIFeature::ImgProcROIResults &imgProcResults)
	    : BaseFeature(bOutputSpeed, speedValues)
	    , imgProcResults_ { imgProcResults } {};
	virtual ~QualityMapFeatures();

	std::vector<NFIQ::QualityFeatureResult> computeFeatureData(
	    const NFIQ::FingerprintImageData &fingerprintImage) override;

	std::string getModuleName() const override;

	void initModule() { /* not needed here */ };

	static std::vector<std::string> getAllFeatureIDs();
	static const std::string speedFeatureIDGroup;
	static const std::string moduleName;

	// compute orientation angle of a block
	static bool getAngleOfBlock(
	    const cv::Mat &block, double &angle, double &coherence);

	// computes low flow value of block
	static double computeLowFlowBlockValue(const cv::Mat &block);

    private:
	// compute low flow map with ROI filter
	static cv::Mat computeLowFlowMapWithROIFilter(cv::Mat &img,
	    bool bUseSurroundingWindow, unsigned int bs,
	    ImgProcROIFeature::ImgProcROIResults &roiResults,
	    unsigned int &noOfHighFlowBlocks, unsigned int &noOfLowFlowBlocks);

	// compute orientation map
	static cv::Mat computeOrientationMap(cv::Mat &img, bool bFilterByROI,
	    double &coherenceSum, double &coherenceRel, unsigned int bs,
	    ImgProcROIFeature::ImgProcROIResults roiResults);

	// static helper functions for numberical gradient computation
	static cv::Mat computeNumericalGradientX(const cv::Mat &mat);
	static void computeNumericalGradients(
	    const cv::Mat &mat, cv::Mat &grad_x, cv::Mat &grad_y);

    private:
	ImgProcROIFeature::ImgProcROIResults imgProcResults_ {};
};

}}

#endif

/******************************************************************************/
