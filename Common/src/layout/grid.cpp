// USER INCLUDES
#include "grid.h"
#include "numericutils.h"
#include "defaultpropertystore.h"

/// Attached properties initialization
Property<TInt>* const Grid::Column = NULL;
Property<TInt>* const Grid::Row = NULL;
Property<TInt>* const Grid::ColumnSpan = NULL;
Property<TInt>* const Grid::RowSpan = NULL;

/// Attached properties default values
TInt Grid::DefaultColumn = 0;
TInt Grid::DefaultRow = 0;
TInt Grid::DefaultColumnSpan = 1;
TInt Grid::DefaultRowSpan = 1;

// ----------------------------------------------------------------------------
// Grid::Grid
// Constructor.
// ----------------------------------------------------------------------------
//
Grid::Grid()
: ColumnDefinitions(*this, &Grid::GetColumnDefinitions, &Grid::SetColumnDefinitions)
, RowDefinitions(*this, &Grid::GetRowDefinitions, &Grid::SetRowDefinitions)
    {
    _columnDefinitions.AppendL(GridSizeDefinition());
    _rowDefinitions.AppendL(GridSizeDefinition());
    }

// ----------------------------------------------------------------------------
// Grid::~Grid
// Destructor.
// ----------------------------------------------------------------------------
//
Grid::~Grid()
    {
    _columnDefinitions.Reset();
    _rowDefinitions.Reset();
    }

// ----------------------------------------------------------------------------
// Grid::SetColumn
// Sets Column attached property.
// ----------------------------------------------------------------------------
//
void Grid::SetColumn(AttachedPropertyStore& aStore, TInt aColumn)
    {
    aStore.SetValue(&Grid::Column, aColumn);
    }

// ----------------------------------------------------------------------------
// Grid::GetColumn
// Retrieves the Column attached property.
// ----------------------------------------------------------------------------
//
Property<TInt>& Grid::GetColumn(AttachedPropertyStore& aStore)
    {
    Property<TInt>* property = aStore.GetValue(&Grid::Column);
    if (!property)
        {
        property = DefaultPropertyStore::Instance().GetValue(&Grid::Column, DefaultColumn);
        ASSERT(property);
        }
    return *property;
    }

// ----------------------------------------------------------------------------
// Grid::SetRow
// Sets Row attached property.
// ----------------------------------------------------------------------------
//
void Grid::SetRow(AttachedPropertyStore& aStore, TInt aRow)
    {
    aStore.SetValue(&Grid::Row, aRow);
    }

// ----------------------------------------------------------------------------
// Grid::GetRow
// Retrieves the Row attached property.
// ----------------------------------------------------------------------------
//
Property<TInt>& Grid::GetRow(AttachedPropertyStore& aStore)
    {
    Property<TInt>* property = aStore.GetValue(&Grid::Row);
    if (!property)
        {
        property = DefaultPropertyStore::Instance().GetValue(&Grid::Row, DefaultRow);
        ASSERT(property);
        }
    return *property;
    }

// ----------------------------------------------------------------------------
// Grid::SetColumnSpan
// Sets ColumnSpan attached property.
// ----------------------------------------------------------------------------
//
void Grid::SetColumnSpan(AttachedPropertyStore& aStore, TInt aColumnSpan)
    {
    aStore.SetValue(&Grid::ColumnSpan, aColumnSpan);
    }

// ----------------------------------------------------------------------------
// Grid::GetColumnSpan
// Retrieves the ColumnSpan attached property.
// ----------------------------------------------------------------------------
//
Property<TInt>& Grid::GetColumnSpan(AttachedPropertyStore& aStore)
    {
    Property<TInt>* property = aStore.GetValue(&Grid::ColumnSpan);
    if (!property)
        {
        property = DefaultPropertyStore::Instance().GetValue(&Grid::ColumnSpan, DefaultColumnSpan);
        ASSERT(property);
        }
    return *property;
    }

// ----------------------------------------------------------------------------
// Grid::SetRowSpan
// Sets RowSpan attached property.
// ----------------------------------------------------------------------------
//
void Grid::SetRowSpan(AttachedPropertyStore& aStore, TInt aRowSpan)
    {
    aStore.SetValue(&Grid::RowSpan, aRowSpan);
    }

// ----------------------------------------------------------------------------
// Grid::GetRowSpan
// Retrieves the RowSpan attached property.
// ----------------------------------------------------------------------------
//
Property<TInt>& Grid::GetRowSpan(AttachedPropertyStore& aStore)
    {
    Property<TInt>* property = aStore.GetValue(&Grid::RowSpan);
    if (!property)
        {
        property = DefaultPropertyStore::Instance().GetValue(&Grid::RowSpan, DefaultRowSpan);
        ASSERT(property);
        }
    return *property;
    }

