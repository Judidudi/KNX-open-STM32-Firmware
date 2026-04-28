#ifndef SWITCH_ACTUATOR_H
#define SWITCH_ACTUATOR_H

/* Example application: single-channel switch actuator.
   ComObject 0 (co_switch_ch1, DPT 1.001) controls the relay. */

void APP_SwitchActuator_Init(void);
void APP_SwitchActuator_Process(void);

#endif /* SWITCH_ACTUATOR_H */
