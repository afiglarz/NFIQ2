#ifndef NFIQ2_DATA_HPP_
#define NFIQ2_DATA_HPP_

#include <nfiq2_exception.hpp>

#include <fstream>
#include <string>
#include <vector>

namespace NFIQ2 {

/**
 * Manages binary data and offers functions for easy handling
 * of fingerprint templates and quality feature values.
 */
class Data : public std::basic_string<uint8_t> {
    public:
	/** Default Data constructor. */
	Data();

	/**
	 * @brief
	 * Constructor with available pointer to data.
	 *
	 * @param pData
	 * Data pointer.
	 *
	 * @param dataSize
	 * Size of data at data pointer.
	 */
	Data(const uint8_t *pData, uint32_t dataSize);

	/** Copy constructor. */
	Data(const Data &otherData);

	/**
	 * @brief
	 * Constructor with string-based data.
	 *
	 * @param otherData
	 * Binary data in string format.
	 */
	explicit Data(const std::basic_string<uint8_t> &otherData);

	/** Destructor. */
	virtual ~Data();

	/**
	 * @brief
	 * Reads the content from the a file into the data
	 * structure.
	 *
	 * @param filename
	 * The path and name of the file that will be read.
	 *
	 * @throws NFIQException
	 */
	void readFromFile(const std::string &filename);

	/**
	 * @brief
	 * Writes the content to a file.
	 *
	 * @param filename
	 * The path and name of the file that will be written to.
	 *
	 * @throws NFIQException
	 */
	void writeToFile(const std::string &filename) const;

	/**
	 * @brief
	 * Generates a string in hexadecimal format of the buffer.
	 *
	 * @return
	 * The content of the buffer as hexadecimal string.
	 *
	 * @throws NFIQException
	 */
	std::string toHexString() const;

	/**
	 * @brief
	 * Imports data from a Base64 encoded string.
	 *
	 * @param base64String
	 * The Base64 encoded string.
	 *
	 * @throws NFIQException
	 */
	void fromBase64String(const std::string &base64String);

	/**
	 * @brief
	 * Generates a string in base64 format of the buffer.
	 *
	 * @return
	 * The content of the buffer as base64 encoded string.
	 *
	 * @throws NFIQException
	 */
	std::string toBase64String() const;
};
} // namespace NFIQ

#endif /* NFIQ2_DATA_HPP_ */
