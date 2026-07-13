#ifndef M3_EDDIE_H
#define M3_EDDIE_H

#include "sh2_common.h"
#include "Chacter/character.h"

#define EDDIE_DRAMA_ANIME_ID_START 4500
#define EDDIE_PLAY_ANIME_ID_START  4800

#define EDDIE_PLAY_ANIM_4801       4801
#define EDDIE_PLAY_ANIM_4802       4802
#define EDDIE_PLAY_ANIM_4803       4803

void shCharacterSetHumanEDILow(SubCharacter* scp);
int shCharacterHumanEDIAnimeSet(SubCharacter* scp, int anime_id);
int shCharacterHumanEDIAnimeSetP(SubCharacter* scp, int anime_id);

#endif // M3_EDDIE_H
