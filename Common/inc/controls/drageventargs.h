#ifndef DRAGEVENTARGS_H_
#define DRAGEVENTARGS_H_

#include "property.h"
#include "dataobject.h"

struct DragDropEffect
    {
    enum {
        None,
        Copy,
        Move,
        Link,
        Scroll,
        All
        };
    };

class DragEventArgs
    {
public: // Properties
    TInt                                    AllowedEffect;
    DataObject*                             Data;
    TInt                                    Effect;
    TInt                                    KeyState;
    PropertyReadExt<TInt, DragEventArgs>    X; // In screen coordinates
    PropertyReadExt<TInt, DragEventArgs>    Y; // In screen coordinates
    TPoint                                  Location; // In screen coordinates
    Control*                                DragSource;

public: // Constructors and destructor
    DragEventArgs(TInt aAllowedEffect, DataObject* aData, TInt aKeyState, const TPoint& aLocation, Control* aDragSource);
    ~DragEventArgs();

protected: // Property mapping
    TInt GetX() const;
    TInt GetY() const;
    };

#endif //DRAGEVENTARGS_H_
