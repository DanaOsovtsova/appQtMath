#ifndef MAINAPP_H
#define MAINAPP_H


#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Mainapp;
}
QT_END_NAMESPACE

class Mainapp : public QMainWindow
{
    Q_OBJECT

public:
    Mainapp(QWidget *parent = nullptr);
    ~Mainapp();

    std::vector<double> solveQuadratic(double a, double b, double c){
        std::vector<double> roots;
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

    double taylorSin(double x, double precision) {
        // Normalize the angle to the range -π to π
        double normalizedAngle = fmod(x + M_PI, 2 * M_PI) - M_PI;

        // Use the built-in sin function for better accuracy
        return sin(normalizedAngle);
    }


    std::vector<int> primeFactors(int n) {//Разлагает число на простые множители
        std::vector<int> factors;
        for (int i = 2; i <= n; i++) {
            while (n % i == 0) {
                factors.push_back(i);
                n /= i;
            }
        }
        return factors;
    }

private slots:
    void on_comboBox_activated(int index);
private:
    Ui::Mainapp *ui;
};
#endif // MAINAPP_H
