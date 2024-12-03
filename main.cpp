#include <QApplication>
#include <QPushButton>
#include <QMessageBox>

int main(int argc, char *argv[]) {
    // Создаем объект приложения
    QApplication app(argc, argv);

    // Создаем кнопку
    QPushButton button("Нажми меня");
    button.resize(200, 100);

    // Подключаем сигнал нажатия кнопки к слоту для показа сообщения
    QObject::connect(&button, &QPushButton::clicked, [&]() {
        QMessageBox::information(nullptr, "Пример Qt6", "Кнопка нажата!");
    });

    // Показываем кнопку
    button.show();

    // Запускаем главный цикл приложения
    return app.exec();
}
