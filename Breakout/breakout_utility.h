#pragma once
#include "Vector2d.h"

float ClosestPtSegSeg(const sgs::mt::Vector&          p1,
	const sgs::mt::Vector&          q1,
	const sgs::mt::Vector&          p2,
	const sgs::mt::Vector&          q2,
	sgs::mt::ClosestPtSegmentSegment_Result& result);

