//
// Created by Сергей on 03.03.2021.
//
#include <iostream>
#include "CombinedBrent.h"
#include <tuple>

double CombinedBrent::evaluate() {
    double eps_n = (c - a) / 2;

    bool usedParabola = false, f = true;
    double f_x = Function::evaluate(x);
    double f_v = f_x;
    double f_w = f_x;
    double f_u;
    double calcFunction = 0;
    intervals.emplace_back(usedParabola, a, c);

    while (eps_n > eps) {
        double g = e;
        e = d;
        double temp_u;

        double tol = eps * fabs(x) + eps / 10;
        if (fabs(x - (a + c) / 2) + (c - a) / 2 <= 2 * tol) {
            break;
        }
        if (Function::different(x, v, w)
            && Function::different(f_x, f_w, f_v)) {
            temp_u = ParabolaUtils::find_x_n(x, w, find_a_1(x, w), find_a_2(x, w, v));
            if (f) {
                calcFunction += 3;
                f = false;
            } else {
                calcFunction += 1;
            }
            if ((temp_u > a || Function::equals(temp_u, a)) && (temp_u < c || Function::equals(temp_u, c)) &&
                fabs(temp_u - x) < g / 2) {
                usedParabola = true;
                u = temp_u;
                if (u - a < 2 * tol || c - u < 2 * tol) {
                    u = x - Function::sign(x - (a + c) / 2) * tol;
                }
            }
        } else {
            if (x < (a + c) / 2) {
                u = x + K * (c - x);
                e = c - x;
            } else {
                u = x - K * (x - a);
                e = x - a;
            }
        }

        if (fabs(u - x) < tol) {
            u = x + Function::sign(x - (a + c) / 2) * tol;
        }
        d = fabs(x - u);
        f_u = Function::evaluate(u);
        calcFunction++;
        if (f_u < f_x) {
            if (u > x || Function::equals(u, x)) {
                a = x;
            } else {
                c = x;
            }
            v = w;
            w = x;
            x = u;
            f_v = f_w;
            f_w = f_x;
            f_x = f_u;
        } else {
            if (u > x || Function::equals(u, x)) {
                c = u;
            } else {
                a = u;
            }
            if (f_u < f_w || Function::equals(f_u, f_w) || Function::equals(w, x)) {
                v = w;
                w = u;
                f_v = f_w;
                f_w = f_u;
            } else if (f_u <= f_w || Function::equals(f_u, f_w) || Function::equals(v, x) || Function::equals(v, w)) {
                v = u;
                f_v = f_u;
            }
        }

        intervals.emplace_back(usedParabola, a, c);
    }
    return std::cout << calcFunction << " ", (a + c) / 2;
}

std::vector<std::tuple<bool, double, double> > CombinedBrent::getIntervals() {
    evaluate();
    for (int i = intervals.size(); i < 30; i++) {
        intervals.emplace_back(false, a, c);
    }
    return intervals;
}