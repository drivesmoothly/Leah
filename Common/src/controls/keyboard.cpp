#include "keyboard.h"
#include "grid.h"
#include "button.h"
#include "handlermethod.h"
#include "debug.h"

// ----------------------------------------------------------------------------
// Keyboard::Keyboard
// Constructor
// ----------------------------------------------------------------------------
//
Keyboard::Keyboard()
: BackgroundColor(KRgbBlack)
, NormalKeyColor(TRgb(35, 35, 35))
, SpecialKeyColor(KRgbBlack)
    {
    CanFocus = ETrue;
    }

// ----------------------------------------------------------------------------
// Keyboard::~Keyboard
// Destructor.
// ----------------------------------------------------------------------------
//
Keyboard::~Keyboard()
    {
    // No implementation required
    }

// ----------------------------------------------------------------------------
// Keyboard::OnPaint
// Paints the keyboard on the screen
// ----------------------------------------------------------------------------
//
void Keyboard::OnPaint(PaintEventArgs& aArgs)
    {
    CBitmapContext& gc = aArgs.Graphics();
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.SetBrushColor(BackgroundColor);
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.Clear(aArgs.ClipRectangle());

    Control::OnPaint(aArgs);
    }

// ----------------------------------------------------------------------------
// Keyboard::Measure
// Measures the control
// ----------------------------------------------------------------------------
//
TSize Keyboard::Measure(const TSize& aAvailableSize)
    {
    TSize measuredSize = rootLayout->Measure(aAvailableSize);
    PreferredSize = measuredSize;
    return measuredSize;
    }

// ----------------------------------------------------------------------------
// Keyboard::Arrange
// Arranges the keyboard on the screen
// ----------------------------------------------------------------------------
//
TSize Keyboard::Arrange(const TSize& aFinalSize)
    {
    rootLayout->Size = aFinalSize;
    return aFinalSize;
    }

// ----------------------------------------------------------------------------
// Keyboard::Create
// Finalizes the keyboard creation and its children.
// ----------------------------------------------------------------------------
//
void Keyboard::Create()
    {
    Control::Create();

    CreateLettersPage();
    CreateNumbersPage();
    CreateSymbolsPage();
    }

// ----------------------------------------------------------------------------
// Keyboard::Button_MouseDown
// Handles the MouseDown event from a button.
// ----------------------------------------------------------------------------
//
void Keyboard::Button_DragEnter(Control* aControl, DragEventArgs& aArgs)
    {
    TRACE_FUNC_ENTRY;
    if (aArgs.DragSource == aControl)
        {
        Button* button = static_cast<Button*>(aControl);
        popupKey->Text = button->Text;
        popupKey->Location = GetPopupLocation(*button);
        popupKey->Visible = ETrue;
        }
    TRACE_FUNC_EXIT;
    }

// ----------------------------------------------------------------------------
// Keyboard::Button_MouseUp
// Handles the MouseUp event from a button.
// ----------------------------------------------------------------------------
//
void Keyboard::Button_DragLeave(Control* /*aControl*/)
    {
    TRACE_FUNC_ENTRY;
    popupKey->Visible = EFalse;
    TRACE_FUNC_EXIT;
    }

// ----------------------------------------------------------------------------
// Keyboard::CreateLettersPage
// Creates the letters page
// ----------------------------------------------------------------------------
//
void Keyboard::CreateLettersPage()
    {
    Button* button = NULL;
    // row 1
    _LIT(KRow1, "QWERTYUIOP");
    AddButtons(KRow1, *abcRow1, 0);
    // row 2
    _LIT(KRow2, "ASDFGHJKL");
    AddButtons(KRow2, *abcRow2, 1);
    // row 3
    _LIT(KRow3, "ZXCVBNM");
    AddButtons(KRow3, *abcRow3, 1);
    button = CreateKey(_L("^"), *abcRow3, 0, ETrue, EFalse);
    button = CreateKey(_L("<"), *abcRow3, 8, ETrue, ETrue);
    // row 4
    button = CreateKey(_L("123"), *abcRow4, 0, ETrue, EFalse);
    button->Click += MethodHandler(this, &Keyboard::NumericButton_Click);
    button = CreateKey(_L("@"), *abcRow4, 1, EFalse, ETrue);
    button = CreateKey(_L(" "), *abcRow4, 2, EFalse, EFalse);
    button = CreateKey(_L("."), *abcRow4, 3, EFalse, ETrue);
    button = CreateKey(_L("return"), *abcRow4, 4, ETrue, EFalse);
    }

