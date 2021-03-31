//
// Created by Сергей on 02.03.2021.
//

#include "Parabola.h"
#include <iostream>
#include "ParabolaUtils.h"

double ParabolaUtils::find_a_1(double x1, double x2) {
    return (Function::evaluate(x2) - Function::evaluate(x1)) / (x2 - x1);
}

double ParabolaUtils::find_a_2(double x1, double x2, double x3) {
    return ((Function::evaluate(x3) - Function::evaluate(x1)) / (x3 - x1) -
            (Function::evaluate(x2) - Function::evaluate(x1)) / (x2 - x1)) / (x3 - x2);
}

double ParabolaUtils::find_x_n(double x1, double x2, double f1, double f2) {
    return (x1 + x2 - f1 / f2) / 2;

}

double Parabola::evaluate() {
    double x1 = a;
    double x3 = b;
    double x2 = (a + b) / 2;
    double eps_n = (b - a) / 2;
    double calcFunction = 3;

    intervals.emplace_back(x1, x3);
    while (eps_n > eps) {
        double x_n = find_x_n(x1, x2, find_a_1(x1, x2), find_a_2(x1, x2, x3));
        calcFunction += 1;
        if (x1 < x_n && x_n < x2 && x2 < x3) {
            calcFunction += 1;
            if (Function::evaluate(x_n) >= Function::evaluate(x2)) {
                x1 = x_n;
            } else {
                x3 = x2;
                x2 = x_n;
            }
        } else if (x1 < x2 && x2 < x_n && x2 < x3) {
            calcFunction += 1;
            if (Function::evaluate(x_n) <= Function::evaluate(x2)) {
                x1 = x2;
                x2 = x_n;
            } else {
                x3 = x_n;
            }
        } else {
            break;
        }
        eps_n = (x3 - x1) / 2;
        intervals.emplace_back(x1, x3);
    }

    return std::cout << calcFunction << " ", x2;
}

std::vector<std::pair<double, double> > Parabola::getIntervals() {
    evaluate();
    for (int i = intervals.size(); i < 30; i++) {
        intervals.emplace_back(intervals[intervals.size() - 1].first, intervals[intervals.size() - 1].second);
    }
    return intervals;
}
