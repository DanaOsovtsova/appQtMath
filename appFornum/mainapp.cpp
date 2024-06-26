#include "mainapp.h"
#include "ui_mainapp.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <algorithm>
#include <QStandardItemModel>
#include <QMessageBox> //для вывода сообщений
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <QSizePolicy>
#include <QTableView>
#include <QDataStream>
#include <QStringList>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>


using namespace std;

class MathHelper {
public:

    bool isPrime(int n) { // Проверяет, является ли число простым
        if (n <= 1) {
            return false;
        }
        for (int i = 2; i <= sqrt(n); i++) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }


    vector<int> primeFactors(int n) {//Разлагает число на простые множители
        vector<int> factors;
        for (int i = 2; i <= n; i++) {
            while (n % i == 0) {
                factors.push_back(i);
                n /= i;
            }
        }
        return factors;
    }


    double sinTaylor(double x, int n = 10) { // Вычисляет значение sin(x) с помощью ряда Тейлора
        double result = 0.0;
        for (int i = 0; i < n; i++) {
            result += pow(-1, i) * pow(x, 2 * i + 1) / factorial(2 * i + 1);
        }
        return result;
    }


    vector<double> solveQuadratic(double a, double b, double c) { // Находит действительные корни квадратного уравнения
        vector<double> roots;
        double discriminant = b * b - 4 * a * c;
        if (discriminant < 0) {
            return roots;
        } else if (discriminant == 0) {
            roots.push_back(-b / (2 * a));
        } else {
            roots.push_back((-b + sqrt(discriminant)) / (2 * a));
            roots.push_back((-b - sqrt(discriminant)) / (2 * a));
        }
        return roots;
    }

private:

    long long factorial(int n) { // Вспомогательная функция для вычисления факториала
        if (n == 0 || n == 1) {
            return 1;
        }
        return n * factorial(n - 1);
    }
};

// Тесты
/*
int main() {
    MathHelper math_helper;

    // Тест на простое число
    std::cout << "Is 7 prime? " << (math_helper.isPrime(7) ? "Yes" : "No") << std::endl;
    std::cout << "Is 12 prime? " << (math_helper.isPrime(12) ? "Yes" : "No") << std::endl;

    // Тест на разложение на простые множители
    std::vector<int> factors = math_helper.primeFactors(12);
    std::cout << "Prime factors of 12: ";
    for (int factor : factors) {
        std::cout << factor << " ";
    }
    std::cout << std::endl;

    // Тест на вычисление sin(x) с помощью ряда Тейлора
    double x = M_PI / 4;
    std::cout << "sin(" << x << ") = " << math_helper.sinTaylor(x) << std::endl;

    // Тест на нахождение действительных корней квадратного уравнения
    std::vector<double> roots = math_helper.solveQuadratic(1, 0, -1);
    std::cout << "Roots of x^2 - 1 = 0: ";
    for (double root : roots) {
        std::cout << root << " ";
    }
    std::cout << std::endl;

    return 0;
}*/


Mainapp::Mainapp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Mainapp)
{
    ui->setupUi(this);

}

Mainapp::~Mainapp()
{
    delete ui;
}


