#ifndef __C_ECOLAB2_FACTORY_H__
#define __C_ECOLAB2_FACTORY_H__

#include "IEcoSystem1.h"

typedef struct CEcoLab2Factory {

    /* Таблица функций интерфейса IEcoComponentFactory */
    IEcoComponentFactoryVTbl* m_pVTblICF;

    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Данные компонентов для фабрики */
    CreateInstance m_pInstance;
    InitInstance m_pInitInstance;
    char_t m_Name[64];
    char_t m_Version[16];
    char_t m_Manufacturer[64];

} CEcoLab2Factory;

#endif /* __C_ECOLAB2_FACTORY_H__ */
