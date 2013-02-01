#ifndef IMAGESTORE_H_
#define IMAGESTORE_H_

// SYSTEM INCLUDES
#include <e32std.h>
#include <e32hashtab.h>
#include <estring.h>

// FORWARDS
class CFbsBitmap;

/**
 * Class that stores the images.
 * Implements reference counting.
 */
class ImageStore
    {
public: // Singleton access
    /**
     * Retrieves the singleton instance.
     * @return A reference to the instance.
     */
    static ImageStore& Instance();
    /**
     * Deletes all the bitmaps and masks and closes the store.
     */
    static void Close();
    /**
     * Initializes the image store.
     */
    static void Initialize();

public: // Public interface
    /**
     * Defines the null bitmap id.
     */
    enum TBitmapId
        {
        EBitmapIdNone = -1, //!< EBitmapIdNone
        EBitmapIdCheckBoxChecked = 0,
        EBitmapIdCheckBoxUnchecked,
        };
    /**
     * Retrieves the bitmap from the store based on id.
     * @param aBitmapId The bitmap id.
     * @param aBitmap The bitmap.
     * @param aMask The mask.
     * @return KErrNone if the bitmap was found, KErrNotFound if the bitmap was not found.
     */
    TInt GetImage(TInt aBitmapId, const CFbsBitmap*& aBitmap, const CFbsBitmap*& aMask) const;
    /**
     * Adds a bitmap to the store. Takes ownership of the bitmaps.
     * @param aBitmapId The bitmap id.
     * @param aBitmap The bitmap to add.
     * @param aMask The mask to add.
     */
    void AddImage(TInt aBitmapId, CFbsBitmap* aBitmap, CFbsBitmap* aMask = NULL);
    /**
     * Adds an image to the store based on id and path.
     * @param aBitmapId The bitmap id.
     * @param aPath The image path.
     */
    void AddImage(TInt aBitmapId, const TDesC& aPath);
    /**
     * Deletes a bitmap and removes it from the store.
     * @param aBitmapId The bitmap id.
     */
    void DeleteImage(TInt aBitmapId);
    /**
     * Checks if an image is added in the store, based on id.
     * @param aBitmapId The bitmap id.
     * @return ETrue if the image was found, EFalse if not.
     */
    TBool HasImage(TInt aBitmapId) const;
    /**
     * Retrieves the bitmap and mask and increases the reference count.
     * @param aBitmapId The bitmap id.
     * @param aBitmap The bitmap to retrieve.
     * @param aMask The mask to retrieve.
     * @return KErrNone if the image was retrieve successful. KErrNotFound if the image
     * is not found by id.
     */
    TInt UseImage(TInt aBitmapId, const CFbsBitmap*& aBitmap, const CFbsBitmap*& aMask);
    /**
     * Increases the reference count for a given image.
     * @param aBitmapId
     * @return KErrNone if the image was found. KErrNotFound if the image
     * is not found by id.
     */
    TInt UseImage(TInt aBitmapId);
    /**
     * Decreases the referece number for the given bitmap.
     * When the reference number goes to 0, the image is deleted.
     * If the image has a path, only the bitmap and mask are deleted, but the entry is kept
     * into the store based on the bitmap id, for future re-loading.
     * @param aBitmapId The bitmap id.
     */
    void ReleaseImage(TInt aBitmapId);

private: // Constructors and destructor
    /**
     * Constructor.
     */
    ImageStore();
    /**
     * Copy constructor.
     * @param aInstance The instance to copy from.
     * @remarks It's listed here just to avoid image store copying.
     */
    ImageStore(const ImageStore& aInstance);
    /**
     * Destructor.
     */
    ~ImageStore();

private: // New functions
    /**
     * Resets the store.
     */
    void Reset();

private: // Types
    /**
     * A data blob to store for each image.
     */
    struct StoreBlob
        {
        /**
         * Destructor.
         */
        ~StoreBlob();
        /// Reference count for the image usage.
        TInt _refCount;
        /// The bitmap.
        CFbsBitmap* _bitmap;
        /// The mask.
        CFbsBitmap* _mask;
        /// The path
        LString _path;
        };

private: // Data
    /// Stores the bitmaps
    RHashMap<TInt, StoreBlob*> _bitmapsMap;
    /// The singleton instance
    static ImageStore* _instance;
    };

#endif //IMAGESTORE_H_
