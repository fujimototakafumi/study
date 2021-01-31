#include "breakout_utility.h"

//2つの線分の最近接点を出力
float ClosestPtSegSeg(const sgs::mt::Vector&          p1,
	const sgs::mt::Vector&          q1,
	const sgs::mt::Vector&          p2,
	const sgs::mt::Vector&          q2,
	sgs::mt::ClosestPtSegmentSegment_Result& result)
{
	sgs::mt::ClosestPtSegmentSegment(p1, q1, p2, q2, result);
	sgs::mt::Vector vec = result.c1 - result.c2;
	return 	vec.Dot(vec);
}
