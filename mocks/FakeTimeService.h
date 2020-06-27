#ifndef FAKETIMESERVICE_H
#define FAKETIMESERVICE_H

enum {EMPTY = 0, CALLBACK_RUN = 1};

void FakeTimeService_SetCurrentTimeInMiliseconds(int time);
int FakeTimeService_GetCurrentTimeInMiliseconds(void);
int FakeTimeService_WakeUpRoutine(void);

#endif /*_FAKETIMESERVICE_H_*/