// ----------------------------------------------------------------------------
// Grid::GetColumnDefinitions
// Retrieves the column definitions
// ----------------------------------------------------------------------------
//
GridBoundsDefinitions& Grid::GetColumnDefinitions() const
    {
    return _columnDefinitions;
    }

// ----------------------------------------------------------------------------
// Grid::SetColumnDefinitions
// Sets the column definitions.
// ----------------------------------------------------------------------------
//
void Grid::SetColumnDefinitions(GridBoundsDefinitions& aColumnDefinitions)
    {
    _columnDefinitions.Reset();
    for (TInt i  = 0; i < aColumnDefinitions.Count(); ++i)
        {
        _columnDefinitions.AppendL(aColumnDefinitions[i]);
        }
    }

// ----------------------------------------------------------------------------
// Grid::GetRowDefinitions
// Retrieves the row definitions
// ----------------------------------------------------------------------------
//
GridBoundsDefinitions& Grid::GetRowDefinitions() const
    {
    return _rowDefinitions;
    }

// ----------------------------------------------------------------------------
// Grid::SetRowDefinitions
// Sets the row definitions
// ----------------------------------------------------------------------------
//
void Grid::SetRowDefinitions(GridBoundsDefinitions& aRowDefinitions)
    {
    _rowDefinitions.Reset();
    for (TInt i = 0; i < aRowDefinitions.Count(); ++i)
        {
        _rowDefinitions.AppendL(aRowDefinitions[i]);
        }
    }

// ----------------------------------------------------------------------------
// Grid::Layout
// Performs layout.
// ----------------------------------------------------------------------------
//
void Grid::Layout()
    {
    Arrange(Size);
    }

// ----------------------------------------------------------------------------
// Grid::Measure
// From Panel, Measure. Measures the necessary size for the grid.
// ----------------------------------------------------------------------------
//
TSize Grid::Measure(const TSize& aAvailableSize)
    {
    // The measurement is done in 3 steps:
    // 1. Rows and columns with fixed width and height by fixed width and height
    // 2. Cells with Auto width by Auto height
    // 3. Remaining rows and columns - the ones with Weight factor

    TSize size(0, 0);
    TSize availableSize = aAvailableSize - MarginsSize();
    ResetActualSize();

    // Step 1
    SetFixedSizeRowsAndColumns();

    // Step 2
    availableSize = aAvailableSize - MarginsSize() - CountActualSize();
    SetAutoSizeCells(availableSize);

    // Step 3
    availableSize = aAvailableSize - MarginsSize() - CountActualSize();
    SetWeightSizeRowsAndColumns(availableSize);

    size = CountActualSize();
    size += MarginsSize();
    NumericUtils::LimitSize(size, aAvailableSize);
    PreferredSize = size;
    return size;
    }

// ----------------------------------------------------------------------------
// Grid::Arrange
// From Panel, Arrange. Arranges the child controls in the grid.
// ----------------------------------------------------------------------------
//
TSize Grid::Arrange(const TSize& aFinalSize)
    {
    Measure(aFinalSize);
    const RControlsArray& controls = Controls;
    for (TInt i = 0; i < controls.Count(); ++i)
        {
        Control& control = *controls[i];
        TPoint position(GetColumn(control), GetRow(control));
        ASSERT(Rng(0, position.iX, _columnDefinitions.Count()));
        ASSERT(Rng(0, position.iY, _rowDefinitions.Count()));
        TSize cellSize(_columnDefinitions[position.iX].iActualValue, _rowDefinitions[position.iY].iActualValue);
        control.Measure(cellSize);
        TRect controlBounds(TPoint(ColumnOffset(position.iX), RowOffset(position.iY)), control.PreferredSize);

        if (control.HorizontalAlignment == HAlignment::EStretch)
            {
            controlBounds.SetWidth(cellSize.iWidth);
            }
        else
            {
            controlBounds.Move(DoAlign(control.HorizontalAlignment, cellSize.iWidth, controlBounds.Width()), 0);
            }
        if (control.VerticalAlignment == VAlignment::EStretch)
            {
            controlBounds.SetHeight(cellSize.iHeight);
            }
        else
            {
            controlBounds.Move(0, DoAlign(control.VerticalAlignment, cellSize.iHeight, controlBounds.Height()));
            }

        control.Bounds = controlBounds;
        }
    return aFinalSize;
    }

// ----------------------------------------------------------------------------
// Grid::MeasureFixedSizeRowsAndColumns
// Measures the size required by fixed rows heights and columns widths.
// ----------------------------------------------------------------------------
//
void Grid::SetFixedSizeRowsAndColumns()
    {
    for (TInt i = 0; i < _columnDefinitions.Count(); ++i)
        {
        if (_columnDefinitions[i].iType == GridSizeDefinition::EPixels)
            {
            _columnDefinitions[i].iActualValue = _columnDefinitions[i].iValue;
            }
        }
    for (TInt i = 0; i < _rowDefinitions.Count(); ++i)
        {
        if (_rowDefinitions[i].iType == GridSizeDefinition::EPixels)
            {
            _rowDefinitions[i].iActualValue = _rowDefinitions[i].iValue;
            }
        }
    }

