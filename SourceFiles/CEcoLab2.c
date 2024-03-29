#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoLab2.h"
#include "IdEcoCalculatorA.h"
#include "IdEcoCalculatorB.h"
#include "IdEcoCalculatorD.h"
#include "IdEcoCalculatorE.h"
#include "IdEcoLab1.h"
#include "IEcoLab1.h"

int16_t ECOCALLMETHOD CEcoLab2_Subtraction(/* in */ struct IEcoCalculatorX* me, /* in */ int16_t a, /* in */ int16_t b);

// Функция QueryInterface для интерфейса IEcoLab1
int16_t ECOCALLMETHOD CEcoLab2_QueryInterface(/* in */ struct IEcoLab2* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab2* pCMe = (CEcoLab2*)me;
    int16_t result = 0;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Включение */
    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoLab2) ) {
        *ppv = &pCMe->m_pVTblIEcoLab2;
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoLab1)) {
        if (pCMe->m_pInnerUnknown != 0){
            return pCMe->m_pInnerUnknown->pVTbl->QueryInterface(pCMe->m_pInnerUnknown, riid, ppv);
    }
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*) pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorX)) {
        *ppv = &pCMe->m_pVTblIEcoCalculatorX;
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*) pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorY)) {
        *ppv = &pCMe->m_pVTblIEcoCalculatorY;
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*) pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoLab2;
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }

    return result;
}

void ECOCALLMETHOD deleteCEcoLab2_IEcoCalculatorX(/* in */  IEcoCalculatorX* pIX) {
    CEcoLab2* pCMe = (CEcoLab2*)pIX;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIX != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        if ( pCMe->m_pIEcoCalculatorX != 0 ) {
            pCMe->m_pIEcoCalculatorX->pVTbl->Release(pCMe->m_pIEcoCalculatorX);
        }
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}

// Функция AddRef для интерфейса IEcoLab2
uint32_t ECOCALLMETHOD CEcoLab2_AddRef(/* in */ struct IEcoLab2* me) {
    CEcoLab2* pCMe = (CEcoLab2*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

// Функция Release для интерфейса IEcoLab2
uint32_t ECOCALLMETHOD CEcoLab2_Release(/* in */ struct IEcoLab2* me) {
    CEcoLab2* pCMe = (CEcoLab2*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoLab2((IEcoLab2*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

// Функция Init для интерфейса IEcoLab2
int16_t ECOCALLMETHOD initCEcoLab2(/*in*/ struct IEcoLab2* me, /* in */ struct IEcoUnknown *pIUnkSystem) {
    CEcoLab2* pCMe = (CEcoLab2*)me;
    IEcoInterfaceBus1* pIBus = 0;
    int16_t result = -1;

    /* Агрегирование */
    IEcoUnknown* pOuterUnknown = (IEcoUnknown*)me;

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorA, 0, &IID_IEcoCalculatorX, (void**) &pCMe->m_pIEcoCalculatorX);
    if (result != 0 || pCMe->m_pIEcoCalculatorX == 0) {
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorB, 0, &IID_IEcoCalculatorX, (void**) &pCMe->m_pIEcoCalculatorX);
    }

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorD, 0, &IID_IEcoCalculatorY, (void**) &pCMe->m_pIEcoCalculatorY);
    if (result != 0 || pCMe->m_pIEcoCalculatorX == 0) {
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorE, 0, &IID_IEcoCalculatorY, (void**) &pCMe->m_pIEcoCalculatorY);
    }

    /* Получение интерфейса внутреннего компонента "Eco.Lab1" c поддержкой агрегирования */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, pOuterUnknown, &IID_IEcoUnknown,(void**) &pCMe->m_pInnerUnknown);

    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);
    
    return result;
}

