#include <iostream>
#include <vector>
#include <string>

// ����������� ���� ������
class Facade {
public:
    // ³������� ���������� ��� �����
    virtual void display() const = 0;
    // �������� ������� ������
    virtual double calculateCost() const = 0;
    virtual ~Facade() = default;
};

// ���� ���������� ������
class SolidFacade : public Facade {
private:
    double width;
    double height;
    double pricePerSquareMeter;
public:
    // ����������� ��� ����������� ������ �� ���� �� ��.�.
    SolidFacade(double w, double h, double price)
        : width(w), height(h), pricePerSquareMeter(price) {}

    // ����� ��� ����������� ���������� ��� �����
    void display() const override {
        std::cout << "Solid Facade (���������): " << width << "x" << height << " �.\n";
    }

    // ����� ��� ���������� ������� ������
    double calculateCost() const override {
        return width * height * pricePerSquareMeter;
    }
};

// ���� ������ � ������� ��� ���� (������)
class GlassFacade : public Facade {
private:
    double width;
    double height;
    double pricePerSquareMeter;
public:
    // ����������� ��� ����������� ������ �� ���� �� ��.�.
    GlassFacade(double w, double h, double price)
        : width(w), height(h), pricePerSquareMeter(price) {}

    // ����� ��� ����������� ���������� ��� �����
    void display() const override {
        std::cout << "Glass Facade (������): " << width << "x" << height << " �.\n";
    }

    // ����� ��� ���������� ������� ������
    double calculateCost() const override {
        return width * height * pricePerSquareMeter;
    }
};

// ���������� ������� ��� ��������� ������
// ��� ���� ������� ��������� ��� ��������� ������
class MaterialFactory {
public:
    // ������� ��������� �����
    virtual Facade* createSolidFacade(double width, double height) = 0;
    // ������� ������ (����� � ������� ��� ����)
    virtual Facade* createGlassFacade(double width, double height) = 0;
    virtual ~MaterialFactory() = default;
};

// ��������� ������� ��� �������� ������
// ��������� ������ ��� �������� ������
class FilmMaterialFactory : public MaterialFactory {
public:
    Facade* createSolidFacade(double width, double height) override {
        return new SolidFacade(width, height, 200); // ֳ�� �� �2 ��� ��������
    }

    Facade* createGlassFacade(double width, double height) override {
        return new GlassFacade(width, height, 250); // ֳ�� �� �2 ��� ��������
    }
};

// ��������� ������� ��� ���������� ������
// ��������� ������ ��� ���������� ������
class PaintedMaterialFactory : public MaterialFactory {
public:
    Facade* createSolidFacade(double width, double height) override {
        return new SolidFacade(width, height, 300); // ֳ�� �� �2 ��� ����������
    }

    Facade* createGlassFacade(double width, double height) override {
        return new GlassFacade(width, height, 350); // ֳ�� �� �2 ��� ����������
    }
};

// ��������� ������� ��� ����������� ������
// ��������� ������ ��� ����������� ������
class PlasticMaterialFactory : public MaterialFactory {
public:
    Facade* createSolidFacade(double width, double height) override {
        return new SolidFacade(width, height, 400); // ֳ�� �� �2 ��� �����������
    }

    Facade* createGlassFacade(double width, double height) override {
        return new GlassFacade(width, height, 450); // ֳ�� �� �2 ��� �����������
    }
};

// ���� ��� ��������� �����������
class Order {
private:
    std::vector<Facade*> facades;
public:
    // ���� ����� �� ����������
    void addFacade(Facade* facade) {
        facades.push_back(facade);
    }

    // ³������� �� ������ � ���������
    void displayOrder() const {
        std::cout << "���������� ������:\n";
        for (const auto& facade : facades) {
            facade->display();
        }
    }

    // ��������� �������� ������� ����������
    double calculateTotalCost() const {
        double totalCost = 0;
        for (const auto& facade : facades) {
            totalCost += facade->calculateCost();
        }
        return totalCost;
    }

    // ���������� ��� ��������� ������ ���� ���������� ������
    ~Order() {
        for (auto& facade : facades) {
            delete facade;
        }
    }
};

int main() {
    // ���� ��������� ������� � ��������� �� ��������
    MaterialFactory* factory = nullptr;
    int materialChoice;

    std::cout << "������� ��� �������� (1 - ��������, 2 - ����������, 3 - �����������): ";
    std::cin >> materialChoice;

    // ��������� �������� ������� �� ����� ������ �����������
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
        std::cout << "������� ����!\n";
        return 1;
    }

    // ��������� ����������
    Order order;
    int facadeType;
    double width, height;

    // �������� ���������� ��� ������
    while (true) {
        std::cout << "������� ��� ������ (1 - ���������, 2 - ³�����, 0 - ���������): ";
        std::cin >> facadeType;

        if (facadeType == 0) {
            break;
        }

        std::cout << "������ ������ (�): ";
        std::cin >> width;
        std::cout << "������ ������ (�): ";
        std::cin >> height;

        // ��������� ������ ����� �������
        if (facadeType == 1) {
            order.addFacade(factory->createSolidFacade(width, height));
        }
        else if (facadeType == 2) {
            order.addFacade(factory->createGlassFacade(width, height));
        }
        else {
            std::cout << "������� ����!\n";
        }
    }

    // ��������� ���������� ��� ����������
    order.displayOrder();
    // ��������� �������� ������� ����������
    std::cout << "�������� �������: " << order.calculateTotalCost() << " ���.\n";

    // ��������� ������� ���� ����������
    delete factory;
    return 0;
}
