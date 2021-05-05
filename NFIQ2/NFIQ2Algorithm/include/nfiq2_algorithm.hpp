#ifndef NFIQ2_ALGORITHM_HPP_
#define NFIQ2_ALGORITHM_HPP_

#include <nfiq2_fingerprintimagedata.hpp>
#include <nfiq2_interfacedefinitions.hpp>
#include <nfiq2_modelinfo.hpp>
#include <nfiq2_qualityfeatures.hpp>

#include <memory>
#include <string>
#include <unordered_map>

namespace NFIQ2 {

/**
 * 	Wrapper for applying the trained random forest parameters to quality
 * 	features to compute an NFIQ2 score.
 */
class Algorithm {
    public:
	/**
	 * @brief
	 * Default constructor of Algorithm.
	 *
	 * @note
	 * May load from embedded, in which case this can be slow.
	 */
	Algorithm();

	/**
	 * @brief
	 * Constructor that loads random forest parameters from disk.
	 *
	 * @param fileName
	 * The file path containing the random forest model.
	 *
	 * @param fileHash
	 * The md5 checksum of the provided file.
	 */
	Algorithm(const std::string &fileName, const std::string &fileHash);

	/**
	 * @brief
	 * Constructor using `modelInfoObj` object to initialize the
	 * random forest model.
	 *
	 * @param modelInfoObj
	 * Contains the random forest model and information about it.
	 */
	Algorithm(const NFIQ2::ModelInfo &modelInfoObj);

	/** Copy constructor. */
	Algorithm(const Algorithm &);

	/** Assignment operator. */
	Algorithm &operator=(const Algorithm &);

	/** Move constructor. */
	Algorithm(Algorithm &&) noexcept;

	/** Move assignment operator. */
	Algorithm &operator=(Algorithm &&) noexcept;

	/** Destructor. */
	~Algorithm();

	/**
	 * @brief
	 * Computes the quality score from the provided fingerprint image data.
	 *
	 * @param rawImage
	 * Encoded Fingerprint image.
	 *
	 * @return
	 * Computed quality score.
	 *
	 * @throw Exception
	 * Called before random forest parameters were loaded.
	 */
	unsigned int computeQualityScore(
	    const NFIQ2::FingerprintImageData &rawImage) const;

	/**
	 * @brief
	 * Computes the quality score from a vector of extracted BaseFeatures
	 * from a cropped fingerprint image.
	 *
	 * @param features
	 * Vector of computed feature metrics that contain quality
	 * information for a fingerprint image.
	 *
	 * @return
	 * Computed quality score.
	 *
	 * @throw Exception
	 * Called before random forest parameters were loaded.
	 */
	unsigned int computeQualityScore(const std::vector<
	    std::shared_ptr<NFIQ2::QualityFeatures::BaseFeature>> &features)
	    const;

	/**
	 * @brief
	 * Computes the quality score from a map of extracted image
	 * quality feature data.
	 *
	 * @param features
	 * Map of string, quality feature data pairs.
	 *
	 * @return
	 * Computed quality score.
	 *
	 * @throw Exception
	 * Called before random forest parameters were loaded.
	 */
	unsigned int computeQualityScore(
	    const std::unordered_map<std::string, NFIQ2::QualityFeatureData>
		&features) const;

	/**
	 * @brief
	 * Obtain MD5 checksum of Random Forest parameter file loaded.
	 *
	 * @return
	 * MD5 checksum of the Random Forest parameter file loaded.
	 *
	 * @throw Exception
	 * Called before random forest parameters were loaded.
	 */
	std::string getParameterHash() const;

	/**
	 * @brief
	 * Determine if random forest parameters have been loaded.
	 *
	 * @return
	 * True if some set of random forest parameters have been loaded, false
	 * otherwise.
	 */
	bool isInitialized() const;

	/**
	 * @brief
	 * Obtain if the random forest parameters are embedded in the library
	 * or located externally.
	 *
	 * @return
	 * true if random forest parameters are embedded, false otherwise.
	 */
	bool isEmbedded() const;

	/**
	 * @brief
	 * Obtain the friction ridge capture technology (FCT) specified for the
	 * embedded random forest parameters.
	 *
	 * @return
	 * Embedded FCT specified.
	 *
	 * @throw NFIQ2::Exception
	 * Parameters were not embedded or FCT was not specified.
	 */
	unsigned int getEmbeddedFCT() const;

    private:
	/** Pointer to Implementation class. */
	class Impl;

	/** Pointer to Implementation smart pointer. */
	std::unique_ptr<Algorithm::Impl> pimpl;
};
} // namespace NFIQ

#endif /* NFIQ2_ALGORITHM_HPP_ */
