// USER INCLUDES
#include "imagestore.h"
#include "imageloader.h"

// SYSTEM INCLUDES
#include <fbs.h>

// The singleton instance
ImageStore* ImageStore::_instance = NULL;

// ----------------------------------------------------------------------------
// ImageStore::Instance
// Retrieves the singleton instance.
// ----------------------------------------------------------------------------
//
ImageStore& ImageStore::Instance()
    {
    if (!_instance)
        {
        _instance = new (ELeave) ImageStore();
        }
    return *_instance;
    }

// ----------------------------------------------------------------------------
// ImageStore::Close
// Frees all resources, deletes the bitmaps and closes the ImageStore
// ----------------------------------------------------------------------------
//
void ImageStore::Close()
    {
    delete _instance;
    _instance = NULL;
    }

// ----------------------------------------------------------------------------
// ImageStore::Initialize
// Initializes the image store. Loads default images.
// ----------------------------------------------------------------------------
//
void ImageStore::Initialize()
    {
    ImageStore& self = ImageStore::Instance();
    self.AddImage(EBitmapIdCheckBoxChecked, _L("c:\\checkbox-checked-bright-small.png"));
    self.AddImage(EBitmapIdCheckBoxUnchecked, _L("c:\\checkbox-unchecked-bright-small.png"));

    self.UseImage(EBitmapIdCheckBoxChecked);
    self.UseImage(EBitmapIdCheckBoxUnchecked);
    }

// ----------------------------------------------------------------------------
// ImageStore::GetImage
// description
// ----------------------------------------------------------------------------
//
TInt ImageStore::GetImage(TInt aBitmapId, const CFbsBitmap*& aBitmap, const CFbsBitmap*& aMask) const
    {
    StoreBlob* const * ptrBlob = _bitmapsMap.Find(aBitmapId);
    if (!ptrBlob)
        {
        return KErrNotFound;
        }
    StoreBlob* blob = *ptrBlob;
    aBitmap = blob->_bitmap;
    aMask = blob->_mask;
    return KErrNone;
    }

// ----------------------------------------------------------------------------
// ImageStore::AddImage
// Adds an image to the store
// ----------------------------------------------------------------------------
//
void ImageStore::AddImage(TInt aBitmapId, CFbsBitmap* aBitmap, CFbsBitmap* aMask)
    {
    StoreBlob* const * ptrBlob = _bitmapsMap.Find(aBitmapId);
    if (ptrBlob)
        {
        delete *ptrBlob;
        }

    StoreBlob* blob = new (ELeave) StoreBlob;
    blob->_bitmap = aBitmap;
    blob->_mask = aMask;
    blob->_refCount = 1;
    _bitmapsMap.InsertL(aBitmapId, blob);
    }

// ----------------------------------------------------------------------------
// ImageStore::AddImage
// Adds an image to the store based on id and path
// ----------------------------------------------------------------------------
//
void ImageStore::AddImage(TInt aBitmapId, const TDesC& aPath)
    {
    StoreBlob* const * ptrBlob = _bitmapsMap.Find(aBitmapId);
    StoreBlob* blob = NULL;
    if (ptrBlob)
        {
        blob = *ptrBlob;
        if (blob->_path != aPath)
            {
            delete blob;
            }
        else
            {
            return;
            }
        }

    blob = new (ELeave) StoreBlob;
    blob->_bitmap = NULL;
    blob->_mask = NULL;
    blob->_refCount = 0;
    blob->_path = aPath;
    _bitmapsMap.InsertL(aBitmapId, blob);
    }

// ----------------------------------------------------------------------------
// ImageStore::DeleteImage
// Deletes an image from the store
// ----------------------------------------------------------------------------
//
void ImageStore::DeleteImage(TInt aBitmapId)
    {
    StoreBlob* const * ptrBlob = _bitmapsMap.Find(aBitmapId);
    if (ptrBlob)
        {
        delete *ptrBlob;
        _bitmapsMap.Remove(aBitmapId);
        }
    }

