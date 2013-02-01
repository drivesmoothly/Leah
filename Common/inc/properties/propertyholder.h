#ifndef PROPERTYHOLDER_H
#define PROPERTYHOLDER_H

#include <e32cmn.h>

class RPropertyBase;
typedef RPointerArray<RPropertyBase> RPropertyArray;

class RPropertyHolder
    {
public: // Constructors and destructor
    IMPORT_C RPropertyHolder();
    IMPORT_C virtual ~RPropertyHolder();

public: // New functions
    IMPORT_C const RPropertyArray& Properties() const;

protected: // New functions
    IMPORT_C RPropertyArray& GetProperties();

protected: // Data
    RPropertyArray iProperties;
    };

#endif //PROPERTYHOLDER_H
