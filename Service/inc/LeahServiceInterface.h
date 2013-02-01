#ifndef LEAHSERVICEINTERFACE_H_
#define LEAHSERVICEINTERFACE_H_

enum TLeahServiceFunctions
    {
    ELeahFunctionNone = 0
    };

enum TLeahServiceObserverEvent
    {
    ELeahServiceEventRequestExit, // Server requests application to exit
    ELeahServiceEventCancel
    };

#endif //LEAHSERVICEINTERFACE_H_
