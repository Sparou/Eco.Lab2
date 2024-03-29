![](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)

# EcoOS-Lab-2

## Постановка задачи

Необходимо в **ранее созданный компонент** ([EcoLab1](https://github.com/Sparou/Eco.Lab1)) используя приемы программирования **включение**/**агрегирование** добавить компонент(-ы) калькулятора, выполняющий(-ие) операции **сложения**, **вычитания**, **деления** и **умножения**.

## Процесс выполнения

- [X] Включение
- [X] Агрегирование

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
## Агрегирование

Для реализации метода агрегирования было создано решение **CEcoLab2**, которое агрегирует **CEcoLab1**.  Для этого в **CEcoLab1** был добавлен указатель **m_pIUnkOuter** на агрегирующий компонент:

```C
/* Делегирующий IEcoUnknown, указывает на внешний или неделегирующий IEcoUnknown */
IEcoUnknown* m_pIUnkOuter;
```
Далее, в функции **CEcoLab1_QueryInterface** управление передается агрегирующему компоненту:

```C
if (pCMe->m_pIUnkOuter != 0) {
      return pCMe->m_pIUnkOuter->pVTbl->QueryInterface(pCMe->m_pIUnkOuter, riid, ppv);
    }
```
В свою очередь, в **CEcoLab2** добавлен указатель на **IEcoUnknown** внутреннего компонента:

```C
/* Указатель на IEcoUnknown внутреннего компонента */
IEcoUnknown* m_pInnerUnknown;
```
Он получается во время инициализации **CEcoLab2** в функции **initCEcoLab2**:

```C
/* Получение интерфейса внутреннего компонента "Eco.Lab1" c поддержкой агрегирования */
result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, pOuterUnknown,  &IID_IEcoUnknown,(void**) &pCMe->m_pInnerUnknown);
```
В **EcoLab2.UnitTes**t мы получаем указатель на интерфейс **IEcoLab1**, благодаря чему можем использовать реализуемый в нем метод **qsort**:
```C
/* Агрегирование */
result = pIEcoLab2->pVTbl->QueryInterface(pIEcoLab2, &IID_IEcoLab1, (void**)&pIEcoLab1);
```

