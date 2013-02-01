/*
 ===============================================================================
 Name        : imageloader.h
 Author      : marius.crisan
 Copyright   : 2010 Symbera Solutions
 Description : Loads images from files.
 ===============================================================================
 */

#ifndef IMAGELOADER_H_
#define IMAGELOADER_H_

class CImageDecoder;
class CFbsBitmap;

#include <e32cmn.h>

/**
 * Loads images from files.
 */
class ImageLoader
    {
public:
    /**
     * Loads an image from a file.
     * @param aFileName The image file name.
     * @param aImage The output image. If the bitmap already exists, it will be deleted before
     * loading the new image. Should be NULL otherwise.
     * @param aMask The output mask. If the mask already exists, it will be deleted before
     * loading the new image. Should be NULL otherwise.
     */
    IMPORT_C static void LoadImageL( const TDesC& aFileName, CFbsBitmap*& aImage, CFbsBitmap*& aMask );
    };

#endif /* IMAGELOADER_H_ */
