
#include "Utils.h"
#include <G4SystemOfUnits.hh>

G4RotationMatrix *Utils::rotate(double axisX, double axisY, double axisZ) {
    axisX *= deg;
    axisY *= deg;
    axisZ *= deg;
    return new G4RotationMatrix(axisX, axisY, axisZ);
}
