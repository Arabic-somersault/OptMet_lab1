#include <iostream>
#include "Dichotomy.h"
#include "Parabola.h"
#include "GoldenRatio.h"
#include "Fibonacci.h"
#include "CombinedBrent.h"

using namespace std;

int main() {
    Dichotomy res_d(0.5, 4, 0.001, 0.00000001);
    cout << "Method Dichotomy: " << res_d.evaluate() << endl;
    Parabola res_p(0.5, 4, 0.001);
    cout << "The parabola method: " << res_p.evaluate() << endl;
    GoldenRatio res_gr(0.5, 4, 0.001);
    cout << "The golder ratio method: " << res_gr.evaluate() << endl;
    Fibonacci res_f(0.5, 4, 0.001);
    cout << "The fibonacci method: " << res_f.evaluate() << endl;
    CombinedBrent res_cb(0.5, 4, 0.001);
    cout << "The combinedBrent method: " << res_cb.evaluate() << endl;
    return 0;
}