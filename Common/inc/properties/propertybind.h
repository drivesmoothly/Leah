#ifndef PROPERTYBIND_H_
#define PROPERTYBIND_H_

class RPropertyBase;

/// ===========================================================================
/// PropertyBind
/// ===========================================================================

/**
 * Base class for property binds.
 */
class PropertyBind
    {
protected: // Constructors and destructors
    PropertyBind() {}
    virtual ~PropertyBind() {}

protected: // New functions
    inline void AddBindL(RPropertyBase& aProperty);
    inline void RemoveBind(RPropertyBase& aProperty);

public:
    virtual void UnBind() = 0;
    };

/// ===========================================================================
/// PropertyBindOneWay<Source, Target>
/// ===========================================================================

/**
 * One way binding
 */
template <class Source, class Target>
class PropertyBindOneWay : public PropertyBind
    {
    typedef PropertyBindOneWay<Source, Target> Self;
public: // Constructors and destructor
    PropertyBindOneWay(Source& aSource, Target& aTarget);
    ~PropertyBindOneWay();

public: // From base class
    void UnBind();

public: // New functions
    void OnSourceChanged(const typename Source::BaseType& aSource);

protected: // Data
    Source& iSource;
    Target& iTarget;
    };

/**
 * Creates a new one way binding between two properties.
 * @param aSource The source property.
 * @param aTarget The target property.
 * @return A pointer to a new bind instance.
 */
template <class Source, class Target>
void BindOneWay(Source& aSource, Target& aTarget);

/// ===========================================================================
/// PropertyBindOneWay<Source, Target>
/// ===========================================================================

/**
 * One way binding using data adapters.
 */
template <class Source, class Target, class Adapter>
class PropertyBindOneWayAdapt : public PropertyBind
    {
    typedef PropertyBindOneWayAdapt<Source, Target, Adapter> Self;

public: // Constructors and destructor
    PropertyBindOneWayAdapt(Source& aSource, Target& aTarget, Adapter aAdapter);
    ~PropertyBindOneWayAdapt();

public: // From base class
    void UnBind();

protected: // New functions
    void OnSourceChanged(const typename Source::BaseType& aSource);

private: // Data
    Source& iSource;
    Target& iTarget;
    Adapter iAdapter;
    };

/**
 * Creates a new one way binding with adapter between two properties.
 * @param aSource The source property.
 * @param aTarget The target property.
 * @param aAdapter The adapter between source and target.
 * @return A pointer to a new bind instance.
 */
template <class Source, class Target, class Adapter>
void BindOneWayAdapt(Source& aSource, Target& aTarget, Adapter aAdapter);

/// ===========================================================================
/// PropertyBindTwoWay<Source, Target>
/// ===========================================================================

/**
 * Two way binding
 */
template <class Source, class Target>
class PropertyBindTwoWay : public PropertyBind
    {
    typedef PropertyBindTwoWay<Source, Target> Self;
public: // Constructors and destructor
    PropertyBindTwoWay(Source& aSource, Target& aTarget);
    ~PropertyBindTwoWay();

public: // From base class
    void UnBind();

protected: // New functions
    void OnSourceChanged(const typename Source::BaseType& aSource);
    void OnTargetChanged(const typename Target::BaseType& aTarget);

protected: // Data
    Source& iSource;
    Target& iTarget;
    };

/**
 * Creates a new two way binding between two properties.
 * @param aSource The source property.
 * @param aTarget The target property.
 * @return A pointer to a new bind instance.
 */
template <class Source, class Target>
void BindTwoWay(Source& aSource, Target& aTarget);

/// ===========================================================================
/// PropertyBindOneWay<Source, Target>
/// ===========================================================================

/**
 * One way binding using data adapters.
 */
template <class Source, class Target, class Adapter, class ReverseAdapter>
class PropertyBindTwoWayAdapt : public PropertyBind
    {
    typedef PropertyBindTwoWayAdapt<Source, Target, Adapter, ReverseAdapter> Self;

public: // Constructors and destructor
    PropertyBindTwoWayAdapt(Source& aSource, Target& aTarget,
            Adapter aAdapter, ReverseAdapter aReverseAdapter);
    ~PropertyBindTwoWayAdapt();

public: // From base class
    void UnBind();

protected: // New functions
    void OnSourceChanged(const typename Source::BaseType& aSource);
    void OnTargetChanged(const typename Target::BaseType& aTarget);

private: // Data
    Source& iSource;
    Target& iTarget;
    Adapter iAdapter;
    ReverseAdapter iReverseAdapter;
    };

/**
 * Creates a new one way binding with adapter between two properties.
 * @param aSource The source property.
 * @param aTarget The target property.
 * @param aAdapter The adapter between source and target.
 * @return A pointer to a new bind instance.
 */
template <class Source, class Target, class Adapter, class ReverseAdapter>
void BindTwoWayAdapt(Source& aSource, Target& aTarget,
        Adapter aAdapter, ReverseAdapter aReverseAdapter);

#include "propertybind.inl"

#endif //PROPERTYBIND_H_
