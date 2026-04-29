#ifndef DBFLOW_H
#define DBFLOW_H
#include "sh2_common.h"
#include "debug.h"

#define dbFlowSetCheckPoint(checkpoint) ___dbFlowSetCheckPoint("`" checkpoint "'(" __FILE__ ":" ASSTR(__LINE__) ")")
#define dbFlowSetCheckPointOnLine(checkpoint, line) ___dbFlowSetCheckPoint("`" checkpoint "'(" __FILE__ ":" ASSTR(line) ")")

#endif
