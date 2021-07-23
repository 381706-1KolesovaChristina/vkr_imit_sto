# vkr_imit_sto
Выпускная квалификационная работа «Применение метода имитационного моделирования для исследования системы технического обслуживания автомобилей»

Поступление машин на СТО происходит в случайные моменты времени. В один момент времени может поступить только одна машина. Время прибытия определяется временными интервалами между поступлением автомобилей. Эти интервалы являются случайными величинами и задаются с помощью законов распределения. 
На СТО автомобили могут поступить на ремонт определенной сложности или на техническое обслуживание, либо сначала поступить на ТО, а затем на ремонт средней сложности. 
Для осуществления обслуживания на СТО могут присутствовать специализированные боксы, либо могут использоваться универсальные боксы.
Время обслуживания и его стоимость задаются с помощью случайных величин и зависят от типа обслуживания. Очевидно, чем сложнее обслуживание, тем больше его стоимость и затраченное на него время. 

В файле generators.h перечислены прототипы используемых в программе генераторов случайных чисел. В файле generators.cpp представлены реализации описанных выше генераторов случайных чисел.
В файле request.h описан класс Req, который хранит все необходимые данные заявки и обеспечивает работу с заявкой. В файле request.cpp представлена реализация методов класса Req.
В файле servDevice.h описан класс Dev, который хранит данные обслуживающего устройства. В файле servDevice.cpp представлена реализация методов класса Dev.
В файле simulCycle.h перечислены прототипы функций, используемых для работы основного имитационного цикла, а также самой функции основного цикла.В файле simulCycle.cpp представлена реализация перечисленных выше функций.
В основном имитационном цикле программы осуществляются изменение таймера модельного времени и соответствующие изменения в боксах обслуживания и очередях. 
	Коррекция таймера модельного времени осуществляется с переменным шагом. Значения таймера совпадают с моментами поступления заявок в систему. 
  
