#ifndef __I_ECOLAB2_H__
#define __I_ECOLAB2_H__

#include "IEcoBase1.h"

/* IEcoLa2 IID = {377FC00C-3562-4096-AFCF-C125B94EEC90} */
#ifndef __IID_IEcoLab2
static const UGUID IID_IEcoLab2 = {0x01, 0x10, 0x37, 0x7F, 0xC0, 0x0C, 0x35, 0x62, 0x40, 0x96, 0xAF, 0xCF, 0xC1, 0x25, 0xB9, 0x4E, 0xEC, 0x90};
#endif /* __IID_IEcoLab2 */

typedef struct IEcoLab2VTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ struct IEcoLab2* me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ struct IEcoLab2* me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ struct IEcoLab2* me);

    /* IEcoLab2 */
    //int16_t (ECOCALLMETHOD *qsort)(struct IEcoLab2* me, char* start_ptr, size_t arr_size, size_t elem_size, int (__cdecl *comp)(const void *, const void*));

} IEcoLab2VTbl, *IEcoLab2VTblPtr;

interface IEcoLab2 {
    struct IEcoLab2VTbl *pVTbl;
} IEcoLab2;


#endif /* __I_ECOLAB2_H__ */
