#include "handlermethod.h"
#include "property.h"

/// ===========================================================================
/// PropertyBind
/// ===========================================================================

void PropertyBind::AddBindL(RPropertyBase& aProperty)
    {
    aProperty.AddBindL(*this);
    }

void PropertyBind::RemoveBind(RPropertyBase& aProperty)
    {
    aProperty.RemoveBind(*this);
    }

/// ===========================================================================
/// PropertyBindOneWay<Source, Target>
/// ===========================================================================

template <class Source, class Target>
PropertyBindOneWay<Source, Target>::PropertyBindOneWay(Source& aSource, Target& aTarget)
: iSource(aSource), iTarget(aTarget)
    {
    iSource.ValueChanged += MethodHandler(this, &Self::OnSourceChanged);
    AddBindL(iSource);
    AddBindL(iTarget);
    }

template <class Source, class Target>
PropertyBindOneWay<Source, Target>::~PropertyBindOneWay()
    {
    }

template <class Source, class Target>
void PropertyBindOneWay<Source, Target>::UnBind()
    {
    iSource.ValueChanged -= MethodHandler(this, &Self::OnSourceChanged);
    RemoveBind(iSource);
    RemoveBind(iTarget);
    delete this;
    }

template <class Source, class Target>
void PropertyBindOneWay<Source, Target>::OnSourceChanged(
        const typename Source::BaseType& /*aSource*/)
    {
    iTarget = iSource;
    }

/// ===========================================================================
/// PropertyBindOneWay<Source, Target> - FACTORY
/// ===========================================================================

template <class Source, class Target>
void BindOneWay(Source& aSource, Target& aTarget)
    {
    new (ELeave) PropertyBindOneWay<Source, Target>(aSource, aTarget);
    aTarget = aSource;
    }

/// ===========================================================================
/// PropertyBindOneWayAdapt<Source, Target>
/// ===========================================================================

template <class Source, class Target, class Adapter>
PropertyBindOneWayAdapt<Source, Target, Adapter>::PropertyBindOneWayAdapt(
        Source& aSource, Target& aTarget, Adapter aAdapter)
        : iSource(aSource), iTarget(aTarget), iAdapter(aAdapter)
    {
    iSource.ValueChanged += MethodHandler(this, &Self::OnSourceChanged);
    AddBindL(iSource);
    AddBindL(iTarget);
    }

template <class Source, class Target, class Adapter>
PropertyBindOneWayAdapt<Source, Target, Adapter>::~PropertyBindOneWayAdapt()
    {
    // No implementation required
    }

template <class Source, class Target, class Adapter>
void PropertyBindOneWayAdapt<Source, Target, Adapter>::UnBind()
    {
    iSource.ValueChanged -= MethodHandler(this, &Self::OnSourceChanged);
    RemoveBind(iSource);
    RemoveBind(iTarget);
    delete this;
    }

template <class Source, class Target, class Adapter>
void PropertyBindOneWayAdapt<Source, Target, Adapter>::OnSourceChanged(
        const typename Source::BaseType& /*aSource*/)
    {
    (*iAdapter)(iSource, iTarget);
    }

/// ===========================================================================
/// PropertyBindOneWayAdapt<Source, Target> - FACTORY
/// ===========================================================================

template <class Source, class Target, class Adapter>
void BindOneWayAdapt(Source& aSource, Target& aTarget, Adapter aAdapter)
    {
    new (ELeave) PropertyBindOneWayAdapt<Source, Target, Adapter>(aSource, aTarget, aAdapter);
    (*aAdapter)(aSource, aTarget);
    }

/// ===========================================================================
/// PropertyBindTwoWay<Source, Target>
/// ===========================================================================

template <class Source, class Target>
PropertyBindTwoWay<Source, Target>::PropertyBindTwoWay(Source& aSource, Target& aTarget)
: iSource(aSource), iTarget(aTarget)
    {
    iSource.ValueChanged += MethodHandler(this, &Self::OnSourceChanged);
    AddBindL(iSource);

    iTarget.ValueChanged += MethodHandler(this, &Self::OnTargetChanged);
    AddBindL(iTarget);
    }