// ----------------------------------------------------------------------------
// Keyboard::CreateNumbersPage
// Creates the numbers page.
// ----------------------------------------------------------------------------
//
void Keyboard::CreateNumbersPage()
    {
    Button* button = NULL;
    // row 1
    _LIT(KNumericRow1, "1234567890");
    AddButtons(KNumericRow1, *numericRow1, 0);
    // row 2
    _LIT(KNumericRow2, "-+/:;()$&\"");
    AddButtons(KNumericRow2, *numericRow2, 0);
    // row 3
    _LIT(KNumericRow3, ".,?!'");
    AddButtons(KNumericRow3, *numericRow3Keys);
    button = CreateKey(_L("#+="), *numericRow3, 0, ETrue, EFalse);
    button->Click += MethodHandler(this, &Keyboard::SymbolsButton_Click);
    button = CreateKey(_L("<"), *numericRow3, 2, ETrue, ETrue);
    // row 4
    button = CreateKey(_L("ABC"), *numericRow4, 0, ETrue, EFalse);
    button->Click += MethodHandler(this, &Keyboard::LettersButton_Click);
    CreateKey(_L("@"), *numericRow4, 1, EFalse, ETrue);
    CreateKey(_L(" "), *numericRow4, 2, EFalse, EFalse);
    CreateKey(_L("."), *numericRow4, 3, EFalse, ETrue);
    CreateKey(_L("return"), *numericRow4, 4, ETrue, EFalse);
    }

// ----------------------------------------------------------------------------
// Keyboard::CreateSymbolsPage
// Creates the symbols page.
// ----------------------------------------------------------------------------
//
void Keyboard::CreateSymbolsPage()
    {
    Button* button = NULL;
    // row1
    _LIT(KSymbolsRow1, "[]{}#%^*+=");
    AddButtons(KSymbolsRow1, *symbolsRow1, 0);
    // row 2
    _LIT(KSymbolsRow2, "_\\|~<>`");
    AddButtons(KSymbolsRow2, *symbolsRow2, 1);
    // row 3
    _LIT(KSymbolsRow3, ".,?!'");
    AddButtons(KSymbolsRow3, *symbolsRow3Keys);
    button = CreateKey(_L("123"), *symbolsRow3, 0, ETrue, EFalse);
    button->Click += MethodHandler(this, &Keyboard::NumericButton_Click);
    CreateKey(_L("<"), *symbolsRow3, 2, ETrue, ETrue);
    // row 4
    button = CreateKey(_L("ABC"), *symbolsRow4, 0, ETrue, EFalse);
    button->Click += MethodHandler(this, &Keyboard::LettersButton_Click);
    CreateKey(_L("@"), *symbolsRow4, 1, EFalse, ETrue);
    CreateKey(_L(" "), *symbolsRow4, 2, EFalse, EFalse);
    CreateKey(_L("."), *symbolsRow4, 3, EFalse, ETrue);
    CreateKey(_L("return"), *symbolsRow4, 4, ETrue, EFalse);
    }

// ----------------------------------------------------------------------------
// Keyboard::AddButtons
// Adds buttons to a given container.
// ----------------------------------------------------------------------------
//
void Keyboard::AddButtons(const TDesC& aKeys, Grid& aGrid, TInt aOffset)
    {
    for (TInt i = aKeys.Length() - 1; i >= 0; --i)
        {
        CreateKey(TPtrC(&aKeys[i], 1), aGrid, aOffset + i, EFalse, ETrue);
        }
    }

// ----------------------------------------------------------------------------
// Keyboard::NumericButton_Click
// Handles Click event for buttons that show numeric page.
// ----------------------------------------------------------------------------
//
void Keyboard::NumericButton_Click(Control* /*aButton*/)
    {
    lettersPage->Hide();
    numbersPage->Show();
    symbolsPage->Hide();
    Invalidate();
    }

// ----------------------------------------------------------------------------
// Keyboard::LettersButton_Click
// Handles Click event for buttons that show letters page.
// ----------------------------------------------------------------------------
//
void Keyboard::LettersButton_Click(Control* /*aSender*/)
    {
    lettersPage->Show();
    numbersPage->Hide();
    symbolsPage->Hide();
    Invalidate();
    }

// ----------------------------------------------------------------------------
// Keyboard::SymbolsButton_Click
// Handles Click event for buttons taht show symbols page.
// ----------------------------------------------------------------------------
//
void Keyboard::SymbolsButton_Click(Control* /*aSender*/)
    {
    lettersPage->Hide();
    numbersPage->Hide();
    symbolsPage->Show();
    Invalidate();
    }
