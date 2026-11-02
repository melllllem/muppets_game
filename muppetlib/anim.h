#pragma once

#include "common.h"
#include "cmp.h"

void setanim(ActiveStateMachine *activeTile, uint8_t which);
void setAnimData(AnimData *anim, uint16_t ofset, uint8_t len, uint8_t frameLen);
AnimData *getAnimData(ActiveStateMachine *activeTile);
void handleanim(ActiveStateMachine *activeTile);
