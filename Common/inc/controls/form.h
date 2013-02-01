#ifndef FORM_H_
#define FORM_H_

#include "control.h"
#include <w32std.h>

class WsClient;
class Application;

class Form : public Control
    {
public: // Properties
    PropertyRead<Form*> ParentForm;
    PropertyRead<Application&> App;
    Property<TRect> WindowBounds;

protected: // Properties
    Property<Control*> MouseOriginatingControl;
    Property<TPoint> MouseOriginatingLocation;
    Property<Control*> MouseDragSource;
    Property<Control*> MouseDragOver;

public: // Constructors and destructor
    IMPORT_C Form(Application& aClient, Form* aParent = NULL);
    IMPORT_C ~Form();

public: // From base class
    IMPORT_C TSize Measure(const TSize& aAvailableSize);
    IMPORT_C TSize Arrange(const TSize& aFinalSize);
    IMPORT_C void Layout();
    IMPORT_C void RaiseMouseEvent(Control* aSender, MouseEventArgs& aArgs);

public: // New functions
    IMPORT_C void Create();
    void Unload();
    IMPORT_C virtual void DoUnload();

protected: // From base class
    IMPORT_C CWsScreenDevice& GetScreen() const;
    IMPORT_C Application& GetApplication() const;
    /**
     * From RAsyncCommandHandler<TInt>.
     * Handles asynchronous commands.
     */
    void AsyncHandleCommandL(const TInt& aCommand);

protected: // New functions
    virtual void Form_WindowBounds_ValueChanged(const PropertyBase<TRect>& aBounds);
    /**
     * Handles Visible property change event.
     * @param aVisible The Visible property.
     */
    void Visible_Changed(const PropertyBase<TBool>& aVisible);

protected: // Data
    enum TAsyncCommands
        {
        EUnload = 0x1000
        };
    };

#endif //FORM_H_
