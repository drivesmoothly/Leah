#ifndef MOUSEEVENTARGS_H_
#define MOUSEEVENTARGS_H_

#include "property.h"
#include <e32keys.h>
#include <pointerevent.h>

class Control;

struct MouseButton
    {
    enum Button {
        Left,
        None,
        Right,
        Middle,
        Finger1,
        Finger2,
        Finger3,
        Finger4,
        Finger5,
        Finger6,
        Finger7,
        Finger8,
        Finger9,
        Finger10
        };
    };

class MouseEventArgs
    {
public: // Constructors and destructor
    MouseEventArgs(TPointerEvent::TType aType, const TPoint& aLocation);
    MouseEventArgs(const MouseEventArgs& aArgs, const TPoint& aLocation);
    ~MouseEventArgs();

public: // New functions
    inline TInt Button() const;
    inline const TPoint& Location() const;
    inline TInt X() const;
    inline TInt Y() const;
    inline TPointerEvent::TType Type() const;
    inline Control* OriginatingControl() const;
    inline void SetOriginatingControl(Control* aControl);
    inline const TPoint& OriginatingLocation() const;
    inline void SetOriginatingLocation(const TPoint& aLocation);
    inline Control* DragSource() const;
    inline void SetDragSource(Control* aDragSource);
    inline Control* DragOver() const;
    inline void SetDragOver(Control* aDragOver);
    inline TBool Handled() const;

private: // Data
    TPoint                  _location;
    TPointerEvent::TType    _type;
    Control*                _originatingControl;
    TPoint                  _originatingLocation;
    Control*                _dragSource;
    Control*                _dragOver;
    TBool                   _handled;
    };

#include "mouseeventargs.inl"

#endif //MOUSEEVENTARGS_H_
