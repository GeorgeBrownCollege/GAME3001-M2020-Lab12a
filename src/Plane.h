#pragma once
#ifndef __PLANE__
#define __PLANE__

#include "Sprite.h"
#include "StateMachine.h"

class Plane final : public Sprite
{
public:
	Plane();
	~Plane();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void setAngle(float angle);

private:
	void m_buildAnimations();

	float m_angle;

	StateMachine m_stateMachine;

	void m_checkCurrentConditions();

	bool m_playerDetected;
	bool m_haveLOS;
	bool m_withinMeleeRange;
	int m_health;
};

#endif /* defined (__PLANE__) */