void Mainapp::on_comboBox_activated(int index)
{
    switch (index) {
    case 0: {
        QDialog* dialog = new QDialog(this);
        dialog->setWindowTitle("PRIME");
        dialog->setMinimumSize(800, 600);

        QVBoxLayout* layout = new QVBoxLayout(dialog);

        // Add a label for angle input
        QLabel* numLabel = new QLabel("Enter number:", dialog);
        layout->addWidget(numLabel);

        // Add a QLineEdit for input
        QLineEdit* inputField = new QLineEdit(dialog);
        layout->addWidget(inputField);

        QLabel* noutLabel = new QLabel("Answer:", dialog);
        layout->addWidget(noutLabel);

        // Add a QLineEdit for result output
        QLineEdit* resultOutput = new QLineEdit(dialog);
        resultOutput->setReadOnly(true);
        layout->addWidget(resultOutput);

        // Add a button for calculation
        QPushButton* calculateButton = new QPushButton("Calculate", dialog);
        layout->addWidget(calculateButton);

        // Connect the calculateButton to a slot that performs the calculation
        connect(calculateButton, &QPushButton::clicked, this, [inputField, resultOutput, this]() {
            bool ok;
            int number = inputField->text().toInt(&ok);
            if (ok) {
                if (isPrime(number)) {
                    resultOutput->setText(QString("The number %1 is prime.").arg(number));
                } else {
                    vector<int> factors = primeFactors(number);
                    QString message = QString("The number %1 is not prime. Its prime factors are: ").arg(number);
                    for (int factor : factors) {
                        message += QString("%1 ").arg(factor);
                    }
                    resultOutput->setText(message);
                }
            } else {
                resultOutput->setText("Please enter a valid integer number.");
            }
        });

        QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        layout->addWidget(buttonBox);

        connect(buttonBox, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, dialog, &QDialog::reject);

        if (dialog->exec() == QDialog::Accepted) {
            // Handle the acceptance of the dialog
            // ...
        }
        break;
    }

        case 1: {
            QDialog* dialog = new QDialog(this);
            dialog->setWindowTitle("SIN");
            dialog->setMinimumSize(800, 600);

            QVBoxLayout* layout = new QVBoxLayout(dialog);

            // Add a label for angle input
            QLabel* angleLabel = new QLabel("Enter angle in radians:", dialog);
            layout->addWidget(angleLabel);

            // Add a QLineEdit for angle input
            QLineEdit* angleInput = new QLineEdit(dialog);
            layout->addWidget(angleInput);

            // Add a QLineEdit for result output
            QLineEdit* resultOutput = new QLineEdit(dialog);
            resultOutput->setReadOnly(true);
            layout->addWidget(resultOutput);

            // Add a button for calculation
            QPushButton* calculateButton = new QPushButton("Calculate", dialog);
            layout->addWidget(calculateButton);

            // Connect the calculateButton to a slot that performs the calculation
            connect(calculateButton, &QPushButton::clicked, this, [angleInput, resultOutput]() {
                bool ok;
                double angle = angleInput->text().toDouble(&ok);
                if (ok) {
                    double sinValue = sin(angle);
                    resultOutput->setText(QString("Sin(%1) = %2").arg(angle).arg(sinValue));
                } else {
                    resultOutput->setText("Please enter a valid number.");
                }
            });


            QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
            layout->addWidget(buttonBox);

            connect(buttonBox, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
            connect(buttonBox, &QDialogButtonBox::rejected, dialog, &QDialog::reject);

            if (dialog->exec() == QDialog::Accepted) {
                // Handle the acceptance of the dialog
                // ...
            }
            break;
        }



    case 2: {
        QDialog* dialog = new QDialog(this);
        dialog->setWindowTitle("EQUATION");
        dialog->setMinimumSize(800, 600);

        QVBoxLayout* layout = new QVBoxLayout(dialog);

        // Add a label for angle input
        QLabel* kvLabel = new QLabel("Enter квадратное уравнение в виде: 2x^2 + 24x + 9", dialog);
        layout->addWidget(kvLabel);

        // Add a QLineEdit for input
        QLineEdit* inputField = new QLineEdit(dialog);
        layout->addWidget(inputField);

        QLabel* rootLabel = new QLabel("Answer:", dialog);
        layout->addWidget(rootLabel);

        // Add a QLineEdit for result output
        QLineEdit* resultOutput = new QLineEdit(dialog);
        resultOutput->setReadOnly(true);
        layout->addWidget(resultOutput);

        // Add a button for calculation
        QPushButton* calculateButton = new QPushButton("Calculate", dialog);
        layout->addWidget(calculateButton);

        // Connect the calculateButton to a slot that performs the calculation
        connect(calculateButton, &QPushButton::clicked, this, [inputField, resultOutput, this]() {
            // Get the input equation
            QString equation = inputField->text();

            // Parse the equation and extract the coefficients
            QStringList parts = equation.split("x^2 + ");
            if (parts.size() != 2) {
                resultOutput->setText("Invalid equation format");
                return;
            }

            bool ok;
            double a = parts[0].toDouble(&ok);
            if (!ok) {
                resultOutput->setText("Invalid equation format");
                return;
            }

            double b = parts[1].split("x + ")[0].toDouble(&ok);
            if (!ok) {
                resultOutput->setText("Invalid equation format");
                return;
            }

            double c = parts[1].split("x + ").last().toDouble(&ok);
            if (!ok) {
                resultOutput->setText("Invalid equation format");
                return;
            }

            vector<double> roots = solveQuadratic(a, b, c);

            // Update the result output
            if (roots.empty()) {
                resultOutput->setText("No real roots");
            } else if (roots.size() == 1) {
                resultOutput->setText("Result: x = " + QString::number(roots[0]));
            } else {
                resultOutput->setText("Results: x1 = " + QString::number(roots[0]) + ", x2 = " + QString::number(roots[1]));
            }
        });


        QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        layout->addWidget(buttonBox);

        connect(buttonBox, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, dialog, &QDialog::reject);

        if (dialog->exec() == QDialog::Accepted) {
            // Handle the acceptance of the dialog
            // ...
        }
        break;
    }
    default:
        break;
    }
}