int16_t ECOCALLMETHOD CEcoLab2_QueryInterface_IEcoCalculatorX(/* in */ struct IEcoCalculatorX* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct IEcoLab2*));
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return result;
    }

    if ( IsEqualUGUID(riid, &IID_IEcoLab2) ) {
        *ppv = &pCMe->m_pVTblIEcoLab2;
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoLab1)) {
        if (pCMe->m_pInnerUnknown != 0){
            return pCMe->m_pInnerUnknown->pVTbl->QueryInterface(pCMe->m_pInnerUnknown, riid, ppv);
    }
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*) pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorX)) {
        *ppv = &pCMe->m_pVTblIEcoCalculatorX;
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*) pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorY)) {
        *ppv = &pCMe->m_pVTblIEcoCalculatorY;
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*) pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoLab2;
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }

    return 0;
}


uint32_t ECOCALLMETHOD CEcoLab2_AddRef_IEcoCalculatorX(/* in */ struct IEcoCalculatorX* me) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct IEcoLab2*));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

uint32_t ECOCALLMETHOD CEcoLab2_Release_IEcoCalculatorX(/* in */ struct IEcoCalculatorX* me) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct IEcoLab2*));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoLab2_IEcoCalculatorX((IEcoCalculatorX*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}


int32_t ECOCALLMETHOD CEcoLab2_Addition(/* in */ struct IEcoCalculatorX* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct IEcoLab2*));
    int32_t result = 0;

    /* Проверка указателей */
    if (me == 0 ) {
        return -1;
    }

    /* Проверка указателя включаемого компонента и вызов метода */
    if (pCMe->m_pIEcoCalculatorX != 0) {
        result = pCMe->m_pIEcoCalculatorX->pVTbl->Addition(pCMe->m_pIEcoCalculatorX, a, b);
    }

    return result;
}

int16_t ECOCALLMETHOD CEcoLab2_Subtraction(/* in */ struct IEcoCalculatorX* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct IEcoLab2*));
    int16_t result = 0;

    if (me == 0 ) return -1; /* Проверка указателей */

    /* Проверка указателя включаемого компонента и вызов метода */
    if (pCMe->m_pIEcoCalculatorX != 0) {
        result = pCMe->m_pIEcoCalculatorX->pVTbl->Subtraction(pCMe->m_pIEcoCalculatorX, a, b);
    }

    return result;
}

int16_t ECOCALLMETHOD CEcoLab2_IEcoCalculatorY_QueryInterface(/* in */ struct IEcoCalculatorY* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct IEcoCalculatorX) - sizeof(struct IEcoLab2*));
    int16_t result = -1;

    if (me == 0 || ppv == 0) return result; /* Проверка указателей */

    if ( IsEqualUGUID(riid, &IID_IEcoLab2) ) {
        *ppv = &pCMe->m_pVTblIEcoLab2;
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoLab1)) {
        if (pCMe->m_pInnerUnknown != 0){
            return pCMe->m_pInnerUnknown->pVTbl->QueryInterface(pCMe->m_pInnerUnknown, riid, ppv);
    }
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*) pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorX)) {
        *ppv = &pCMe->m_pVTblIEcoCalculatorX;
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*) pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorY)) {
        *ppv = &pCMe->m_pVTblIEcoCalculatorY;
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*) pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoLab2;
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }

    return 0;
}

uint32_t ECOCALLMETHOD CEcoLab2_IEcoCalculatorY_AddRef(/* in */ struct IEcoCalculatorY* me) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me -sizeof(struct IEcoCalculatorX) - sizeof(struct IEcoLab2*));

    if (me == 0 ) return -1; /* Проверка указателя */

    return ++pCMe->m_cRef;
}

