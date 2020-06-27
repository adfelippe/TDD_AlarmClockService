#include "unity.h"
#include "AlarmClock.h"
#include "FakeTimeService.h"

void setUp(void)
{
    AlarmClock_Init();
}

void tearDown(void)
{
    AlarmClock_Deinit();
}

void DummyHello(void)
{
    //DUMMY
}

void DummyHelloA(void)
{
    //DUMMY
}

void fillAlarmList(void)
{
    uint32_t alarmTime = 100;
    for (int i = 0; i < MAX_ALARMS; i++) {
        TEST_ASSERT_EQUAL(ALARM_SET_OK, SetAlarmClockCallback(alarmTime, DummyHello));
        alarmTime += alarmTime;
    }
}

void test_AlarmClock_AlarmCallbackListIsEmptyAfterInitialzation(void)
{
    TEST_ASSERT_EQUAL(0, GetAmountOfSetAlarms());
}

void test_AlarmClock_AlarmDoesNotTriggerAtWrongTime(void)
{
    SetAlarmClockCallback(500, DummyHello);

    FakeTimeService_SetCurrentTimeInMiliseconds(400);

    TEST_ASSERT_EQUAL(EMPTY, FakeTimeService_WakeUpRoutine());
}

void test_AlarmClock_AlarmTriggersAtCorrectTime(void)
{
    SetAlarmClockCallback(500, DummyHello);

    FakeTimeService_SetCurrentTimeInMiliseconds(500);

    TEST_ASSERT_EQUAL(CALLBACK_RUN, FakeTimeService_WakeUpRoutine());
}

void test_AlarmClock_RejectsAlarmsNotMultipleOfOneHundredMilliseconds(void)
{
    TEST_ASSERT_EQUAL(ALARM_NOT_MULTIPLE_OF_100MS, SetAlarmClockCallback(550, DummyHello));
}

void test_AlarmClock_RejectsAlarmsWithZeroValue(void)
{
    TEST_ASSERT_EQUAL(ALARM_IS_ZERO, SetAlarmClockCallback(0, DummyHello));
}

void test_AlarmClock_AcceptsAlarmsMultipleOfOneHundredMilliseconds(void)
{
    TEST_ASSERT_EQUAL(ALARM_SET_OK, SetAlarmClockCallback(1500, DummyHello));
}

void test_AlarmClock_AlarmsCountingReturnCorrectNumberOfCurrentAlarms(void)
{
    SetAlarmClockCallback(100, DummyHello);
    SetAlarmClockCallback(200, DummyHello);
    SetAlarmClockCallback(300, DummyHello);

    TEST_ASSERT_EQUAL(3, GetAmountOfSetAlarms());
}

void test_AlarmClock_MultipleAlarmCallbackAreSetCorrectly(void)
{
    SetAlarmClockCallback(500, DummyHello);
    SetAlarmClockCallback(600, DummyHelloA);

    TEST_ASSERT_TRUE(IsAlarmClockTimeSet(500));
    TEST_ASSERT_EQUAL(DummyHello, GetAlarmClockCallbackFromTime(500));
    TEST_ASSERT_TRUE(IsAlarmClockTimeSet(600));
    TEST_ASSERT_EQUAL(DummyHelloA, GetAlarmClockCallbackFromTime(600));
}

void test_AlarmClock_MultipleAlarmsTriggerAtCorrectTime(void)
{
    SetAlarmClockCallback(500, DummyHello);
    SetAlarmClockCallback(600, DummyHelloA);

    FakeTimeService_SetCurrentTimeInMiliseconds(500);
    TEST_ASSERT_EQUAL(CALLBACK_RUN, FakeTimeService_WakeUpRoutine());

    FakeTimeService_SetCurrentTimeInMiliseconds(600);
    TEST_ASSERT_EQUAL(CALLBACK_RUN, FakeTimeService_WakeUpRoutine());
}

void test_AlarmClock_SettingSameAlarmTimeTwiceIsRejected(void)
{
    TEST_ASSERT_EQUAL(ALARM_SET_OK, SetAlarmClockCallback(500, DummyHello));
    TEST_ASSERT_EQUAL(ALARM_ALREADY_SET, SetAlarmClockCallback(500, DummyHelloA));
}

void test_AlarmClock_RejectsMoreThanMaximumAlarmsAllowed(void)
{
    fillAlarmList();
    TEST_ASSERT_EQUAL(ALARM_LIST_FULL, SetAlarmClockCallback(100000, DummyHello));
}

void test_AlarmClock_RemoveAlarmClockDeleteAlarmTimeFromList(void)
{
    fillAlarmList();
    RemoveAlarmClock(100);
    TEST_ASSERT_FALSE(IsAlarmClockTimeSet(100));
}


void test_AlarmClock_RemoveAlarmClockFreesListSlot(void)
{
    fillAlarmList();
    RemoveAlarmClock(100);
    TEST_ASSERT_EQUAL(ALARM_SET_OK, SetAlarmClockCallback(100, DummyHello));
}

void test_AlarmClock_MultipleAlarmsSetDoNotTriggerAtWrongTimesButTriggerAtRightTimes(void)
{
    SetAlarmClockCallback(500, DummyHello);
    SetAlarmClockCallback(700, DummyHello);

    FakeTimeService_SetCurrentTimeInMiliseconds(400);
    TEST_ASSERT_EQUAL(EMPTY, FakeTimeService_WakeUpRoutine());

    FakeTimeService_SetCurrentTimeInMiliseconds(500);
    TEST_ASSERT_EQUAL(CALLBACK_RUN, FakeTimeService_WakeUpRoutine());

    FakeTimeService_SetCurrentTimeInMiliseconds(600);
    TEST_ASSERT_EQUAL(EMPTY, FakeTimeService_WakeUpRoutine());

    FakeTimeService_SetCurrentTimeInMiliseconds(700);
    TEST_ASSERT_EQUAL(CALLBACK_RUN, FakeTimeService_WakeUpRoutine());
}

void test_AlarmClock_Deinit_Leaves_AlarmsListEmpty(void)
{
    AlarmClock_Deinit();
    TEST_ASSERT_EQUAL(0, GetAmountOfSetAlarms());
}
