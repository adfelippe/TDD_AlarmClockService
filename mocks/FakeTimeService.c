#include "AlarmClock.h"
#include "FakeTimeService.h"


int currentTimeInMilliseconds = 0;


void FakeTimeService_SetCurrentTimeInMiliseconds(int time)
{
    currentTimeInMilliseconds = time;
}

int FakeTimeService_GetCurrentTimeInMiliseconds(void)
{
    return currentTimeInMilliseconds;
}

int FakeTimeService_WakeUpRoutine(void)
{
    if (IsAlarmClockTimeSet(currentTimeInMilliseconds)) {
        AlarmCallback callback = GetAlarmClockCallbackFromTime(currentTimeInMilliseconds);
        callback();
        return CALLBACK_RUN;
    } else {
        return EMPTY;
    }
}
