#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int x1 = 33;
    int y1 = 45;

    double low_point_angle_y45 = ((atan2(y1, x1)) * 180 / 3.1415);

    int x2 = 59;
    int y2 = 40;

    double up_point_angle_y40 = ((atan2(y2, x2)) * 180 / 3.1415);
    cout << "low_point_angle_y45: " << low_point_angle_y45 << endl;
    cout << "up_point_angle_y40: " << up_point_angle_y40 << endl;
    cout << "difference: " << low_point_angle_y45 - up_point_angle_y40;
}
