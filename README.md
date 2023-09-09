# Quasigroup

##### Генерация квазигрупп
Генерировать квазигруппы можно с помощью фабрик. 
На данный момент реализованы следующие фабрики:
* *JMQuasigroupFactory* генерирует квазигруппы методом Джейкобсона-Мэтьюза
* *FNQuasigroupFactory* генерирует квазигруппы на основе обобщенных сетей Фейстеля
* *PFQuasigroupFactory* генерирует квазигруппы на основе правильных семейств
* *SRQuasigroupFactory* генерирует квазигруппы на основе обобщенных регистров сдвига с обратной связью
* *AffineQuasigroupFactory* генерирует только аффинные квазигруппы
```c++
int quasigroupOrder = 16;
Quasigroup::JMQuasigroupFactory factory; // здесь фабрика нужного вида
Quasigroup::Quasigroup *q = factory.createQuasigroup(quasigroupOrder);

// какие-то действия с квазигруппой q

delete q;
```

##### Проверка свойств квазигрупп

Для проверки известных свойств доступны следующие методы класса *Quasigroup*:
```c++
/* 
 * При передаче useLightTest = false будет использован оригинальный
 * алгоритм проверки аффинности. По умолчанию используется оптимизированный
 * вариант, использующий тест Лайта.
*/ 
 bool isAffine(bool useLightTest = true) const;
```
```c++
bool isSimple() const;
```
```c++
/*
 * Ищет подквазигруппу наименьшего размера с порядком не меньше чем border. 
 * Возвращает порядок найденной подквазигруппы.
 * Подквазигруппа сохраняется в a_sq.
 * 
 * Для проверки отсутствия подквазигрупп достаточно передать border = 1
 * и проверить, что метод вернул 0.
 */
int findSubquasigroup(int border, unsigned int **a_sq) const;
```

##### Эксперименты

Для проведения экспериментов можно использовать некоторые заранее 
готовые методы из *src/test*. Например, *generateLatinSquareQuasigroupSet* и *generateFunctionalQuasigroupSet*
позволяют получить сразу множество с необходимым количеством квазигрупп определенного порядка.
```c++
/*
 * Сгенерирует 100 квазигрупп порядка 4 алгоритмом Джейкобсона-Мэтьюза, среди которых уберет дубликаты.
 * Задав заранее достаточно большое значение quasigroupCount можно попробовать получить
 * все квазигруппы заданного порядка.
 */

Quasigroup::JMQuasigroupFactory factory;

int quasigroupOrder = 4;
int quasigroupCount = 100;

auto quasiSet = generateLatinSquareQuasigroupSet(factory, quasigroupOrder, quasigroupCount);

for (auto &q: quasiSet) {
    // желаемые действия с квазигруппой q

    delete q;
}
```
```c++
/*
 * Сгенерирует 100 квазигрупп порядка 4^2 на основе регистров сдвига с обратной связью, 
 * среди которых уберет дубликаты.
 * Задав заранее достаточно большое значение quasigroupCount можно попробовать получить
 * все квазигруппы заданного порядка.
 */

int k = 4;
int n = 2;
int quasigroupCount = 100;
Quasigroup::SRQuasigroupFactory factory;

auto quasiSet = generateFunctionalQuasigroupSet(factory, k, n, quasigroupCount);

for (auto &q: quasiSet) {
    // желаемые действия с квазигруппой q

    delete q;
}
```