// ----------------------------------------------------------------------------
// ImageStore::HasImage
// Checks if the store contains an image.
// ----------------------------------------------------------------------------
//
TBool ImageStore::HasImage(TInt aBitmapId) const
    {
    return (_bitmapsMap.Find(aBitmapId) != NULL);
    }

// ----------------------------------------------------------------------------
// ImageStore::UseImage
// Retrieves an image and increases the reference count.
// ----------------------------------------------------------------------------
//
TInt ImageStore::UseImage(TInt aBitmapId, const CFbsBitmap*& aBitmap, const CFbsBitmap*& aMask)
    {
    TInt errorCode = UseImage(aBitmapId);
    if (KErrNone == errorCode)
        {
        StoreBlob* const * ptrBlob = _bitmapsMap.Find(aBitmapId);
        ASSERT(ptrBlob);
        ASSERT(*ptrBlob);
        aBitmap = (*ptrBlob)->_bitmap;
        aMask = (*ptrBlob)->_mask;
        }
    return errorCode;
    }

// ----------------------------------------------------------------------------
// ImageStore::UseImage
// Increases the reference count for an image.
// ----------------------------------------------------------------------------
//
TInt ImageStore::UseImage(TInt aBitmapId)
    {
    StoreBlob* const * ptrBlob = _bitmapsMap.Find(aBitmapId);
    if (ptrBlob)
        {
        StoreBlob* blob = *ptrBlob;
        if (!blob->_bitmap)
            {
            if (blob->_path != KNullDesC)
                {
                ImageLoader::LoadImageL(blob->_path, blob->_bitmap, blob->_mask);
                ASSERT(blob->_bitmap);
                }
            else
                {
                return KErrBadName;
                }
            }
            ++blob->_refCount;
            return KErrNone;
        }
    else
        {
        return KErrNotFound;
        }
    }

// ----------------------------------------------------------------------------
// ImageStore::ReleaseImage
// Decreases the reference count. Unloads the image when the ref count is 0.
// ----------------------------------------------------------------------------
//
void ImageStore::ReleaseImage(TInt aBitmapId)
    {
    StoreBlob* const * ptrBlob = _bitmapsMap.Find(aBitmapId);
    if (ptrBlob)
        {
        StoreBlob* blob = *ptrBlob;
        --blob->_refCount;
        ASSERT(blob->_refCount >= 0);
        if (!blob->_refCount)
            {
            delete blob->_bitmap;
            blob->_bitmap = NULL;
            delete blob->_mask;
            blob->_mask = NULL;
            // Unload the image
            if (blob->_path == KNullDesC)
                {
                // We don't have a path, so we delete the entry.
                _bitmapsMap.Remove(aBitmapId);
                }
            }
        }
    }

// ----------------------------------------------------------------------------
// ImageStore::ImageStore
// Constructor.
// ----------------------------------------------------------------------------
//
ImageStore::ImageStore()
    {
    // No implementation required
    }

// ----------------------------------------------------------------------------
// ImageStore::ImageStore
// Copy constructor.
// ----------------------------------------------------------------------------
//
ImageStore::ImageStore(const ImageStore& /*aInstance*/)
    {
    // No implementation required
    }

// ----------------------------------------------------------------------------
// ImageStore::~ImageStore
// Destructor
// ----------------------------------------------------------------------------
//
ImageStore::~ImageStore()
    {
    Reset();
    }

// ----------------------------------------------------------------------------
// ImageStore::Reset
// Frees all memory, deletes all bitmaps.
// ----------------------------------------------------------------------------
//
void ImageStore::Reset()
    {
    THashMapIter<TInt, StoreBlob*> iterator(_bitmapsMap);
    StoreBlob* const * ptrBlob = NULL;
    while (NULL != (ptrBlob = iterator.NextValue()))
        {
        delete *ptrBlob;
        }
    _bitmapsMap.Close();
    }

// ----------------------------------------------------------------------------
// ImageStore::StoreBlob::~StoreBlob
// Destructor of the blob.
// ----------------------------------------------------------------------------
//
ImageStore::StoreBlob::~StoreBlob()
    {
    delete _bitmap;
    _bitmap = NULL;
    delete _mask;
    _mask = NULL;
    }
