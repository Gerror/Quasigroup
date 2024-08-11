# Quasigroup

##### Генерация квазигрупп
Генерировать квазигруппы можно с помощью класса-генератора *QuasigroupGenerator*, передав
ему необходимую фабрику квазигрупп в конструктор. 
На данный момент реализованы следующие фабрики:
* *JMQuasigroupFactory* генерирует квазигруппы методом Джейкобсона-Мэтьюза
* *FNQuasigroupFactory* генерирует квазигруппы на основе обобщенных сетей Фейстеля
* *PFQuasigroupFactory* генерирует квазигруппы на основе правильных семейств
* *SRQuasigroupFactory* генерирует квазигруппы на основе обобщенных регистров сдвига с обратной связью
* *AffineQuasigroupFactory* генерирует только аффинные квазигруппы
```c++
// Порождение одной квазигруппы порядка 16 методом Джейкобсона-Мэтьюза

Quasigroup::JMQuasigroupFactory factory(16);
Quasigroup::QuasigroupGenerator generator(&factory);

auto q = generator.generate();

// какие-то действия с квазигруппой q

delete q;
```
```c++
// Порождение набора из 1000 квазигрупп порядка 16 методом Джейкобсона-Мэтьюза 
// (возможно повторяющихся)

Quasigroup::JMQuasigroupFactory factory(16);
Quasigroup::QuasigroupGenerator generator(&factory);

auto qVector = generator.generateVector(1000);

for (auto q : qVector) {
    // какие-то действия с квазигруппой q
    delete q;
}
```
```c++
// Порождение набора из 1000 уникальных квазигрупп порядка 16 методом Джейкобсона-Мэтьюза

Quasigroup::JMQuasigroupFactory factory(16);
Quasigroup::QuasigroupGenerator generator(&factory);

auto qSet = generator.generateSet(1000);

for (auto q : qSet) {
    // какие-то действия с квазигруппой q
    delete q;
}
```

В методы *generate* и *generateSet* дополнительно можно передать lambda-функцию с набором свойств, которыми должны обладать получаемые квазигруппы.
```c++
// Порождение одной бесформенной полиномиально полной 
// квазигруппы порядка 16 методом Джейкобсона-Мэтьюза

Quasigroup::JMQuasigroupFactory factory(16);
Quasigroup::QuasigroupGenerator generator(&factory);

auto q = generator.generate(
        [](Quasigroup::Quasigroup* q) {
            return q->isShapeless() && q->isPolynomiallyComplete(); // логическое условие какой должна быть квазигруппа
        }
);

// какие-то действия с квазигруппой q

delete q;
```
```c++
// Порождение набора из 1000 уникальных полиномиально полных бесформенных
// квазигрупп порядка 16 методом Джейкобсона-Мэтьюза

Quasigroup::JMQuasigroupFactory factory(16);
Quasigroup::QuasigroupGenerator generator(&factory);

auto qSet = generator.generateSet(
        1000,
        [](Quasigroup::Quasigroup* q) {
            return q->isShapeless() && q->isPolynomiallyComplete(); // логическое условие какой должна быть квазигруппа
        }
);

for (auto q : qSet) {
    // какие-то действия с квазигруппой q
    delete q;
}
```

##### Проверка свойств квазигрупп

Для проверки известных свойств доступны следующие методы класса *Quasigroup*. Каждое из bool свойств
можно задать в lambda-функции для генерации квазигруппы с необходимыми свойствами.
```c++
/* 
 * Проверка аффинности
 * При передаче useLightTest = false будет использован оригинальный
 * алгоритм проверки аффинности. По умолчанию используется оптимизированный
 * вариант, использующий тест Лайта.
*/ 
bool isAffine(bool useLightTest = true) const;

// Проверка простоты
bool isSimple() const;

// Проверка ассоциативности
// DEPRECATED
bool isAssociative() const;

// Проверка ассоциативности
bool isAssociativeByLightTest() const;

// Проверка коммутативности
bool isCommutative() const;

// Проверка идемпотентности
bool isIdempotent() const;

// Проверка наличия левой единицы
bool hasLeftUnit() const;

// Проверка наличия правой единицы
bool hasRightUnit() const;

// Проверка наличия единицы
bool hasUnit() const;

// Проверка бесформенности
bool isShapeless() const;

// Проверка того, что тождества вида
// (x * ( ... * x * (x * y)) = y и (((y * x) * x) * ... * x) (k раз)
// выполняются для всех k < 2 * N, где N порядок квазигруппы
bool shapelessIdentitiesIsSatisfied() const;

// Проверка того, что тождества вида
// (x * ( ... * x * (x * y)) = y и (((y * x) * x) * ... * x) (k раз)
// выполняются для конкретного k
bool shapelessIdentitiesIsSatisfied(int k) const;

// Проверка того, что квазигруппа является лупой
// Равносильно hasUnit
bool isLoop() const;

// Проверка того, что квазигруппа является группой
bool isGroup() const;

// Проверка того, что квазигруппа является абелевой группой
bool isAbelianGroup() const;

// Проверка того, что квазигруппа содержит собственную подквазигруппу
bool containsProperSubqusigroup() const;

// Проверка что выполнено тождество (x * y) * x = (z * x) * (y * z)
bool isQuadratical() const;

// Проверка что выполнено тождество (x * y) * x = y
bool isHexagonal() const;

// Проверка что выполнено тождество ((x * y) * z) * z = y
bool isGoldenSquare() const;

// Проверка что выполнено тождество (x * y) * z = (z * y) * x
bool isRightModular() const;

// Проверка что выполнено тождество x * (y * z) = z * (y * x)
bool isLeftModular() const;

// Проверка что выполнено тождество (x * y) * y = (y * x) * x
bool isAffineRegularOctagonal() const;

// Проверка что выполнено тождество (((x * y) * x) * y) * x = y
bool isPentagonal() const;

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
Эксперименты запускаются вызовом метода *run* класса *ExperimentsRunner*. Сигнатура метода:
```c++
// iterations - число итераций эксперимента
// objectsPerIteration - количество обрабатываемых объектов в одной итерации эксперимента
// experiment - проводимый эксперимент
ExperimentalReport *run(int iterations, int objectsPerIteration, Experiment *experiment);
```
На данный момент реализованы следующие эксперименты:
* *QuantitiveExperiment* проводит эксперимент, связанный с измерением типичности свойств объектом
* *GenerationTimeExperiment* измеряет время генерации квазигрупп
* *CheckPropertyTimeExperiment* измеряет время проверки свойств квазигрупп

Результатом работы каждого эксперимента на одной итерации является число: количество подходящих квазигрупп \ 
общее время генерации \ общее время проверки свойств и тд.
На выходе эксперимента будет получен объект класса *ExperimentalReport*, содержающий следующие поля:
```c++
// Порядок квазигрупп, над которыми проводился эксперимент
int quasigroupOrder;

