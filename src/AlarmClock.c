#include "AlarmClock.h"

typedef struct {
    uint32_t time;
    AlarmCallback callback;
} Alarm;

static Alarm scheduledAlarms[MAX_ALARMS];

static void scheduleAlarm(Alarm *scheduledAlarm, int time, AlarmCallback callback);


void AlarmClock_Init(void)
{

    for (uint8_t i = 0; i < MAX_ALARMS; i++) {
        scheduledAlarms[i].callback = NULL;
        scheduledAlarms[i].time = 0;
    }
}

int SetAlarmClockCallback(int time, AlarmCallback callback)
{
    if (time % ALARMS_MULTIPLE_VALID_VALUE != 0)
        return ALARM_NOT_MULTIPLE_OF_100MS;

    if (time == 0)
        return ALARM_IS_ZERO;

    if (IsAlarmClockTimeSet(time))
        return ALARM_ALREADY_SET;

    for (int i = 0; i < MAX_ALARMS; i++) {
        if (scheduledAlarms[i].time == 0) {
            scheduleAlarm(&scheduledAlarms[i], time, callback);
            return ALARM_SET_OK;
        }
    }

    return ALARM_LIST_FULL;
}

uint32_t GetAmountOfSetAlarms(void)
{
    uint8_t countAlarms = 0;

    for (uint8_t i = 0; i < MAX_ALARMS; i++) {
        if (scheduledAlarms[i].time != 0)
            ++countAlarms;
    }

    return countAlarms;
}

bool IsAlarmClockTimeSet(uint32_t time)
{
    for (uint8_t i = 0; i < MAX_ALARMS; i++) {
        if (scheduledAlarms[i].time == time)
            return true;
    }

    return false;
}

AlarmCallback GetAlarmClockCallbackFromTime(uint32_t time)
{
    for (uint8_t i = 0; i < MAX_ALARMS; i++) {
        if (scheduledAlarms[i].time == time)
            return scheduledAlarms[i].callback;
    }

    return NULL;
}

void RemoveAlarmClock(uint32_t time)
{
    for (uint8_t i = 0; i < MAX_ALARMS; i++) {
        if (scheduledAlarms[i].time == time)
            scheduledAlarms[i].time = 0;
    }
}

static void scheduleAlarm(Alarm *scheduledAlarm, int time, AlarmCallback callback)
{
    scheduledAlarm->time = time;
    scheduledAlarm->callback = callback;
}