void Grid::SetAutoSizeCells(const TSize& aAvailableSize)
    {
    const RControlsArray& controls = Controls;
    RControlsArray measuredControls;

    for (TInt c = 0; c < _columnDefinitions.Count(); ++c)
        {
        if (_columnDefinitions[c].iType == GridSizeDefinition::EAuto)
            {
            for (TInt i = 0; i < controls.Count(); ++i)
                {
                Control& control = *controls[i];
                if (GetColumn(control) == c)
                    {
                    TSize controlSize = control.Measure(aAvailableSize);
                    measuredControls.AppendL(&control);
                    _columnDefinitions[c].iActualValue = Max(_columnDefinitions[c].iActualValue, controlSize.iWidth);
                    }
                }
            }
        }

    for (TInt r = 0; r < _rowDefinitions.Count(); ++r)
        {
        if (_rowDefinitions[r].iType == GridSizeDefinition::EAuto)
            {
            for (TInt i = 0; i < controls.Count(); ++i)
                {
                Control& control = *controls[i];
                if (GetRow(control) == r)
                    {
                    TSize controlSize(0, 0);
                    // Make sure the same control is not measured twice
                    if (measuredControls.Find(&control) != KErrNotFound)
                        {
                        // Control was already measured
                        controlSize = control.PreferredSize;
                        }
                    else
                        {
                        // Control was not measured
                        controlSize = control.Measure(aAvailableSize);
                        }
                    _rowDefinitions[r].iActualValue = Max(_rowDefinitions[r].iActualValue, controlSize.iHeight);
                    }
                }
            }
        }
    measuredControls.Reset();
    }

void Grid::SetWeightSizeRowsAndColumns(const TSize& aAvailableSize)
    {
    TRealSize totalWeight = CountWeight();
    TSize availableSize = aAvailableSize;
    for (TInt c = 0; c < _columnDefinitions.Count(); ++c)
        {
        GridSizeDefinition& column = _columnDefinitions[c];
        if (column.iType == GridSizeDefinition::EWeight)
            {
            column.iActualValue = availableSize.iWidth - availableSize.iWidth * (totalWeight.iWidth - column.iValue) / totalWeight.iWidth;
            availableSize.iWidth -= column.iActualValue;
            totalWeight.iWidth -= column.iValue;
            }
        }
    for (TInt r = 0; r < _rowDefinitions.Count(); ++r)
        {
        GridSizeDefinition& row = _rowDefinitions[r];
        if (row.iType == GridSizeDefinition::EWeight)
            {
            row.iActualValue = availableSize.iHeight - availableSize.iHeight * (totalWeight.iHeight - row.iValue) / totalWeight.iHeight;
            availableSize.iHeight -= row.iActualValue;
            totalWeight.iHeight -= row.iValue;
            }
        }
    }

void Grid::ResetActualSize()
    {
    for (TInt i = 0; i < _columnDefinitions.Count(); ++i)
        {
        _columnDefinitions[i].iActualValue = 0;
        }
    for (TInt i = 0; i < _rowDefinitions.Count(); ++i)
        {
        _rowDefinitions[i].iActualValue = 0;
        }
    }

TSize Grid::CountActualSize()
    {
    TSize size(0, 0);
    for (TInt i = 0; i < _columnDefinitions.Count(); ++i)
        {
        size.iWidth += _columnDefinitions[i].iActualValue;
        }
    for (TInt i = 0; i < _rowDefinitions.Count(); ++i)
        {
        size.iHeight += _rowDefinitions[i].iActualValue;
        }
    return size;
    }

TRealSize Grid::CountWeight()
    {
    TRealSize weight(0, 0);
    for (TInt i = 0; i < _columnDefinitions.Count(); ++i)
        {
        if (_columnDefinitions[i].iType == GridSizeDefinition::EWeight)
            {
            weight.iWidth += _columnDefinitions[i].iValue;
            }
        }
    for (TInt i = 0; i < _rowDefinitions.Count(); ++i)
        {
        if (_rowDefinitions[i].iType == GridSizeDefinition::EWeight)
            {
            weight.iHeight += _rowDefinitions[i].iValue;
            }
        }
    return weight;
    }

TInt Grid::ColumnOffset(TInt aColumnIndex)
    {
    TInt offset = Margin().iTl.iX;
    for (TInt i = 0; i < aColumnIndex; ++i)
        {
        offset += _columnDefinitions[i].iActualValue;
        }
    return offset;
    }

TInt Grid::RowOffset(TInt aRowIndex)
    {
    TInt offset = Margin().iTl.iY;
    for (TInt i = 0; i < aRowIndex; ++i)
        {
        offset += _rowDefinitions[i].iActualValue;
        }
    return offset;
    }