uint32_t ECOCALLMETHOD CEcoLab2_IEcoCalculatorY_Release(/* in */ struct IEcoCalculatorY* me) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me -sizeof(struct IEcoCalculatorX) - sizeof(struct IEcoLab2*));

    if (me == 0 ) return -1; /* Проверка указателя */
    --pCMe->m_cRef; /* Уменьшение счетчика ссылок на компонент */

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoLab2_IEcoCalculatorX((IEcoCalculatorX*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

int32_t ECOCALLMETHOD CEcoLab2_Multiplication(/* in */ struct IEcoCalculatorY* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me -sizeof(struct IEcoCalculatorX) - sizeof(struct IEcoLab2*));
    int32_t result = 0;

    /* Проверка указателей */
    if (me == 0 ) {
        return -1;
    }

    if (pCMe->m_pIEcoCalculatorY != 0) {
        result = pCMe->m_pIEcoCalculatorY->pVTbl->Multiplication(pCMe->m_pIEcoCalculatorY, a, b);
    }

    return result;
}

int16_t ECOCALLMETHOD CEcoLab2_Division(/* in */ struct IEcoCalculatorY* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct IEcoCalculatorX) - sizeof(struct IEcoLab2*));
    int16_t result = 0;

    if (me == 0 ) return -1; /* Проверка указателей */

    /* Проверка указателя включаемого компонента и вызов метода */
    if (pCMe->m_pIEcoCalculatorY != 0) {
        result = pCMe->m_pIEcoCalculatorY->pVTbl->Division(pCMe->m_pIEcoCalculatorY, a, b);
    }

    return result;
}

/* Create Virtual Table */
IEcoCalculatorXVTbl g_x9322111622484742AE0682819447843DVTblD = {
    CEcoLab2_QueryInterface_IEcoCalculatorX,
    CEcoLab2_AddRef_IEcoCalculatorX,
    CEcoLab2_Release_IEcoCalculatorX,
    CEcoLab2_Addition,
    CEcoLab2_Subtraction
};

IEcoCalculatorYVTbl g_xBD6414C29096423EA90C04D77AFD1CADVTblD = {
    CEcoLab2_IEcoCalculatorY_QueryInterface,
    CEcoLab2_IEcoCalculatorY_AddRef,
    CEcoLab2_IEcoCalculatorY_Release,
    CEcoLab2_Multiplication,
    CEcoLab2_Division
};

/* Create Virtual Table IEcoLab1 */
IEcoLab2VTbl g_x377FC00C35624096AFCFC125B94EEC90VTbl = {
    CEcoLab2_QueryInterface,
    CEcoLab2_AddRef,
    CEcoLab2_Release
};


// Функция Create для интерфейса IEcoLab1
int16_t ECOCALLMETHOD createCEcoLab2(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoLab2** ppIEcoLab2) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoLab2* pCMe = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;
    
    if (ppIEcoLab2 == 0 || pIUnkSystem == 0) return result; /* Проверка указателей */

    /* Получение системного интерфейса приложения */
    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem1, (void **)&pISys);

    if (result != 0 && pISys == 0) return result; /* Проверка */

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    /* Получение идентификатора компонента для работы с памятью */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Получение интерфейса распределителя памяти */
    pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 && pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        pISys->pVTbl->Release(pISys);
        return result;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoLab2*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab2));

    pCMe->m_pISys = pISys;  /* Сохранение указателя на системный интерфейс */
    pCMe->m_pIMem = pIMem;  /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_cRef = 1;       /* Установка счетчика ссылок на компонент */

    /* Создание таблиц функций интерфейсов */
    pCMe->m_pVTblIEcoLab2 = &g_x377FC00C35624096AFCFC125B94EEC90VTbl;
    pCMe->m_pVTblIEcoCalculatorX = &g_x9322111622484742AE0682819447843DVTblD;
    pCMe->m_pVTblIEcoCalculatorY = &g_xBD6414C29096423EA90C04D77AFD1CADVTblD;

    pCMe->m_Name = 0;   /* Инициализация данных */
    *ppIEcoLab2 = (IEcoLab2*)pCMe; /* Возврат указателя на интерфейс */
    pIBus->pVTbl->Release(pIBus); /* Освобождение */

    return 0;
}



// Функция Delete для интерфейса IEcoLab1
void ECOCALLMETHOD deleteCEcoLab2(/* in */ IEcoLab2* pIEcoLab2) {
    CEcoLab2* pCMe = (CEcoLab2*)pIEcoLab2;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoLab2 != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        if ( pCMe->m_Name != 0 ) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}

