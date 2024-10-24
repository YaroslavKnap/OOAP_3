#include <iostream>
#include <vector>
#include <string>

// Абстрактний клас фасаду
class Facade {
public:
    // Відображає інформацію про фасад
    virtual void display() const = 0;
    // Обчислює вартість фасаду
    virtual double calculateCost() const = 0;
    virtual ~Facade() = default;
};

// Клас суцільного фасаду
class SolidFacade : public Facade {
private:
    double width;
    double height;
    double pricePerSquareMeter;
public:
    // Конструктор для ініціалізації розмірів та ціни за кв.м.
    SolidFacade(double w, double h, double price)
        : width(w), height(h), pricePerSquareMeter(price) {}

    // Метод для відображення інформації про фасад
    void display() const override {
        std::cout << "Solid Facade (суцільний): " << width << "x" << height << " м.\n";
    }

    // Метод для обчислення вартості фасаду
    double calculateCost() const override {
        return width * height * pricePerSquareMeter;
    }
};

// Клас фасаду з отвором для скла (вітрина)
class GlassFacade : public Facade {
private:
    double width;
    double height;
    double pricePerSquareMeter;
public:
    // Конструктор для ініціалізації розмірів та ціни за кв.м.
    GlassFacade(double w, double h, double price)
        : width(w), height(h), pricePerSquareMeter(price) {}

    // Метод для відображення інформації про фасад
    void display() const override {
        std::cout << "Glass Facade (вітрина): " << width << "x" << height << " м.\n";
    }

    // Метод для обчислення вартості фасаду
    double calculateCost() const override {
        return width * height * pricePerSquareMeter;
    }
};

// Абстрактна фабрика для створення фасадів
// Цей клас визначає інтерфейс для створення фасадів
class MaterialFactory {
public:
    // Створює суцільний фасад
    virtual Facade* createSolidFacade(double width, double height) = 0;
    // Створює вітрину (фасад з отвором для скла)
    virtual Facade* createGlassFacade(double width, double height) = 0;
    virtual ~MaterialFactory() = default;
};

// Конкретна фабрика для плівкових фасадів
// Реалізація методів для плівкових фасадів
class FilmMaterialFactory : public MaterialFactory {
public:
    Facade* createSolidFacade(double width, double height) override {
        return new SolidFacade(width, height, 200); // Ціна за м2 для плівкових
    }

    Facade* createGlassFacade(double width, double height) override {
        return new GlassFacade(width, height, 250); // Ціна за м2 для плівкових
    }
};

// Конкретна фабрика для фарбованих фасадів
// Реалізація методів для фарбованих фасадів
class PaintedMaterialFactory : public MaterialFactory {
public:
    Facade* createSolidFacade(double width, double height) override {
        return new SolidFacade(width, height, 300); // Ціна за м2 для фарбованих
    }

    Facade* createGlassFacade(double width, double height) override {
        return new GlassFacade(width, height, 350); // Ціна за м2 для фарбованих
    }
};

// Конкретна фабрика для пластикових фасадів
// Реалізація методів для пластикових фасадів
class PlasticMaterialFactory : public MaterialFactory {
public:
    Facade* createSolidFacade(double width, double height) override {
        return new SolidFacade(width, height, 400); // Ціна за м2 для пластикових
    }

    Facade* createGlassFacade(double width, double height) override {
        return new GlassFacade(width, height, 450); // Ціна за м2 для пластикових
    }
};

// Клас для управління замовленням
class Order {
private:
    std::vector<Facade*> facades;
public:
    // Додає фасад до замовлення
    void addFacade(Facade* facade) {
        facades.push_back(facade);
    }

    // Відображає всі фасади у замовленні
    void displayOrder() const {
        std::cout << "Замовлення включає:\n";
        for (const auto& facade : facades) {
            facade->display();
        }
    }

    // Розраховує загальну вартість замовлення
    double calculateTotalCost() const {
        double totalCost = 0;
        for (const auto& facade : facades) {
            totalCost += facade->calculateCost();
        }
        return totalCost;
    }

    // Деструктор для видалення фасадів після завершення роботи
    ~Order() {
        for (auto& facade : facades) {
            delete facade;
        }
    }
};

int main() {
    // Вибір конкретної фабрики в залежності від матеріалу
    MaterialFactory* factory = nullptr;
    int materialChoice;

    std::cout << "Виберіть тип матеріалу (1 - Плівковий, 2 - Фарбований, 3 - Пластиковий): ";
    std::cin >> materialChoice;

    // Створення відповідної фабрики на основі вибору користувача
    switch (materialChoice) {
    case 1:
        factory = new FilmMaterialFactory();
        break;
    case 2:
        factory = new PaintedMaterialFactory();
        break;
    case 3:
        factory = new PlasticMaterialFactory();
        break;
    default:
        std::cout << "Невірний вибір!\n";
        return 1;
    }

    // Створюємо замовлення
    Order order;
    int facadeType;
    double width, height;

    // Введення інформації про фасади
    while (true) {
        std::cout << "Виберіть тип фасаду (1 - Суцільний, 2 - Вітрина, 0 - Завершити): ";
        std::cin >> facadeType;

        if (facadeType == 0) {
            break;
        }

        std::cout << "Введіть ширину (м): ";
        std::cin >> width;
        std::cout << "Введіть висоту (м): ";
        std::cin >> height;

        // Створення фасаду через фабрику
        if (facadeType == 1) {
            order.addFacade(factory->createSolidFacade(width, height));
        }
        else if (facadeType == 2) {
            order.addFacade(factory->createGlassFacade(width, height));
        }
        else {
            std::cout << "Невірний вибір!\n";
        }
    }

    // Виведення інформації про замовлення
    order.displayOrder();
    // Виведення загальної вартості замовлення
    std::cout << "Загальна вартість: " << order.calculateTotalCost() << " грн.\n";

    // Видалення фабрики після завершення
    delete factory;
    return 0;
}
