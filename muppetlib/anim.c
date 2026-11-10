#include "anim.h"

void setanim(ActiveStateMachine *activeTile, uint8_t which) {
	//do not reset anim if it is already playing
	if (activeTile->data.muppet.animSet.whichanim == which) return;

	activeTile->data.muppet.animSet.whichanim = which;
	activeTile->data.muppet.animSet.animProgress = 0;
}

void setAnimData(AnimData *anim, uint16_t ofset, uint8_t len, uint8_t frameLen) {
	anim->animOfset = ofset;
	anim->animLen = len;
	anim->frameLen = frameLen;
}

AnimData *getAnimData(ActiveStateMachine *activeTile) {

	if (activeTile->type == STATE_MACHINE_MUPPET)
	switch (activeTile->data.muppet.animSet.whichanim) {
	case ANIM_IDLE:	return &activeTile->data.muppet.animSet.idleAnim;
	case ANIM_WALK: return &activeTile->data.muppet.animSet.walkAnim;
	case ANIM_ATTACK: return &activeTile->data.muppet.animSet.attackAnim;
	case ANIM_DEAD: return &activeTile->data.muppet.animSet.deadAnim;
	default: return NULL;
	}
	
	return NULL;
}

void handleanim(ActiveStateMachine *activeTile) {
	switch (activeTile->type) {
	case STATE_MACHINE_MUPPET:
		if (activeTile->dead) {
			setanim(activeTile, ANIM_DEAD);
			return;
		}

		if (activeTile->type == STATE_MACHINE_MUPPET)
		if (!coordCmp(activeTile->coord, activeTile->data.muppet.target)) {
			setanim(activeTile, ANIM_WALK);
		} else {
			setanim(activeTile, ANIM_IDLE);
		}
		break;
	
		case STATE_MACHINE_MOSSPLANT:
			break;
	}
}
