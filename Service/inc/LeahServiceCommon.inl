#include "LeahConsts.h"

inline void PanicServer(TInt aReason)
    {
    User::Panic(KLeahServicePanicCategory, aReason);
    }

inline void PanicClient(const RMessage2& aMessage, TInt aReason)
    {
    aMessage.Panic(KLeahServicePanicCategory, aReason);
    }
