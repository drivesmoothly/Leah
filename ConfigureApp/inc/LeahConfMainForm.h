#ifndef LEAHCONFMAINFORM_H_
#define LEAHCONFMAINFORM_H_

// USER INCLUDES
#include "form.h"
#include "layoutforwards.h"
#include "controlsforwards.h"

// FORWARDS
class LeahConfApplication;

/**
 * Main form in the config application/
 */
class LeahConfMainForm : public Form
    {
public: // Constructors and destructor
    /**
     * Constructor.
     * @param aApplication The application instance.
     */
    LeahConfMainForm(Application& aApplication);
    /**
     * Destructor.
     */
    ~LeahConfMainForm();

public: // From base class
    /**
     * From Form, Create.
     * Creates the child controls.
     */
    void Create();

protected: // From base class
    /**
     * From Form, OnPaint.
     * Performs drawing in the given graphics context.
     * @param aArgs The paint event args.
     */
    void OnPaint(PaintEventArgs& aArgs);
    /**
     * From Form, OnKeyPress.
     * @param aArgs The key event arguments.
     */
    void OnKeyPress(KeyPressEventArgs& aArgs);

private: // New functions
    /**
     * Handled for Click event for the Next button.
     * @param aSender The Next button.
     */
    void ButtonNext_Click(Control* aSender);
    /**
     * Handled for Click event for the Back button.
     * @param aSender The Back button.
     */
    void ButtonBack_Click(Control* aSender);

protected: // Data
    LeahConfApplication* iApplication;
#include "LeahConfMainForm.xml.h"
    };

#endif //LEAHCONFMAINFORM_H_
