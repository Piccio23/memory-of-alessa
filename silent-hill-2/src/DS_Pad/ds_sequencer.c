#include "sh2_common.h"
#include "ds_sequencer.h"

void Sequencer_Type_Hispeed(EntryRecord *pER)
{
    DS_Record *pDSR;
    Record_Info *pInfo;

    int Node;
    int Node_Next;
    u32 now_act_lv_i;

    float time;
    float section_0;
    float section_1;

    pInfo = &pER->Info;
    time = pER->Time_Count;
    Node = Node_Current_Search(pInfo, time);
    Node_Next = Node_Next_Search(pInfo, time);

    if ((Node != -1) && (Node_Next != -1))
    {
        pDSR = (DS_Record *)pInfo->pAddress + Node;
        now_act_lv_i = 0;
        if (pDSR->Complement_Enable != 0)
        {
            now_act_lv_i = pDSR->Actuater_LV ? 1 : 0;
        }
        else
        {
            section_0 = pDSR->Time;
            section_1 = section_0 + Sequence_Different_Time_Get();
            if ((section_0 <= time) && (time < section_1))
            {
                now_act_lv_i = pDSR->Actuater_LV ? 1 : 0;
            }
        }

        now_act_lv_i *= pER->Ratio > 0.0f ? 1 : 0;

        TotalActuaterLV_Keeper(
            pER->Controller_ID,
            0u,
            now_act_lv_i);
    }
}

static int Node_Next_Search(Record_Info* pInfo, float Time) {
    u_int node_num = pInfo->pObject->DataNode_num;
    DS_Record * pDSR = pInfo->pAddress;

    int result = -1;
    u_int i;
    for (i = 0; i < node_num; i++, pDSR++) {
        if (Time < pDSR->Time) {
            result = i;
            break;
        }
    }

    return result;
}

static int Node_Current_Search(Record_Info * pInfo /* r2 */, float Time /* r29+0x10 */) {
    signed int result = -1; // r7
    signed int num = Node_Next_Search(pInfo, Time); // r2

    if (num > 0) {
        result = num - 1;
    }

    return result;
}
