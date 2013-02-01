
/// Defines the Symbian Forms panic category
_LIT(KSymbianFormsPanicCategory, "SymbianForms");

// ----------------------------------------------------------------------------
// Application::NewInstance
// Template factory method for application objects.
// ----------------------------------------------------------------------------
//
template <class T>
Application* Application::NewInstance()
    {
    if (NULL == Application::iInstance)
        {
        Application::iInstance = new (ELeave) T();
        }
    return Application::Instance();
    }

// ----------------------------------------------------------------------------
// Application::Run
// Template function that runs the application.
// ----------------------------------------------------------------------------
//
template <class T>
TInt Application::Run()
    {
    __UHEAP_MARK;

    CTrapCleanup* cleanupStack = CTrapCleanup::New();
    if (NULL == cleanupStack)
        {
        User::Panic(KSymbianFormsPanicCategory, KErrNoMemory);
        }

    TRAPD(err, ThreadFunction(&Application::NewInstance<T>));

    if (KErrNone != err)
        {
        User::Panic(KSymbianFormsPanicCategory, err);
        }

    delete cleanupStack;
    cleanupStack = NULL;

    __UHEAP_MARKEND;
    return KErrNone;
    }
