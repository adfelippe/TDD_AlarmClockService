#include "AlarmClock.h"

typedef struct {
    uint32_t time;
    AlarmCallback callback;
} Alarm;

static Alarm scheduledAlarms[MAX_ALARMS];

static void scheduleAlarm(int8_t alarmSlot, uint32_t time, AlarmCallback callback);
static int8_t getAlarmTimePositionFromList(uint32_t time);
static void clearScheduledAlarms(void);
static bool IsTimeMultipleOf100ms(uint32_t time);
static int8_t FindEmptyAlarmSlot(void);


void AlarmClock_Init(void)
{
    clearScheduledAlarms();
}

void AlarmClock_Deinit(void)
{
    clearScheduledAlarms();
}

int SetAlarmClockCallback(int time, AlarmCallback callback)
{
    if (!time)
        return ALARM_IS_ZERO;

    if (!IsTimeMultipleOf100ms(time))
        return ALARM_NOT_MULTIPLE_OF_100MS;

    if (IsAlarmClockTimeSet(time))
        return ALARM_ALREADY_SET;

    int8_t emptyAlarmSlot = FindEmptyAlarmSlot();

    if (emptyAlarmSlot < 0) {
        return ALARM_LIST_FULL;
    } else {
        scheduleAlarm(emptyAlarmSlot, time, callback);
        return ALARM_SET_OK;
    }
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
    if (getAlarmTimePositionFromList(time) < 0)
        return false;
    else
        return true;
}

AlarmCallback GetAlarmClockCallbackFromTime(uint32_t time)
{

    int8_t alarmTimeIndexPosition = getAlarmTimePositionFromList(time);

    if (alarmTimeIndexPosition < 0) {
        return NULL;
    } else {
        return scheduledAlarms[alarmTimeIndexPosition].callback;
    }
}

void RemoveAlarmClock(uint32_t time)
{
    int8_t alarmTimeIndexPosition = getAlarmTimePositionFromList(time);

    if (alarmTimeIndexPosition >= 0) {
        scheduledAlarms[alarmTimeIndexPosition].time = 0;
    }
}

static int8_t getAlarmTimePositionFromList(uint32_t time)
{
    for (uint8_t i = 0; i < MAX_ALARMS; i++) {
        if (scheduledAlarms[i].time == time)
            return i;
    }

    return -1;
}

static void scheduleAlarm(int8_t alarmSlot, uint32_t time, AlarmCallback callback)
{
    scheduledAlarms[alarmSlot].time = time;
    scheduledAlarms[alarmSlot].callback = callback;
}

static void clearScheduledAlarms(void)
{
    for (uint8_t i = 0; i < MAX_ALARMS; i++) {
        scheduledAlarms[i].callback = NULL;
        scheduledAlarms[i].time = 0;
    }
}

static bool IsTimeMultipleOf100ms(uint32_t time)
{
    if (time % ALARMS_MULTIPLE_VALID_VALUE == 0)
        return true;
    else
        return false;
}

static int8_t FindEmptyAlarmSlot(void)
{
    for (int8_t i = 0; i < MAX_ALARMS; i++) {
        if (scheduledAlarms[i].time == 0)
            return i;
    }

    return -1;
}
