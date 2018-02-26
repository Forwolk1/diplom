
#ifndef B1_GEANTGEOMETRY_H
#define B1_GEANTGEOMETRY_H


#include <G4VUserDetectorConstruction.hh>

class GeantGeometry : public G4VUserDetectorConstruction {
public:
    virtual G4VPhysicalVolume *Construct();
};


#endif //B1_GEANTGEOMETRY_H