// Число итераций эксперимента
uint iterations;

// Число обрабатываемых объектов на одной итерации
uint objectsPerIteration;

// Набор с результатами работы каждый итерации
std::vector<double> results;

// Среднее арифметическое элементов вектора results
double averageResult;

// Максимальное значение в векторе results
double maxResult;

// Минимальное значение в векторе results
double minResult;

// Вектор отношений результатов эксперимента к objectsPerIteration
std::vector<double> fractions;

// averageResult / objectsPerIteration
double averageFraction;

// maxResult / objectsPerIteration
double maxFraction;

// minResult / objectsPerIteration
double minFraction;
```
Класс *ExperimentalReport* записывается в консоль и файл в формате json, для удобства дальнейшей визуализации результатов.
```c++
// Генерирует 3 раза по 10000 квазигрупп порядка 5 методом Джейкобсона-Мэтьюза
// и считает сколько из них являются полиномиально полными

Quasigroup::JMQuasigroupFactory factory(5);
Quasigroup::ExperimentsRunner runner(&factory);
Quasigroup::QuantitiveExperiment experiment(
    [](Quasigroup::Quasigroup *q) {
        return q->isPolynomiallyComplete(); // логическое условие какой должна быть квазигруппа
    }
);

auto report = runner.run(3, 10000, &experiment);

std::cout << *report << std::endl;

delete report;
```
```json
{
	"type": "experimental_report",
	"results": [
		9959,
		9964,
		9962
	],
	"fractions": [
		0.9959,
		0.9964,
		0.9962
	],
	"quasigroup_order": 5,
	"iterations": 3,
	"objects_per_iteration": 10000,
	"average_result": 9961.67,
	"min_result": 9959,
	"max_result": 9964,
	"average_fraction": 0.996167,
	"min_fraction": 0.9959,
	"max_fraction": 0.9964
}
```
```c++
// Генерирует 5 раз по 1 квазигруппе порядка 128 
// и измеряет сколько времени заняла генерация

Quasigroup::JMQuasigroupFactory factory(128);
Quasigroup::ExperimentsRunner runner(&factory);
Quasigroup::GenerationTimeExperiment experiment;

auto report = runner.run(5, 1, &experiment);

std::cout << *report;

delete report;
```
```json
{
	"type": "experimental_report",
	"results": [
		0.371899,
		0.379093,
		0.359035,
		0.368913,
		0.361926
	],
	"fractions": [
		0.371899,
		0.379093,
		0.359035,
		0.368913,
		0.361926
	],
	"quasigroup_order": 128,
	"iterations": 5,
	"objects_per_iteration": 1,
	"average_result": 0.368173,
	"min_result": 0.359035,
	"max_result": 0.379093,
	"average_fraction": 0.368173,
	"min_fraction": 0.359035,
	"max_fraction": 0.379093
}
```
```c++
// Генерирует 5 раз по 1 квазигруппе порядка 128 
// и измеряет сколько времени проверка полиномиальной полноты

Quasigroup::JMQuasigroupFactory factory(128);
Quasigroup::ExperimentsRunner runner(&factory);
Quasigroup::CheckPropertyTimeExperiment experiment(
    [](Quasigroup::Quasigroup *q) {
        q->isPolynomiallyComplete(); // вызов тех методов, скорость работы которых нужно измерить
    }
);

auto report = runner.run(5, 1, &experiment);

std::cout << *report;

delete report;
```
```json
{
	"type": "experimental_report",
	"results": [
		0.008323,
		0.008492,
		0.00806,
		0.007765,
		0.007774
	],
	"fractions": [
		0.008323,
		0.008492,
		0.00806,
		0.007765,
		0.007774
	],
	"quasigroup_order": 128,
	"iterations": 5,
	"objects_per_iteration": 1,
	"average_result": 0.0080828,
	"min_result": 0.007765,
	"max_result": 0.008492,
	"average_fraction": 0.0080828,
	"min_fraction": 0.007765,
	"max_fraction": 0.008492
}
```