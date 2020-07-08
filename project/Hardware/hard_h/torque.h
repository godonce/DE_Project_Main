#ifndef __torque_H_
#define __torque_H_
#include "stdint.h"
#include "dataCRC.h"

#define RISE_TIMER_05   26*2
#define RISE_TIMER_07   28*2
#define RISE_TIMER_10   32*2
#define RISE_TIMER_14   38*2
#define RISE_TIMER_20   44*2
#define RISE_TIMER_28   51*2
#define RISE_TIMER_40   63*2

#define FALL_TIMER_05   10*2
#define FALL_TIMER_07   12*2
#define FALL_TIMER_10   13*2
#define FALL_TIMER_14   18*2
#define FALL_TIMER_20   23*2
#define FALL_TIMER_28   30*2
#define FALL_TIMER_40   40*2

#define START_SPEED_05   0x0000
#define START_SPEED_07   0x0000
#define START_SPEED_10   0x0000
#define START_SPEED_14   0x0000
#define START_SPEED_20   0x0000
#define START_SPEED_28   0x0000
#define START_SPEED_40   0x0000

#define RUN_SPEED_05   0x03E8
#define RUN_SPEED_07   0x0514
#define RUN_SPEED_10   0x0640
#define RUN_SPEED_14   0x0898
#define RUN_SPEED_20   0x0BB8
#define RUN_SPEED_28   0x0FA0
#define RUN_SPEED_40   0x14E0

#define END_SPEED_05   0x0000
#define END_SPEED_07   0x0000
#define END_SPEED_10   0x0000
#define END_SPEED_14   0x0000
#define END_SPEED_20   0x0000
#define END_SPEED_28   0x0000
#define END_SPEED_40   0x0000

#define STOP_SPEED_05   0x0000
#define STOP_SPEED_07   0x0000
#define STOP_SPEED_10   0x0000
#define STOP_SPEED_14   0x0000
#define STOP_SPEED_20   0x0000
#define STOP_SPEED_28   0x0000
#define STOP_SPEED_40   0x0000



#define START_TORQUE_18   0x0000
#define START_TORQUE_24   0x0000
#define START_TORQUE_30   0x0000
#define START_TORQUE_36   0x0000
#define START_TORQUE_42   0x0000
#define START_TORQUE_48   0x0000
#define START_TORQUE_54   0x0000
#define START_TORQUE_60   0x0000

#define RUN_TORQUE_18   0x2880
#define RUN_TORQUE_24   0x2E00
#define RUN_TORQUE_30   0x3340
#define RUN_TORQUE_36   0x3800
#define RUN_TORQUE_42   0x3C40
#define RUN_TORQUE_48   0x4000
#define RUN_TORQUE_54   0x4480
#define RUN_TORQUE_60   0x4840

#define END_TORQUE_18   0x0000
#define END_TORQUE_24   0x0000
#define END_TORQUE_30   0x0000
#define END_TORQUE_36   0x0000
#define END_TORQUE_42   0x0000
#define END_TORQUE_48   0x0000
#define END_TORQUE_54   0x0000
#define END_TORQUE_60   0x0000

#define STOP_TORQUE_18   0x001C
#define STOP_TORQUE_24   0x001C
#define STOP_TORQUE_30   0x4020
#define STOP_TORQUE_36   0x8024
#define STOP_TORQUE_42   0x0027
#define STOP_TORQUE_48   0x002B
#define STOP_TORQUE_54   0xC02D
#define STOP_TORQUE_60   0x0032




void pchange();
void check_hand();
void choice_speed_line();
int changeDIR(void);
void changetorque(uint8_t dir);
short  RC(uint16_t current);

void choice_speed_line13DE();
void choice_speed_line13EE();
void choice_speed_line11CE();
void choice_speed_line11DE();
void choice_speed_line11EE();
#endif

