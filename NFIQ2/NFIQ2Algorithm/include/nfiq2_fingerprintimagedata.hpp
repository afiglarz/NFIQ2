#ifndef NFIQ2_FINGERPRINTIMAGEDATA_HPP_
#define NFIQ2_FINGERPRINTIMAGEDATA_HPP_

#include <nfiq2_data.hpp>

/**
 * Pixel intensity threshold used for determining whitespace
 * around fingerprint.
 */
#define MU_THRESHOLD 250

namespace NFIQ2 {

/** Resolution of an image in pixels per inch (PPI). */
typedef enum image_resolution_e {
	/** 500 PPI. */
	e_ImageResolution_500dpi = 500,
	/** 1000 PPI. */
	e_ImageResolution_1000dpi = 1000
} ImageResolution;

/**
 * Binary data representing a decompressed fingerprint image, canonically
 * encoded as per ISO/IEC 19794-4:2005.
 */
class FingerprintImageData : public Data {
    public:
	/** Default constructor. */
	FingerprintImageData();

	/**
	 * @brief
	 * Constructor that does not store image data.
	 *
	 *
	 * @param imageWidth
	 * Width of the image in pixels.
	 * @param imageHeight
	 * Height of the image in pixels.
	 * @param fingerCode
	 * Finger position of the fingerprint in the image.
	 * @param imageDPI
	 * Resolution of the image in pixels per inch.
	 */
	FingerprintImageData(uint32_t imageWidth, uint32_t imageHeight,
	    uint8_t fingerCode, uint16_t imageDPI);

	/**
	 * @brief
	 * Constructor storing image data.
	 *
	 * @param pData
	 * Pointer to decompressed 8 bit-per-pixel grayscale image data,
	 * canonically encoded as per ISO/IEC 19794-4:2005.
	 * @param dataSize
	 * Size of the buffer pointed to by `pData`.
	 * @param imageWidth
	 * Width of the image in pixels.
	 * @param imageHeight
	 * Height of the image in pixels.
	 * @param fingerCode
	 * Finger position of the fingerprint in the image.
	 * @param imageDPI
	 * Resolution of the image in pixels per inch.
	 */
	FingerprintImageData(const uint8_t *pData, uint32_t dataSize,
	    uint32_t imageWidth, uint32_t imageHeight, uint8_t fingerCode,
	    uint16_t imageDPI);

	/** Copy constructor. */
	FingerprintImageData(const FingerprintImageData &otherData);

	/** Destructor. */
	virtual ~FingerprintImageData();

	/** Width of the fingerprint image (in pixels) */
	uint32_t m_ImageWidth;
	/** Height of the fingerprint image (in pixels) */
	uint32_t m_ImageHeight;
	/** ISO finger code of the fingerprint in the image */
	uint8_t m_FingerCode;
	/** Dots per inch of the fingerprint image */
	int16_t m_ImageDPI;

	/**
	 * @brief
	 * Remove near-white lines around the image.
	 *
	 * @return
	 * Cropped fingerprint image.
	 *
	 * @throws NFIQException
	 * Error performing the crop, or the image is too small to be processed
	 * after cropping.
	 */
	NFIQ2::FingerprintImageData removeWhiteFrameAroundFingerprint() const;
};
} // namespace NFIQ

#endif /* NFIQ2_FINGERPRINTIMAGEDATA_HPP_ */
