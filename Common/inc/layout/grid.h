#ifndef GRID_H_
#define GRID_H_

// USER INCLUDES
#include "panel.h"
#include "arrayutils.h"
#include "gridsizedefinition.h"
#include "realsize.h"

// FORWARDS
class AttachedPropertyStore;

/**
 * Grid layout class responsible for arranging controls in a grid.
 */
class Grid : public Panel
    {
public: // Properties
    /// Number of columns
    PropertyExt<GridBoundsDefinitions&, Grid> ColumnDefinitions;
    /// Number of rows
    PropertyExt<GridBoundsDefinitions&, Grid> RowDefinitions;

public: // Attached properties
    static Property<TInt>* const Column;
    static Property<TInt>* const Row;
    static Property<TInt>* const ColumnSpan;
    static Property<TInt>* const RowSpan;

protected: // Default values for attached properties
    static TInt DefaultColumn;
    static TInt DefaultRow;
    static TInt DefaultColumnSpan;
    static TInt DefaultRowSpan;

public: // Constructors and destructor.
    /**
     * Constructor.
     */
    Grid();
    /**
     * Destructor.
     */
    ~Grid();

public: // From base class
    /**
     * From Panel, Measure. Measures the necessary size of the grid.
     * @param aAvailableSize The available maximum size.
     * @return The necessary size.
     */
    TSize Measure(const TSize& aAvailableSize);
    /**
     * From Panel, Arrange. Arrarnges the controls in the grid.
     * @param aFinalSize The final size available for the grid.
     * @return The necessary size.
     */
    TSize Arrange(const TSize& aFinalSize);

public: // Attached properties support
    /**
     * Column attached property setter.
     * @param aStore The store to set the property to.
     * @param aColumn The property value.
     */
    static void SetColumn(AttachedPropertyStore& aStore, TInt aColumn);
    /**
     * Column attached property getter.
     * @param aStore The store to get the property from.
     * @return The property value.
     */
    static Property<TInt>& GetColumn(AttachedPropertyStore& aStore);
    static void SetRow(AttachedPropertyStore& aStore, TInt aRow);
    static Property<TInt>& GetRow(AttachedPropertyStore& aStore);
    static void SetColumnSpan(AttachedPropertyStore& aStore, TInt aColumnSpan);
    static Property<TInt>& GetColumnSpan(AttachedPropertyStore& aStore);
    static void SetRowSpan(AttachedPropertyStore& aStore, TInt aRowSpan);
    static Property<TInt>& GetRowSpan(AttachedPropertyStore& aStore);

protected: // External properties support
    GridBoundsDefinitions& GetColumnDefinitions() const;
    void SetColumnDefinitions(GridBoundsDefinitions& aColumnDefinitions);
    GridBoundsDefinitions& GetRowDefinitions() const;
    void SetRowDefinitions(GridBoundsDefinitions& aRowDefinitions);

protected: // From base clases
    /**
     * From Panel, Layout.
     * Performs layout.
     */
    void Layout();

private: // New functions
    void SetFixedSizeRowsAndColumns();
    void SetAutoSizeCells(const TSize& aAvailableSize);
    void SetWeightSizeRowsAndColumns(const TSize& aAvailableSize);
    void ResetActualSize();
    TSize CountActualSize();
    TRealSize CountWeight();
    TInt ColumnOffset(TInt aColumnIndex);
    TInt RowOffset(TInt aRowIndex);

private: // Data
    /// Stores the column definitions
    mutable GridBoundsDefinitions _columnDefinitions;
    /// Stores the row definitions
    mutable GridBoundsDefinitions _rowDefinitions;
    };

#endif //GRID_H_
