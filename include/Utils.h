
#ifndef DIPLOM_UTILS_H
#define DIPLOM_UTILS_H


#include <G4RotationMatrix.hh>

class Utils {
public:
   static G4RotationMatrix *rotate (double axisX, double axisY, double axisZ);
};


#endif //DIPLOM_UTILS_H
