#ifndef NFIQ2_MODELINFO_HPP_
#define NFIQ2_MODELINFO_HPP_

#include <string>

namespace NFIQ2 {
/** Information about a random forest parameter model. */
class ModelInfo {
    public:
	/** Default constructor. */
	ModelInfo();

	/**
	 * Constructor
	 *
	 * @param modelInfoFilePath
	 * Path to model information file.
	 */
	ModelInfo(const std::string &modelInfoFilePath);

	/**
	 * @brief
	 * Obtain the model name.
	 *
	 * @return
	 * Returns model name.
	 */
	std::string getModelName() const;

	/**
	 * @brief
	 * Obtain the entity that trained the random forest model.
	 *
	 * @return
	 * Returns model trainer.
	 */
	std::string getModelTrainer() const;

	/**
	 * @brief
	 * Obtain additional description information for model.
	 *
	 * @return
	 * Returns model description.
	 */
	std::string getModelDescription() const;

	/**
	 * @brief
	 * Obtain the version number of the model.
	 *
	 * @return
	 * Returns model version.
	 */
	std::string getModelVersion() const;

	/**
	 * @brief
	 * Obtain the file path of the model.
	 *
	 * @return
	 * Returns model file path.
	 */
	std::string getModelPath() const;

	/**
	 * @brief
	 * Obtain the md5 checksum of the model
	 *
	 * @return
	 * Returns model md5 checksum.
	 */
	std::string getModelHash() const;

	/** Name Key. */
	static const std::string ModelInfoKeyName;
	/** Trainer Key. */
	static const std::string ModelInfoKeyTrainer;
	/** Description Key. */
	static const std::string ModelInfoKeyDescription;
	/** Version Key. */
	static const std::string ModelInfoKeyVersion;
	/** Path Key. */
	static const std::string ModelInfoKeyPath;
	/** Hash Key. */
	static const std::string ModelInfoKeyHash;

    private:
	/** Name member. */
	std::string modelName;
	/** Trainer member. */
	std::string modelTrainer;
	/** Description member. */
	std::string modelDescription;
	/** Version member. */
	std::string modelVersion;
	/** Path member. */
	std::string modelPath;
	/** Hash member. */
	std::string modelHash;
};

} // namespace NFIQ

#endif /* NFIQ2_MODELINFO_HPP_ */
