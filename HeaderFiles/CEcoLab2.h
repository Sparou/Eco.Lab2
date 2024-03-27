#ifndef __C_ECOLAB2_H__
#define __C_ECOLAB2_H__

#include "IEcoLab2.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IEcoCalculatorX.h"
#include "IEcoCalculatorY.h"

typedef struct CEcoLab2 {

    /* Таблица функций интерфейса IEcoLab1 */
    IEcoLab2VTbl* m_pVTblIEcoLab2;

    /* Таблица функций интерфейса IEcoCalculatorX */
    IEcoCalculatorXVTbl* m_pVTblIEcoCalculatorX;

    /* Таблица функций интерфейса IEcoCalculatorY */
    IEcoCalculatorYVTbl* m_pVTblIEcoCalculatorY;

    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

    /* Системный интерфейс */
    IEcoSystem1* m_pISys;

/* Указатель на интерфейс IEcoCalculatorX включаемого компонента */
    IEcoCalculatorX* m_pIEcoCalculatorX;

    /* Указатель на интерфейс IEcoCalculatorY включаемого компонента */
    IEcoCalculatorY* m_pIEcoCalculatorY;

    /* Неделегирующий интерфейс IEcoUnknown */
    IEcoUnknownVTbl* m_pVTblINondelegatingUnk;

    /* Указатель на IEcoUnknown внутреннего компонента */
    IEcoUnknown* m_pInnerUnknown;

    /* Данные экземпляра */
    char_t* m_Name;

} CEcoLab2, *CEcoLab2Ptr;

/* Инициализация экземпляра */
int16_t ECOCALLMETHOD initCEcoLab2(/*in*/ struct IEcoLab2* me, /* in */ IEcoUnknown *pIUnkSystem);
/* Создание экземпляра */
int16_t ECOCALLMETHOD createCEcoLab2(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoLab2** ppIEcoLab2);
/* Удаление */
void ECOCALLMETHOD deleteCEcoLab2(/* in */ IEcoLab2* pIEcoLab2);

#endif /* __C_ECOLAB2_H__ */
