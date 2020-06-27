#include "unity.h"
#include "FakeTimeService.h"
#include "AlarmClock.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_FakeTimeService_SetCurrentTimeCorrectly(void)
{
    FakeTimeService_SetCurrentTimeInMiliseconds(500);
    TEST_ASSERT_EQUAL(500, FakeTimeService_GetCurrentTimeInMiliseconds());
}

void test_FakeTimeService_WakeUpRoutineReturnEmptyIfNoAlarmIsConfiguredForCurrentTime(void)
{
    FakeTimeService_SetCurrentTimeInMiliseconds(400);
    TEST_ASSERT_EQUAL(EMPTY, FakeTimeService_WakeUpRoutine());
}
