#ifndef SH2GFW_VIEWCLIP_H
#define SH2GFW_VIEWCLIP_H

int sh2gfw_viewclip_block(union Q_WORDDATA** qwd_tag);

void sh2gfw_set_objclip_matrix(void);

int sh2gfw_Set_DispOnOffObj(int mapid, int dispflg);

void sh2gfw_Init_DispOnOffObj(void);

int sh2gfw_FastSet_DispOnOffObj(int mapid, int dispflg);

int sh2gfw_Get_ChrClip_FLG(void);

void sh2gfw_Check_ChrClip_FLG(int mp);

int sh2gfw_Check_ClipOKChar(void* sp);


#endif // SH2GFW_VIEWCLIP_H
