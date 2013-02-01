#ifndef LEAHSERVICECOMMON_H_
#define LEAHSERVICECOMMON_H_

#include <e32std.h>

inline void PanicServer(TInt aReason);
inline void PanicClient(const RMessage2& aMessage, TInt aReason);

#include "LeahServiceCommon.inl"

#endif //LEAHSERVICECOMMON_H_
