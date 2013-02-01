#ifndef HASHUTILS_H_
#define HASHUTILS_H_

#include <e32hashtab.h>

/**
 * Hash for custom types.
 */
class CustomHash
    {
public:
    IMPORT_C static TUint32 Integer64(const TInt64&);
    };

/**
 * Identity for custom types.
 */
class CustomIdentity
    {
public:
    IMPORT_C static TBool Integer64(const TInt64&, const TInt64&);
    };

/**
 * Additional hash implementations.
 */
template<>
class RHashTableBase::Defaults<TInt64, RHashTableBase::EDefaultSpecifier_Normal>
    {
public:
    inline static TGeneralHashFunction32 Hash();
    inline static TGeneralIdentityRelation Id();
    };
/// Inline implementation
inline TGeneralHashFunction32 RHashTableBase::Defaults<TInt64, RHashTableBase::EDefaultSpecifier_Normal>::Hash()
    {return (TGeneralHashFunction32)&CustomHash::Integer64;}
/// Inline implementation
inline TGeneralIdentityRelation RHashTableBase::Defaults<TInt64, RHashTableBase::EDefaultSpecifier_Normal>::Id()
    {return (TGeneralIdentityRelation)&CustomIdentity::Integer64;}

#endif //HASHUTILS_H_
