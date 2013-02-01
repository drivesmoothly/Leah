/*
 ===============================================================================
 Name        : imageloader.cpp
 Author      : marius.crisan
 Copyright   : 2010 Symbera Solutions
 Description : Loads images from file.
 ===============================================================================
 */

#include "imageloader.h"
#include <imageconversion.h>
#include <w32std.h>

// ----------------------------------------------------------------------------
// ImageLoader::LoadImageL
// Loads an image from a file.
// ----------------------------------------------------------------------------
//
EXPORT_C void ImageLoader::LoadImageL( const TDesC& aFileName, CFbsBitmap*& aImage, CFbsBitmap*& aMask )
    {
    delete aImage;
    aImage = NULL;
    delete aMask;
    aMask = NULL;

    CFbsBitmap* image = NULL;
    CFbsBitmap* mask = NULL;

    RFs fsSession;
    User::LeaveIfError( fsSession.Connect() );
    CleanupClosePushL( fsSession );

    CImageDecoder* decoder = CImageDecoder::FileNewL( fsSession, aFileName,
            CImageDecoder::EOptionAlwaysThread );
    CleanupStack::PushL( decoder );

    RWsSession wsSession;
    User::LeaveIfError( wsSession.Connect( fsSession ) );
    CleanupClosePushL( wsSession );

    image = new ( ELeave ) CWsBitmap( wsSession );
    CleanupStack::PushL( image );

    mask = new ( ELeave ) CWsBitmap( wsSession );
    CleanupStack::PushL( mask );

    const TFrameInfo& frameInfo = decoder->FrameInfo();
    User::LeaveIfError( image->Create( frameInfo.iOverallSizeInPixels, EColor16M ) );
    User::LeaveIfError( mask->Create( frameInfo.iOverallSizeInPixels, EGray256 ) );

    TRequestStatus decoderStatus = KErrNone;
    decoder->Convert( &decoderStatus, *image, *mask );
    User::WaitForRequest( decoderStatus );

    CleanupStack::Pop( 2, image );
    aImage = image;
    aMask = mask;

    CleanupStack::PopAndDestroy( 3, &fsSession );
    }
