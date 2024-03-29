![](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)

# EcoOS-Lab-2

## Постановка задачи

Необходимо в **ранее созданный компонент** ([EcoLab1](https://github.com/Sparou/Eco.Lab1)) используя приемы программирования **включение**/**агрегирование** добавить компонент(-ы) калькулятора, выполняющий(-ие) операции **сложения**, **вычитания**, **деления** и **умножения**.

## Включение 

Для поддержки сторонних компонентов в структуру **CEcoLab1** и **CEcoLab2** были добавлены указатели на новые интерфейсы и их виртуальные таблицы:

```C
/* Таблица функций интерфейса IEcoLab1 */
IEcoLab1VTbl* m_pVTblIEcoLab1;

/* Таблица функций интерфейса IEcoCalculatorX */
IEcoCalculatorXVTbl* m_pVTblIEcoCalculatorX;

/* Таблица функций интерфейса IEcoCalculatorY */
IEcoCalculatorYVTbl* m_pVTblIEcoCalculatorY;

/* Указатель на интерфейс IEcoCalculatorX включаемого компонента */
IEcoCalculatorX* m_pIEcoCalculatorX;

/* Указатель на интерфейс IEcoCalculatorY включаемого компонента */
IEcoCalculatorY* m_pIEcoCalculatorY;
```
Пример метода включения и взаимозаменяемости компонентов (A, B, D, E):

```C
result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorA, 0, &IID_IEcoCalculatorX, (void**) &pCMe->m_pIEcoCalculatorX);
if (result != 0 || pCMe->m_pIEcoCalculatorX == 0) {
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorB, 0, &IID_IEcoCalculatorX, (void**) &pCMe->m_pIEcoCalculatorX);
    }

result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorD, 0, &IID_IEcoCalculatorY, (void**) &pCMe->m_pIEcoCalculatorY);
if (result != 0 || pCMe->m_pIEcoCalculatorX == 0) {
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorE, 0, &IID_IEcoCalculatorY, (void**) &pCMe->m_pIEcoCalculatorY);
    }
```

Теперь, если компоненты **A/B** и **D/E** с интерфейсов **IEcoCalculatorX** и **IEcoCalculatorY** доступны, мы можем имплементировать методы интерфейса внутри нашего компонента и определить их в виртуальную таблицу, которая будет присвоена соответствующей переменной во время исполнения create функции. 

Для передачи интерфейса пользователю добавим **else if** в метод **QueryInterface**:

```C
  /* Проверка и получение запрошенного интерфейса */
    if (IsEqualUGUID(riid, &IID_IEcoLab1) ) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorX)) {
        if (pCMe->m_pIUnkOuter != 0) {
            return pCMe->m_pIUnkOuter->pVTbl->QueryInterface(pCMe->m_pIUnkOuter, riid, ppv);
    }
    else {
        *ppv = &pCMe->m_pVTblIEcoCalculatorX;
    }
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*) pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorY)) {
        *ppv = &pCMe->m_pVTblIEcoCalculatorY;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*) pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }
```
