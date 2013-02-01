#ifndef PROPERTYREADER_H_
#define PROPERTYREADER_H_

// SYSTEM INCLUDES
#include <e32std.h>
#include <gdi.h>
#include "align.h"
#include "gridsizedefinition.h"
#include "stackpanelorientation.h"

// FORWARDS
template <class T>
class PropertyBase;

/**
 * Reads properties values.
 */
namespace PropertyReader
    {
    /**
     * A structure that holds a symbol and a value for the symbol.
     * Using this structure we create a symbol table that is used to map values with symbols.
     */
    struct SymbolEntry
        {
        TLitC<64>   iSymbol;
        TInt        iValue;
        };
    // Expands a text to a TLitC compatible descriptor value
    #define EXPANDLIT(a) {sizeof(L##a)/2-1,L##a}

    /**
     * Reads a generic property.
     * @remarks Does nothing.
     * @param aProperty The property to read the value for.
     * @param aText The text containing the value.
     */
    template <class T>
    void Read(PropertyBase<T>& /*aProperty*/, const TDesC& /*aText*/) {}

    /**
     * Reads a TInt property.
     * @param aProperty The property to read the value for.
     * @param aText The text containing the value.
     */
    void Read(PropertyBase<TInt>& aProperty, const TDesC& aText);

    /**
     * Reads a TPoint property.
     * @param aProperty The property to read the value for.
     * @param aText The text containing the value.
     */
    void Read(PropertyBase<TPoint>& aProperty, const TDesC& aText);

    /**
     * Reads a TSize property.
     * @param aProperty The property to read the value for.
     * @param aText The text containing the value.
     */
    void Read(PropertyBase<TSize>& aProperty, const TDesC& aText);

    /**
     * Reads a TRect property.
     * @param aProperty The property to read the value for.
     * @param aText The text containing the value.
     */
    void Read(PropertyBase<TRect>& aProperty, const TDesC& aText);

    /**
     * Reads a TDesC property.
     * @param aProperty The property to read the value for.
     * @param aText The text containing the value.
     */
    void Read(PropertyBase<const TDesC&>& aProperty, const TDesC& aText);

    /**
     * Reads a TRgb property.
     * @param aProperty The property to read the value for.
     * @param aText The text containing the value.
     */
    void Read(PropertyBase<TRgb>& aProperty, const TDesC& aText);

    /**
     * Reads a Alignment::Align property.
     * @param aProperty The property to read the value for.
     * @param aText The text containing the value.
     */
    void Read(PropertyBase<Alignment::Align>& aProperty, const TDesC& aText);

    /**
     * Reads a HAlignment::Align property.
     * @param aProperty The property to read the value for.
     * @param aText The text containing the value.
     */
    void Read(PropertyBase<HAlignment::Align>& aProperty, const TDesC& aText);

    /**
     * Reads a Alignment::Align property.
     * @param aProperty The property to read the value for.
     * @param aText The text containing the value.
     */
    void Read(PropertyBase<VAlignment::Align>& aProperty, const TDesC& aText);

    /**
     * Reads a Font property.
     * @param aProperty The property tyo read the value for.
     * @param aText The text containing the value.
     */
    void Read(PropertyBase<const CFont*>& aProperty, const TDesC& aText);

    /**
     * Reads a Grid::BoundsDefinitions property.
     * @param aProperty The property.
     * @param aText The text.
     */
    void Read(PropertyBase<GridBoundsDefinitions&>& aProperty, const TDesC& aText);

    /**
     * Reads a StackPanel::TOrientation property.
     * @param aProperty The property.
     * @param aText The text.
     */
    void Read(PropertyBase<StackPanelOrientation::TOrientation>& aProperty, const TDesC& aText);

    /**
     * Retrieves the value of a symbol.
     * @param aText The text containing the symbol.
     * @return The value of that symbol if found.
     * @remarks Leaves with KErrBadDescriptor if no matching symbol is found.
     */
    TInt GetSymbolValue(const TDesC& aText, const SymbolEntry* aSymbolsTable, TInt aSymbolsCount);
    }


#endif //PROPERTYREADER_H_
