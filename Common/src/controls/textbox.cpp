#include "textbox.h"
#include "handlermethod.h"
#include "propertyadapters.h"
#include "propertybind.h"
#include "descutils.h"
#include "lexutils.h"
#include "application.h"
#include "fontsmanager.h"
#include "numericutils.h"

// Constants
_LIT(KMinTextReference, "MM");

// ----------------------------------------------------------------------------
// TextBox::TextBox
// Constructor.
// ----------------------------------------------------------------------------
//
EXPORT_C TextBox::TextBox()
// Default values for properties
: Color(KRgbBlack)
, BackgroundColor(KRgbTransparent)
, HAlign(HAlignment::ELeft)
, VAlign(VAlignment::ETop)
, LineSpacing(1.5)
    {
    Font = Application::Instance()->Fonts->NormalFont();
    BindTwoWayAdapt(Align, HAlign, &PropertyAdapters::FromAlignmentToHAlignment, &PropertyAdapters::FromHAlignmentToAlignment);
    BindTwoWayAdapt(Align, VAlign, &PropertyAdapters::FromAlignmentToVAlignment, &PropertyAdapters::FromVAlignmentToAlignment);
    Align.ValueChanged += MethodHandler(this, &TextBox::Align_Changed);
    Text.ValueChanged += MethodHandler(this, &TextBox::Text_Changed);
    Font.ValueChanged += MethodHandler(this, &TextBox::Font_Changed);
    ClientRectangle.ValueChanged += MethodHandler(this, &TextBox::ClientRectangle_Changed);
    LineSpacing.ValueChanged += MethodHandler(this, &TextBox::LineSpacing_Changed);
    }

// ----------------------------------------------------------------------------
// TextBox::~TextBox
// Destructor.
// ----------------------------------------------------------------------------
//
EXPORT_C TextBox::~TextBox()
    {
    _linesPositions.Reset();
    _lines.Reset();
    }

// ----------------------------------------------------------------------------
// TextBox::OnPaint
// From Control. Paints the control on the screen.
// ----------------------------------------------------------------------------
//
EXPORT_C void TextBox::OnPaint(PaintEventArgs& aArgs)
    {
    CBitmapContext& gc = aArgs.Graphics();
    gc.SetClippingRect(ClientRectangle);

    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.SetBrushColor(BackgroundColor);
    gc.Clear(aArgs.ClipRectangle());

    gc.SetPenStyle(CGraphicsContext::ESolidPen);
    gc.SetPenColor(Color);
    gc.SetPenSize(TSize(1, 1));
    gc.UseFont(Font);

    ASSERT( _lines.Count() == _linesPositions.Count());
    TInt linesCount = _lines.Count();
    for (TInt i = 0; i < linesCount; ++i)
        {
        gc.DrawText(_lines[i], _linesPositions[i]);
        }
    gc.DiscardFont();

    gc.CancelClippingRect();
    Control::OnPaint(aArgs);
    }

// ----------------------------------------------------------------------------
// TextBox::Layout
// Arranges control components.
// ----------------------------------------------------------------------------
//
void TextBox::Layout()
    {
    Arrange(ClientSize);

    Invalidate();
    }

// ----------------------------------------------------------------------------
// TextBox::Measure
// From Control, Measure. Measures the necessary size.
// ----------------------------------------------------------------------------
//
TSize TextBox::Measure(const TSize& aAvailableSize)
    {
    const CFont& font = *Font;
    TSize preferredSize(0, 0);
    TSize availableSize = aAvailableSize - MarginsSize();
    preferredSize = SplitTextToLines(availableSize, font, LineSpacing);

    preferredSize += MarginsSize();
    ++preferredSize.iHeight;
    PreferredSize = preferredSize;
    return preferredSize;
    }

// ----------------------------------------------------------------------------
// TextBox::Arrange
// Arranges the text in the text box.
// ----------------------------------------------------------------------------
//
TSize TextBox::Arrange(const TSize& aFinalSize)
    {
    _linesPositions.Reset();
    TPoint clientTl = ClientRectangle().iTl;
    const CFont& font = *Font;
    TInt fontMaxHeight = font.FontMaxHeight();
    TSize availableSize = ClientSize;
    SplitTextToLines(availableSize, font, LineSpacing);

    TInt linesCount = _lines.Count();
    TInt lineVerticalPos = DoAlign(VAlign, availableSize.iHeight,
            (TInt)(fontMaxHeight * linesCount + (linesCount - 1) * (LineSpacing - 1) * fontMaxHeight));
    lineVerticalPos += font.FontMaxAscent();
    for (TInt i = 0; i < linesCount; ++i)
        {
        TInt lineHorizPos = DoAlign(HAlign, availableSize.iWidth, font.TextWidthInPixels(_lines[i]));
        _linesPositions.Append(TPoint(lineHorizPos, lineVerticalPos) + clientTl);
        lineVerticalPos += (TInt)(fontMaxHeight * LineSpacing);
        }
    return aFinalSize;
    }

