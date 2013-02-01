#ifndef APPLICATION_H_
#define APPLICATION_H_

// SYSTEM INCLUDES
#include <fbs.h>
#include <e32base.h>
#include <w32std.h>

// USER INCLUDES
#include "property.h"

// FORWARDS
class Form;
class WsClient;
class WsRedrawer;
class FontsManager;
class KeyboardForm;

/**
 * The main application class.
 */
class Application : public CBase
    {
public: // Properties

    /// The window server client.
    PropertyReadExt<WsClient&, Application> Ws;
    /// The fonts manager.
    PropertyReadExt<FontsManager&, Application> Fonts;

public: // Constructors and destructors
    /**
     * Destructor.
     */
    ~Application();

    /**
     * Creates a new instance.
     * @return A pinter to the new instance.
     */
    template <class T>
    static Application* NewInstance();

    /**
     * Runs te application/
     * @return The return code from running the application.
     */
    template <class T>
    static TInt Run();

    /**
     * Retrieves the singleton instance.
     * @return The application instance.
     */
    static Application* Instance();

protected: // Constructors and destructors
    /**
     * Constructor.
     * @param aUid The UID of the application.
     * @remarks Very important for the window group.
     */
    Application(const TUid& aUid);
    /**
     * Second phase construtor.
     */
    virtual void ConstructL();
    /**
     * The thread function which is the main application loop.
     * @param aFactory The factory function that create the specific application object.
     */
    static void ThreadFunction(Application* (*aFactory)());

public: // New functions
    /**
     * Asynchronously stops the application.
     */
    void Stop();

protected: // New functions
    /**
     * Starts the application.
     */
    void Start();

    // Forms management
    /**
     * Creates the keyboard form.
     */
    void CreateKeyboardForm();
    /**
     * Creates the forms.
     */
    virtual void CreateForms();
    /**
     * Adds a form to the application.
     * @param aForm The form to add.
     */
    void AddForm(Form* aForm);
    /**
     * Removes a form from the application.
     * @param aForm The form to remove.
     */
    void RemoveForm(Form* aForm);
    /**
     * Sets the current visible form.
     * @param aForm
     */
    void SetCurrentForm(Form* aForm);
    /**
     * Retrieves the current form.
     * @return A pointer to the current form. Can be NULL if there is no form.
     */
    Form* CurrentForm() const;
    /**
     * Handles window server events raised by the window server client.
     * @param aEvent The event to handle.
     */
    void WsClient_WsEvent(TWsEvent& aEvent);
    /**
     * Sets all the forms size.
     * @param aSize The new size.
     */
    void SetFormsSize(const TSize& aSize);

protected: // Properties code
    /**
     * Retrieves the window server client.
     * @return The window server client.
     */
    WsClient& GetWsClient() const;
    /**
     * Retrieves the fonts manager.
     * @return The fonts manager.
     */
    FontsManager& GetFontsManager() const;

protected: // Data
    /// The application singleton instance.
    static Application* iInstance;

    /// The active scheduler wait object that runs the main application loop.
    CActiveSchedulerWait* iWait;
    /// The main file server session.
    RFs iFsSession;
    /// The main window server session.
    RWsSession iWsSession;

    /// The window server client.
    WsClient* iWsClient;
    /// The window server redrawer.
    WsRedrawer* iWsRedrawer;

    /// The child forms.
    RPointerArray<Form> iForms;
    /// The current form.
    Form* iCurrentForm;
    /// The keyboard form
    KeyboardForm* iKeyboardForm;

    /// The fonts manager.
    FontsManager* iFontsManager;
    /// The application UID.
    TUid iAppUid;
    };

// Inline implementations
#include "application.inl"

#endif //APPLICATION_H_
