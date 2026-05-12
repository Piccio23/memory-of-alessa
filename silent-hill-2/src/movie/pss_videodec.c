#include "pss_videodec.h"

INCLUDE_ASM("asm/nonmatchings/movie/pss_videodec", videoDecCreate);

INCLUDE_ASM("asm/nonmatchings/movie/pss_videodec", videoDecSetStream);

INCLUDE_ASM("asm/nonmatchings/movie/pss_videodec", videoDecBeginPut);

INCLUDE_ASM("asm/nonmatchings/movie/pss_videodec", videoDecEndPut);

INCLUDE_ASM("asm/nonmatchings/movie/pss_videodec", videoDecDelete);

INCLUDE_ASM("asm/nonmatchings/movie/pss_videodec", videoDecAbort);

INCLUDE_ASM("asm/nonmatchings/movie/pss_videodec", videoDecGetState);

INCLUDE_ASM("asm/nonmatchings/movie/pss_videodec", videoDecSetState);

INCLUDE_ASM("asm/nonmatchings/movie/pss_videodec", videoDecPutTs);

int videoDecFlush(VideoDec *vd) {
    u_char *pd0;
    u_char *pd1;
    u_char seq_end_code[4] = {0x00, 0x00, 0x01, 0xb7};
    int d0;
    int d1;
    u_char *pd0_unc;
    u_char *pd1_unc;
    int size;

    videoDecBeginPut(vd, &pd0, &d0, &pd1, &d1);

    if (d0 + d1 < 4) {
        return 0;
    }

    pd0_unc = (u_char*)UncAddr(pd0);
    pd1_unc = (u_char*)UncAddr(pd1);

    size = cpy2area(pd0_unc, d0, pd1_unc, d1, seq_end_code, 4, NULL, 0);

    videoDecEndPut(&videoDec, size);

    viBufFlush(&vd->vibuf);

    if (vd->state == VD_STATE_NORMAL) {
        vd->state = VD_STATE_FLUSH;
    }

    return 1;
}

INCLUDE_ASM("asm/nonmatchings/movie/pss_videodec", videoDecMain);

int decBs0(VideoDec *vd) {
    VoData *voData;
    sceIpuRAW8 *raw8;
    int ret;
    int status = 1;
    sceMpeg *mp = &sys_mpeg;
    int picture_structure;
    extern int csct;

    while (sceMpegIsEnd(&sys_mpeg) == 0) {
        if (videoDecGetState(vd) == VD_STATE_ABORT) {
            status = -1;
            debugPrintf("decode thread: aborted\n");
            break;
        }

        while ((voData = voBufGetData(&voBuf)) == 0) {
            switchThread();
        }
        raw8 = (sceIpuRAW8*) voData->v;

        if (viBufAddDMA(&vd->vibuf) != 1) {
            debugPrintf("viBufAddDMA() failed\n");
            status = -1;
            break;
        }

        WaitSemaPss();
        ret = sceMpegGetPictureRAW8(mp, raw8, MAX_WIDTH/16 * MAX_HEIGHT/16);
        SignalSemaPss();

        if (ret < 0) {
            debugPrintf("sceMpegGetPictureRAW8() failed\n");
            status = -1;
            break;
        }

        picture_structure = (int)((mp->flags >> 3) & 3);
        if (picture_structure == SCE_MPEG_FRAME) {
            csct = (mp->flags & 0x180) ? CSCVU1_PROG_FRAME : CSCVU1_INTER_FRAME;
        } else {
            debugPrintf("pss_videodec.c:342> assert:(%s)\n", "@576_0x0039C028");
            do {} while (1);
        }

        if (ret < 0) {
            ErrMessage("sceMpegGetPicture() decode error");
        }

        if (mp->frameCount == 0) {
            int i;

            for (i = 0; i < N_VOBUF; i++) {
                cscVu1SetTag(
                    voBuf.tagInter[i].v,
                    0,
                    voBuf.data[i].v,
                    mp->width,
                    mp->height
                );
            }
        }

        voBufIncCount(&voBuf);
        switchThread();
    }

    sceMpegReset(mp);
    return status;
}

INCLUDE_ASM("asm/nonmatchings/movie/pss_videodec", mpegError);

INCLUDE_ASM("asm/nonmatchings/movie/pss_videodec", mpegNodata);

INCLUDE_ASM("asm/nonmatchings/movie/pss_videodec", mpegStopDMA);

INCLUDE_ASM("asm/nonmatchings/movie/pss_videodec", mpegRestartDMA);

INCLUDE_ASM("asm/nonmatchings/movie/pss_videodec", mpegTS);

INCLUDE_ASM("asm/nonmatchings/movie/pss_videodec", cpy2area);