// ----------------------------------------------------------------------------
// TextBox::Align_Changed
// Handels Align property change.
// ----------------------------------------------------------------------------
//
void TextBox::Align_Changed(const PropertyBase<Alignment::Align>& /*aAlign*/)
    {
    LayoutDeferred();
    }

// ----------------------------------------------------------------------------
// TextBox::Text_Changed
// Handels Text property change.
// ----------------------------------------------------------------------------
//
void TextBox::Text_Changed(const PropertyBase<const TDesC&>& /*aText*/)
    {
    LayoutDeferred();
    }

// ----------------------------------------------------------------------------
// TextBox::Font_Changed
// Handels Font property change.
// ----------------------------------------------------------------------------
//
void TextBox::Font_Changed(const PropertyBase<const CFont*>& /*aFont*/)
    {
    LayoutDeferred();
    }

// ----------------------------------------------------------------------------
// TextBox::ClientRectangle_Changed
// Handels ClientRectangle property change.
// ----------------------------------------------------------------------------
//
void TextBox::ClientRectangle_Changed(const PropertyBase<TRect>& /*aClientRect*/)
    {
    LayoutDeferred();
    }

// ----------------------------------------------------------------------------
// TextBox::LineSpacing_Changed
// Handels LineSpacing property change.
// ----------------------------------------------------------------------------
//
void TextBox::LineSpacing_Changed(const PropertyBase<TReal>& /*aLineSpacing*/)
    {
    LayoutDeferred();
    }

// ----------------------------------------------------------------------------
// TextBox::SplitTextToLines
// Splits the text in lines.
// ----------------------------------------------------------------------------
//
TSize TextBox::SplitTextToLines(const TSize& aSize, const CFont& aFont, const TReal& aSpacing)
    {
    _lines.Reset();
    TSize textSize(0, 0);
    if (aSize.iWidth < aFont.TextWidthInPixels(KMinTextReference))
        {
        return textSize;
        }

    const TDesC& text = Text;
    TLex lexxer(text);
    TLexMark lineStartMark, lineEndMark;
    lexxer.SkipSpaceAndMark(lineStartMark);
    TPtrC currentLine;
    TInt newLinePosition = 0;
    TInt wordsInLine = 0;

    while (!lexxer.Eos())
        {
        lexxer.Mark(lineEndMark);
        lexxer.NextToken();
        ++wordsInLine;

        currentLine.Set(lexxer.MarkedToken(lineStartMark));

        if ((newLinePosition = DescUtils::FindNewLine(currentLine)) != KErrNotFound)
            {
            TPtrC line(currentLine.Ptr(), newLinePosition);
            textSize.iWidth = Max(textSize.iWidth, AppendLine(line, aFont));
            LexUtils::SkipMarkBy(lexxer, lineStartMark, newLinePosition + 1);
            currentLine.Set(lexxer.MarkedToken(lineStartMark));
            --wordsInLine;
            }

        while (aFont.TextWidthInPixels(currentLine) > aSize.iWidth)
            {
            if (wordsInLine == 1)
                {
                newLinePosition = DescUtils::GetLineLimit(aSize.iWidth, currentLine, aFont);
                TPtrC line(currentLine.Ptr(), newLinePosition);
                textSize.iWidth = Max(textSize.iWidth, AppendLine(line, aFont));
                LexUtils::SkipMarkBy(lexxer, lineStartMark, newLinePosition);
                currentLine.Set(lexxer.MarkedToken(lineStartMark));
                }
            else
                {
                TPtrC line = LexUtils::TokenBetweenMarks(text, lexxer, lineStartMark, lineEndMark);
                textSize.iWidth = Max(textSize.iWidth, AppendLine(line, aFont));
                lineStartMark = lineEndMark;
                currentLine.Set(lexxer.MarkedToken(lineStartMark));
                wordsInLine = 1;
                }
            }

        lexxer.SkipSpace();
        }

    // Any remainder?
    TPtrC remainder = lexxer.RemainderFromMark(lineStartMark);
    if (remainder.Length() > 0)
        {
        textSize.iWidth = Max(textSize.iWidth, AppendLine(remainder, aFont));
        }
    TInt fontMaxHeight = aFont.FontMaxHeight();
    textSize.iHeight = (TInt)(_lines.Count() * fontMaxHeight +
            (_lines.Count() - 1) * (aSpacing - 1) * fontMaxHeight);
    NumericUtils::LimitSize(textSize, aSize);
    return textSize;
    }

// ----------------------------------------------------------------------------
// TextBox::AppendLine
// Appends a line to the text lines and calculates the line width in pixels
// ----------------------------------------------------------------------------
//
TInt TextBox::AppendLine(const TDesC& aLine, const CFont& aFont)
    {
    _lines.AppendL(aLine);
    return aFont.TextWidthInPixels(aLine);
    }