Полученные множества также можно использовать для передачи в другие методы для экспериментов:
```c++
/*
 * Посчитать число простых квазигрупп, заданных латинскими квадратами в множестве qusigroups
 * Возвращает колличество, худшее время, среднее время, лучшее время
 */
tuple<int, double, double, double> simpleTestForLatinSquareQuasigroups(const std::unordered_set<LatinSquareQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>& quasigroups, bool printResult = false);

/*
 * Посчитать число аффинных квазигрупп, заданных латинскими квадратами в множестве qusigroups
 * Возвращает колличество, худшее время, среднее время, лучшее время
 */
tuple<int, double, double, double> affineTestForLatinSquareQuasigroups(const std::unordered_set<LatinSquareQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>& quasigroups, bool useLightTest = false, bool printResult = false);

/*
 * Посчитать число простых квазигрупп, заданных функционально в множестве qusigroups
 * Возвращает колличество, худшее время, среднее время, лучшее время
 */
tuple<int, double, double, double> simpleTestForFunctionalQuasigroups(const std::unordered_set<FunctionalQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>& quasigroups, bool printResult = false);

/*
 * Посчитать число аффинных квазигрупп, заданных функционально в множестве qusigroups.
 * Возвращает колличество, худшее время, среднее время, лучшее время
 */
tuple<int, double, double, double> affineTestForFunctionalQuasigroups(const std::unordered_set<FunctionalQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>& quasigroups, bool useLightTest = false, bool printResult = false);

/*
 * Считает колличество функциональных квазигрупп у которых есть подквазигруппы порядка не менее чем border
 */
int subquasigroupTestForFunctionalQuasigroups(const std::unordered_set<FunctionalQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>& quasigroups, int border, bool printResult = false);

/*
* Считает колличество квазигрупп, заданных латинскими квадратами, у которых есть подквазигруппы порядка не менее чем border
*/
int subquasigroupTestForLatinSquareQuasigroups(const std::unordered_set<LatinSquareQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>& quasigroups, int border, bool printResult = false);

/*
* Считает колличество квазигрупп, заданных латинскими квадратами, у которых есть подквазигруппы порядка 1
*/
int idempotentElementTestForFunctionalQuasigroups(const std::unordered_set<FunctionalQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>& quasigroups, bool printResult = false);

/*
* Считает колличество квазигрупп, заданных латинскими квадратами, у которых есть подквазигруппы порядка 1
*/
int idempotentElementTestForLatinSquareQuasigroups(const std::unordered_set<LatinSquareQuasigroup*, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>& quasigroups, bool printResult = false);
```

##### Примеры
```c++
/*
 * Генерация квазигруппы порядка 8 алгоритмом Джейкобсона-Мэтьюза. Проверка аффиности и простоты.
 * Поиск подквазигруппы порядка не меньше 3.
 */

int quasigroupOrder = 8;
Quasigroup::JMQuasigroupFactory factory;
Quasigroup::Quasigroup *q = factory.createQuasigroup(quasigroupOrder);

std::cout << "Quasigroup: " << std::endl;
std::cout << *q << std::endl;

std::cout << "Is affine: " << q->isAffine() << std::endl;
std::cout << "Is simple: " << q->isSimple() << std::endl;

unsigned int *sqg;
sqg = nullptr;

int sqgMinOrder = 3;
int sqgOrder = q->findSubquasigroup(sqgMinOrder, &sqg);

std::cout << "Subquasigroup order: " << sqgOrder << std::endl;

std::cout << "Subquasigroup: " << std::endl;
for (int i = 0; i < sqgOrder; i++) std::cout << sqg[i] << " ";

if (sqg != nullptr) {
    free(sqg);
}
delete q;

>>>>>>>>>>>>>>>>>>>>>>>>>> Output

Quasigroup: 
5 7 4 1 3 0 6 2 
7 5 6 0 4 2 1 3 
3 0 2 6 1 4 7 5 
2 6 1 3 5 7 4 0 
4 2 5 7 0 1 3 6 
0 3 7 4 2 6 5 1 
6 1 3 2 7 5 0 4 
1 4 0 5 6 3 2 7 

Is affine: 0
Is simple: 1
Subquasigroup order: 3
Subquasigroup: 
0 5 6 
```
```c++
/*
 * Пробуем сгенерировать все возможные квазигруппы на основе регистров сдвига с обратной связью при k = n = 2.
 * Если сгенерировать сразу 100 квазигрупп, возможно среди них удастся получить все 4 желаемые квазигруппы.
 */

int k = 2;
int n = 2;
int quasigroupCount = 100;
Quasigroup::SRQuasigroupFactory factory;

auto quasiSet = generateFunctionalQuasigroupSet(factory, k, n, quasigroupCount);

for (auto &q: quasiSet) {
    std::cout << *q << std::endl;
    delete q;
}

>>>>>>>>>>>>>>>>>>>>>>>>>> Output
0 2 3 1 
3 1 0 2 
1 3 2 0 
2 0 1 3 

3 1 0 2 
0 2 3 1 
2 0 1 3 
1 3 2 0 

1 3 2 0 
2 0 1 3 
0 2 3 1 
3 1 0 2 

2 0 1 3 
1 3 2 0 
3 1 0 2 
0 2 3 1 
```