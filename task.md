1. class Layer. Определяет слой для рисования. Имеет методы:
- создать новый объект
- изменить цвет пикселя
- изменить цвет всего поля
- установить прозрачность
- установить видимость/невидимость
- заблокировать/разрешить для рисования
- слить с другим слоем
- установить/изменить размер
2. class Canvas. Класс холста. Имеет список слоев. Имеет методы:
-  установить/изменить размер
- добавить/удалить слой
- сохранить/экспортировать
3. class Brush. Класс кисти. Имеет методы:
- установить ширину
- установить прозрачность
- установить цвет
- установить степень размытия краев
- покрасить область на слое. Будет принимать аргументом слой, на котором работает
4. class Palette. Имеет методы:
- установить пипетку
- вернуть цвет
5. class Figure. Родительский класс для всех фигур. Имеет методы:
- нарисовать фигуру с заданными параметрами. Принимает аргументом слой.
- установить цвет контура
- установить толщину контура
- установить прозрачность
- установить заливку