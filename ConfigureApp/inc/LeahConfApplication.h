#ifndef LEAHCONFAPPLICATION_H_
#define LEAHCONFAPPLICATION_H_

// USER INCLUDES
#include "application.h"

// FORWARDS
class LeahConfIntroForm;
class LeahConfMainForm;

/**
 * Application class for Leah Configuration utility.
 */
class LeahConfApplication : public Application
    {
public: // Constructors and destructors
    /**
     * Default constructor.
     */
    LeahConfApplication();
    /**
     * Destructor.
     */
    ~LeahConfApplication();

public: // New functions
    /**
     * Shows the main form.
     */
    void ShowMainForm();
    /**
     * Shows the intro form.
     */
    void ShowIntroForm();

protected: // From base class
    /**
     * From Application, creates the forms.
     */
    void CreateForms();

private: // Data
    /// The intro form
    LeahConfIntroForm* iIntroForm;
    /// The main form
    LeahConfMainForm* iMainForm;
    };

#endif //LEAHCONFAPPLICATION_H_
