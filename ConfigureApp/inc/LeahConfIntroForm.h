#ifndef LEAHCONFINTROFORM_H_
#define LEAHCONFINTROFORM_H_

// USER INCLUDES
#include "form.h"
#include "layoutforwards.h"
#include "controlsforwards.h"

// FORWARDS
class LeahConfApplication;

/**
 * Intro form for the config application.
 */
class LeahConfIntroForm : public Form
    {
public: // Constructors and destructor
    /**
     * Constructor.
     * @param aApplication The application instance.
     */
    LeahConfIntroForm(Application& aApplication);
    /**
     * Destructor.
     */
    ~LeahConfIntroForm();

public: // From base class
    /**
     * From Form, Create.
     * Creates the child controls.
     */
    void Create();

protected: // From base class
    /**
     * From Control, OnPaint.
     * Paints the control in the graphics context.
     * @param aArgs The Paint event arguments.
     */
    void OnPaint(PaintEventArgs& aArgs);

private: // New functions
    /**
     * Handled for Click event for the Next button.
     * @param aSender The Next button.
     */
    void ButtonNext_Click(Control* aButton);

protected: // Data
    LeahConfApplication* iApplication;

#include "LeahConfIntroForm.xml.h"
    };

#endif //LEAHCONFINTROFORM_H_
