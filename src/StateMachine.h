#pragma once
#ifndef __STATE_MACHINE__
#define __STATE_MACHINE__

#include "BehaviourState.h"
#include "DisplayObject.h"


class StateMachine
{
public:
	StateMachine();
	~StateMachine();

	void Update(DisplayObject* object);

	// Getters
	BehaviourState GetOuterState();
	BehaviourState GetInnerState();

	// Setters
	void SetOuterState(BehaviourState new_state);
	void SetInnerState(BehaviourState new_state);

private:
	BehaviourState m_currentOuterState;
	BehaviourState m_currentInnerState;

	// Actions
	void m_moveToLOS(DisplayObject* object);
	void m_meleeAttack(DisplayObject* object);
	void m_flee(DisplayObject* object);
};


#endif /* defined (__STATE_MACHINE__) */
