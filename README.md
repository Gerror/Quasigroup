# Quasigroup

## Описание

Класс квазигрупп, реализованный на языке C++ в рамках выполнения курсовой работы. <br />
В классе реализованы три основных метода - генерация случайной квазигруппы, <br />
проверка сгенерированной квазигруппы на афинность и простоту. <br />
Так же был реализован класс кубов инцидентности, являющийся вспомогательным <br />
при генерации квазигрупп. <br />
Подробное описание программной реализации алгоритмов, а так же ссылки на соответствующую литературу, <br />
можно найти в файле Course_work.pdf. <br />

Программа при запуске вызывает функцию Test, осуществляющую серию из нескольких генераций квазигрупп <br />
всех порядков от 4 до 128 и проверки их на афинность и простоту. Замеряется среднее и худшее время работы <br />
алгоритмов на всех заданных порядках. Измеренное время, а также seed генерации сохраняются в соответствующих файлах.