template <class Source, class Target>
PropertyBindTwoWay<Source, Target>::~PropertyBindTwoWay()
    {
    // No implementation required
    }

template <class Source, class Target>
void PropertyBindTwoWay<Source, Target>::UnBind()
    {
    iSource.ValueChanged -= MethodHandler(this, &Self::OnSourceChanged);
    RemoveBind(iSource);

    iTarget.ValueChanged -= MethodHandler(this, &Self::OnTargetChanged);
    RemoveBind(iTarget);

    delete this;
    }

template <class Source, class Target>
void PropertyBindTwoWay<Source, Target>::OnSourceChanged(
        const typename Source::BaseType& /*aSource*/)
    {
    iTarget = iSource;
    }

template <class Source, class Target>
void PropertyBindTwoWay<Source, Target>::OnTargetChanged(
        const typename Target::BaseType& /*aTarget*/)
    {
    iSource = iTarget;
    }

/// ===========================================================================
/// PropertyBindTwoWay<Source, Target> - FACTORY
/// ===========================================================================

template <class Source, class Target>
void BindTwoWay(Source& aSource, Target& aTarget)
    {
    new (ELeave) PropertyBindTwoWay<Source, Target>(aSource, aTarget);
    aTarget = aSource;
    }

/// ===========================================================================
/// PropertyBindTwoWayAdapt<Source, Target, Adapter, ReverseAdapter>
/// ===========================================================================

template <class Source, class Target, class Adapter, class ReverseAdapter>
PropertyBindTwoWayAdapt<Source, Target, Adapter, ReverseAdapter>::PropertyBindTwoWayAdapt(
        Source& aSource, Target& aTarget, Adapter aAdapter, ReverseAdapter aReverseAdapter)
        : iSource(aSource), iTarget(aTarget), iAdapter(aAdapter), iReverseAdapter(aReverseAdapter)
    {
    iSource.ValueChanged += MethodHandler(this, &Self::OnSourceChanged);
    AddBindL(iSource);

    iTarget.ValueChanged += MethodHandler(this, &Self::OnTargetChanged);
    AddBindL(iTarget);
    }

template <class Source, class Target, class Adapter, class ReverseAdapter>
PropertyBindTwoWayAdapt<Source, Target, Adapter, ReverseAdapter>::~PropertyBindTwoWayAdapt()
    {
    // No implementation required
    }

template <class Source, class Target, class Adapter, class ReverseAdapter>
void PropertyBindTwoWayAdapt<Source, Target, Adapter, ReverseAdapter>::UnBind()
    {
    iSource.ValueChanged -= MethodHandler(this, &Self::OnSourceChanged);
    RemoveBind(iSource);

    iTarget.ValueChanged -= MethodHandler(this, &Self::OnTargetChanged);
    RemoveBind(iTarget);

    delete this;
    }

template <class Source, class Target, class Adapter, class ReverseAdapter>
void PropertyBindTwoWayAdapt<Source, Target, Adapter, ReverseAdapter>::OnSourceChanged(
        const typename Source::BaseType& /*aSource*/)
    {
    (*iAdapter)(iSource, iTarget);
    }

template <class Source, class Target, class Adapter, class ReverseAdapter>
void PropertyBindTwoWayAdapt<Source, Target, Adapter, ReverseAdapter>::OnTargetChanged(
        const typename Target::BaseType& /*aTarget*/)
    {
    (*iReverseAdapter)(iTarget, iSource);
    }

/// ===========================================================================
/// PropertyBindTwoWayAdapt<Source, Target, Adapter, ReverseAdapter> - FACTORY
/// ===========================================================================

template <class Source, class Target, class Adapter, class ReverseAdapter>
void BindTwoWayAdapt(Source& aSource, Target& aTarget,
        Adapter aAdapter, ReverseAdapter aReverseAdapter)
    {
    new (ELeave) PropertyBindTwoWayAdapt<Source, Target, Adapter, ReverseAdapter>(
            aSource, aTarget, aAdapter, aReverseAdapter);
    (*aAdapter)(aSource, aTarget);
    }
