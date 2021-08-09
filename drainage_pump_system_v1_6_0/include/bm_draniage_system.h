#ifndef BM_DRAINAGE_H
#define BM_DRAINAGE_H

#define NUMBER_OF_VALVES 8

extern int16_t drain_intervall_h;
extern int16_t valve_drain_time_s[NUMBER_OF_VALVES];

void bm_drainage_stateMachine();



#endif