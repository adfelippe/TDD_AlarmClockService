#ifndef ALARMCLOCK_H
#define ALARMCLOCK_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define ALARMS_MULTIPLE_VALID_VALUE     100
#define MAX_ALARMS                      10

enum {ALARM_LIST_FULL = -4,
      ALARM_ALREADY_SET = -3,
      ALARM_IS_ZERO = -2,
      ALARM_NOT_MULTIPLE_OF_100MS = -1,
      ALARM_SET_OK = 0};
enum {ALARM_UNSET = 0, ALARM_SET = 1};

typedef void (*AlarmCallback)(void);

void AlarmClock_Init(void);
int SetAlarmClockCallback(int time, AlarmCallback callback);
uint32_t GetAmountOfSetAlarms(void);
bool IsAlarmClockTimeSet(uint32_t time);
AlarmCallback GetAlarmClockCallbackFromTime(uint32_t time);
void RemoveAlarmClock(uint32_t time);

#endif // ALARMCLOCK_H
