/*
 * button_status.h
 *
 *  Created on: 29 nov 2022
 *      Author: isaac
 */

#ifndef BUTTON_STATUS_H_
#define BUTTON_STATUS_H_

#include "bits.h"

#define LOGIC_ONE 1

#define ZERO 0

void Buttons_Validation(void);

boolean_t Ask_Red_Button_Status(void);

void Set_True_Play_Flag_Shoot(void);

void Set_False_Play_Flag_Shoot(void);

#endif /* BUTTON_STATUS_H_ */
