#ifndef KEYBOARD_H_
#define KEYBOARD_H_

// USER INCLUDES
#include "control.h"
#include "controlsforwards.h"
#include "layoutforwards.h"

/**
 * Keyboard class.
 * Responsible for displaying a keyboard.
 */
class Keyboard : public Control
    {
public: // Properties
    /// Stores the text displayed.
    PropertyDes Text;
    /// Stores the cursor position.
    Property<TInt> CursorPosition;
    /// The background color
    Property<TRgb> BackgroundColor;
    Property<TRgb> NormalKeyColor;
    Property<TRgb> SpecialKeyColor;

public: // Singleton access
    /**
     * Singleton accessor.
     * @return A reference to the instance.
     */
    inline static Keyboard& Instance();
    /**
     * Destroys the singleton object.
     */
    inline void Destroy();

public: // Constructors and destructors
    /**
     * Default constructor.
     */
    Keyboard();
    /**
     * Destructor.
     */
    ~Keyboard();

public: // From base class
    /**
     * From Control, OnPaint. Paints the keyboard on the screen.
     * @param aArgs The paint event arguments.
     */
    void OnPaint(PaintEventArgs& aArgs);
    /**
     * From Control, Measure.
     * @param aAvailableSize The available size.
     * @return The necessary size for the control.
     */
    TSize Measure(const TSize& aAvailableSize);
    /**
     * From Control, Arrange.
     * @param aFinalSize The final available size.
     * @return The size occupied by the control.
     */
    TSize Arrange(const TSize& aFinalSize);
    /**
     * From Control, creates the keyboard and its children.
     */
    void Create();

private: // New functions
    /**
     * Handles the DragEnter event from a keyboard button.
     * @param aControl The keyboard button.
     * @param aArgs The mouse event args.
     */
    void Button_DragEnter(Control* aControl, DragEventArgs& aArgs);
    /**
     * Handles the DragLeave event from a keyboard button.
     * @param aControl The keyboard button.
     * @param aArgs The mouse event args.
     */
    void Button_DragLeave(Control* aControl);
    /**
     * Creates the letters page.
     */
    void CreateLettersPage();
    /**
     * Creates the numbers page.
     */
    void CreateNumbersPage();
    /**
     * Creates the symbols page.
     */
    void CreateSymbolsPage();
    /**
     * Adds a button to a given container.
     * @param aKeys The keys to add.
     * @param aContainer The container to add to.
     */
    void AddButtons(const TDesC& aKeys, Grid& aGrid, TInt aOffset = 0);
    /**
     * Creates a key button and sets the text and the Grid.Column attached property.
     * @param aText The text.
     * @param aGrid The grid to add the key to.
     * @param aGridColumn The Grid.Column value.
     * @return A pointer to the new instance.
     */
    inline Button* CreateKey(const TDesC& aText, Grid& aGrid, TInt aGridColumn,
            TBool aSpecialColor = EFalse, TBool aSetDragHandlers = EFalse);
    /**
     * Sets the drag handlers for a button.
     * @param aButton The button.
     */
    inline void SetButtonDragHandlers(Button& aButton);
    /**
     * Calculates the popup location for a given button.
     * @param aButton The button to calculate the popup position for.
     * @return The popup position in local coordinates.
     */
    inline TPoint GetPopupLocation(Button& aButton);
    /**
     * Handles Click event for buttons that switch to numeric page.
     * @param aSender The button.
     */
    void NumericButton_Click(Control* aSender);
    /**
     * Handles Click event for buttons that switch to letters page.
     * @param aSender The button.
     */
    void LettersButton_Click(Control* aSender);
    /**
     * Handles Click event for buttons that switch to symbols page.
     * @param aSender The button.
     */
    void SymbolsButton_Click(Control* aSender);

#include "Keyboard.xml.h"
    };

#include "keyboard.inl"

#endif //KEYBOARD_H_
