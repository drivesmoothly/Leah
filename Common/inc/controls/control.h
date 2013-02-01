#ifndef CONTROL_H_
#define CONTROL_H_

// SYSTEM INCLUDES
#include <e32base.h>

// USER INCLUDES
#include "events.h"
#include "property.h"
#include "keyeventargs.h"
#include "keypresseventargs.h"
#include "mouseeventargs.h"
#include "painteventargs.h"
#include "drageventargs.h"
#include "attachedpropertystore.h"
#include "asynccommandhandler.h"

// FORWARDS
class Control;
class BackBuffer;
class RWindow;
class CWsScreenDevice;
class Application;

// TYPEDEFS
typedef RPointerArray<Control> RControlsArray;

/**
 * Base class for the controls.
 */
class Control : public CBase, public AttachedPropertyStore, protected RAsyncCommandHandler<TInt>
    {
public: // Events
    Event<Control* /*sender*/>                                  Click;
    Event<Control* /*sender*/>                                  DoubleClick;
    Event<Control* /*sender*/, Control* /*added control*/>      ControlAdded;
    Event<Control* /*sender*/, Control* /*removed control*/>    ControlRemoved;
    Event<Control* /*sender*/, DragEventArgs& /*drag args*/>    DragDrop;
    Event<Control* /*sender*/, DragEventArgs& /*drag args*/>    DragEnter;
    Event<Control* /*sender*/>                                  DragLeave;
    Event<Control* /*sender*/, DragEventArgs& /*drag args*/>    DragOver;
    Event<Control* /*sender*/>                                  GotFocus;
    Event<Control* /*sender*/, KeyEventArgs& /*key args*/>      KeyDown;
    Event<Control* /*sender*/, KeyPressEventArgs& /*key args*/> KeyPress;
    Event<Control* /*sender*/, KeyEventArgs& /*key args*/>      KeyUp;
    Event<Control* /*sender*/>                                  LostFocus;
    Event<Control* /*sender*/, MouseEventArgs& /*mouse args*/>  MouseClick;
    Event<Control* /*sender*/, MouseEventArgs& /*mouse args*/>  MouseDoubleClick;
    Event<Control* /*sender*/, MouseEventArgs& /*mouse args*/>  MouseDown;
    Event<Control* /*sender*/, MouseEventArgs& /*mouse args*/>  MouseUp;
    Event<Control* /*sender*/, PaintEventArgs& /*paint args*/>  Paint;
    Event<Control* /*sender*/>                                  Invalidated;
    Event<Control* /*sender*/>                                  Validated;
    Event<Control* /*sender*/>                                  RequestFocus;

public: // Dependency Properties
    static Property<TSize>* const               SizeProperty;
    static Property<TInt>* const                WidthProperty;
    static Property<TInt>* const                HeightProperty;
    static Property<TRect>* const               MarginProperty;
    static Property<TBool>* const               VisibleProperty;

public: // Properties
    // Size and location
    Property<TRect>         Bounds;
    Property<TInt>          Top;
    Property<TInt>          Left;
    Property<TInt>          Bottom;
    Property<TInt>          Right;
    Property<TPoint>        Location;
    Property<TPoint>        BottomRight;
    Property<TSize>         Size;
    Property<TInt>          Width;
    Property<TInt>          Height;
    Property<TRect>         ClientRectangle;
    Property<TRect>         DisplayRectangle;
    Property<TSize>         ClientSize;
    Property<TRect>         Margin;
    Property<TSize>         DefaultSize;
    Property<TSize>         MinimumSize;
    Property<TSize>         MaximumSize;
    Property<TSize>         PreferredSize;
    Property<HAlignment::Align> HorizontalAlignment;
    Property<VAlignment::Align> VerticalAlignment;

    // Hierarchy
    Property<Control*>                              Parent;
    PropertyReadExt<const RControlsArray&, Control> Controls;
    PropertyReadExt<RWindow*, Control>              Window;
    PropertyReadExt<CWsScreenDevice&, Control>      Screen;
    PropertyReadExt<Application&, Control>          App;
    PropertyDes                                     Name;

    // Focus
    Property<TBool>         CanFocus;
    Property<TBool>         ContainsFocus;
    Property<TBool>         Focused;

    // Behavior
    Property<TBool>         DoubleBuffered;
    Property<TBool>         Enabled;
    Property<TInt>          TabIndex;
    Property<TBool>         TabStop;
    Property<TBool>         Visible;
    Property<TBool>         Capture;

    // Others
    Property<TAny*>         Tag;

protected: // Properties
    Property<TBool>         IsInvalidated;
    Property<TRect>         InvalidatedRect;
    Property<Control*>      FocusedChild;

protected: // Data types
    /// Asynchronous commands the panel can handle.
    enum TCommand
        {
        ECommandLayout
        };

public: // Constructors and destructor
    Control();
    ~Control();
    virtual void Create();

public: // New functions
    void BringToFront();
    TBool Contains(Control* aControl) const;
    TBool Focus();
    Control* GetChildAtPoint(const TPoint& aPoint);
    Control* GetFocusingChildAtPointRecursive(const TPoint& aPoint);
    Control* GetContainerControl();
    Control* GetNextControl(Control* aControl, TBool aForward);
    virtual TSize GetPreferredSize(const TSize& aProposedSize);
    TBool GetTopLevel() const;
    const Control* TopLevelControl() const;
    void Show();
    void Hide();
    /**
     * Issues a redraw without invalidating.
     */
    void Redraw();
    void Invalidate();
    void Invalidate(const TRect& aRect);
    void InvokeGotFocus(Control* aControl);
    void InvokeLostFocus(Control* aControl);
    void InvokeClick(Control* aControl);
    void InvokePaint(Control* aControl, PaintEventArgs& aArgs);
    TPoint PointToClient(const TPoint& aPoint);
    TPoint PointToScreen(const TPoint& aPoint);
    TRect RectangleToClient(const TRect& aRect);
    TRect RectangleToScreen(const TRect& aRect);
    virtual void Refresh();
    void SendToBack();
    void AddControl(Control* aControl);
    void RemoveControl(Control* aControl);
    TPoint PositionToScreen() const;
    /**
     * Calculates the position relative to the draw context.
     * This is the position of the control relative to it's parents until
     * a parent is double buffered or is top level.
     * @return The position relative to the draw context.
     */
    TPoint PositionToDrawContext() const;
    /**
     * Measures the size in layout required for child elements.
     * @param aGivenSize The available size that this element can give to child elements.
     * @return The size that this element needs during layout.
     */
    virtual TSize Measure(const TSize& aAvailableSize);
    /**
     * Positions child elements.
     * @param aFinalSize The final area within the parent that can be used
     * to arrange the children.
     * @return The actual size used.
     */
    virtual TSize Arrange(const TSize& aFinalSize);
    /**
     * Posts a layout command to be executed deferred.
     */
    void LayoutDeferred();
    /**
     * Performs layout.
     * Provides support for both Panel based layout and custom Control layout.
     */
    virtual void Layout();

protected: // New functions
    /**
     * Initializes the control from XML generated code.
     */
    virtual void InitFromXml();

public: // Infrastructure
    virtual void RaisePaintEvent(Control* aSender, PaintEventArgs& aArgs);
    void DispatchPaint(PaintEventArgs& aArgs);
    virtual void RaiseKeyEvent(Control* aSender, KeyEventArgs& aArgs);
    virtual void RaiseMouseEvent(Control* aSender, MouseEventArgs& aArgs);

protected: // From base classes
    /**
     * From RAsyncCommandHandler<TInt>.
     * Handles asynchronous commands.
     */
    void AsyncHandleCommandL(const TInt& aCommand);

protected: // Raising events
    virtual void OnClick();
    virtual void OnDoubleClick();
    virtual void OnControlAdded(Control* aControl);
    virtual void OnControlRemoved(Control* aControl);
    virtual void OnDragDrop(DragEventArgs& aArgs);
    virtual void OnDragEnter(DragEventArgs& aArgs);
    virtual void OnDragLeave();
    virtual void OnDragOver(DragEventArgs& aArgs);
    virtual void OnGotFocus();
    virtual void OnKeyDown(KeyEventArgs& aArgs);
    virtual void OnKeyPress(KeyPressEventArgs& aArgs);
    virtual void OnKeyUp(KeyEventArgs& aArgs);
    virtual void OnLostFocus();
    virtual void OnMouseClick(MouseEventArgs& aArgs);
    virtual void OnMouseDoubleClick(MouseEventArgs& aArgs);
    virtual void OnMouseDown(MouseEventArgs& aArgs);
    virtual void OnMouseUp(MouseEventArgs& aArgs);
    virtual void OnPaint(PaintEventArgs& aArgs);
    virtual void OnInvalidated();
    virtual void OnValidated();
    virtual void OnRequestFocus();

protected: // New functions
    virtual void InvalidateWindow(const TRect& aRect);
    TBool FocusChild(Control* aChild);
    /**
     * Calculates the margins size.
     * @return The margins size.
     */
    TSize MarginsSize() const;

protected: // Events handlers
    void DoubleBuffered_ValueChanged(const PropertyBase<TBool>& aDoubleBuffered);
    void DoubleBuffered_Size_ValueChanged(const PropertyBase<TSize>& aSize);
    void Focused_ValueChanged(const PropertyBase<TBool>& aFocused);
    void Margin_Changed(const PropertyBase<TRect>& aMargin);
    void Size_Changed(const PropertyBase<TSize>& aSize);
    void Child_RequestFocus(Control* aChild);
    void Visible_Changed(const PropertyBase<TBool>& aVisible);

protected: // Property backing functions
    virtual RWindow* GetWindow() const;
    virtual CWsScreenDevice& GetScreen() const;
    virtual Application& GetApplication() const;
    const RControlsArray& GetControlsArray() const;

private: // New functions
    void CalculateClientRect();
    /**
     * Performs invalidation for this control. Marks IsInvalidated to true
     * and extends InvalidatedRect accordingly.
     * @param aRect The rectangle to invalidate.
     */
    void InvalidateControl(const TRect& aRect);
    /**
     * Invalidates the parents based on InvalidatedRect.
     */
    void InvalidateParents();

    template <typename Event>
    void TriggerEvent(Event& aEvent);
    template <typename Event, typename Arg1>
    void TriggerEvent(Event& aEvent, Arg1& aArg1);
    template <typename Event, typename Arg1, typename Arg2>
    void TriggerEvent(Event& aEvent, Arg1& aArg1, Arg2& aArg2);
    template <typename Event, typename Arg1, typename Arg2, typename Arg3>
    void TriggerEvent(Event& aEvent, Arg1& aArg1, Arg2& aArg2, Arg3& aArg3);

protected: // Data
    RControlsArray iControls;
    BackBuffer* iBackBuffer;
    mutable RWindow* iWindow;
    mutable CWsScreenDevice* iScreen;
    mutable Application* iApplication;
    };

#include "control.inl"

#endif //CONTROL_H_
