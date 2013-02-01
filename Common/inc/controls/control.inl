/*
 * Filename: control.inl
 *
 * Template implementations
 */


template <typename Event>
void Control::TriggerEvent(Event& aEvent)
    {
    if (Enabled)
        {
        aEvent();
        }
    }

template <typename Event, typename Arg1>
void Control::TriggerEvent(Event& aEvent, Arg1& aArg1)
    {
    if (Enabled)
        {
        aEvent(aArg1);
        }
    }

template <typename Event, typename Arg1, typename Arg2>
void Control::TriggerEvent(Event& aEvent, Arg1& aArg1, Arg2& aArg2)
    {
    if (Enabled)
        {
        aEvent(aArg1, aArg2);
        }
    }

template <typename Event, typename Arg1, typename Arg2, typename Arg3>
void Control::TriggerEvent(Event& aEvent, Arg1& aArg1, Arg2& aArg2, Arg3& aArg3)
    {
    if (Enabled)
        {
        aEvent(aArg1, aArg2, aArg3);
        }
    }
