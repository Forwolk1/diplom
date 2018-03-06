#include <G4LogicalVolume.hh>
#include <G4Box.hh>
#include <ObjectHolder.h>
#include "GeantGeometry.h"


G4VPhysicalVolume *GeantGeometry::Construct() {
    auto objectHolder = ObjectHolder();
    return objectHolder.installationPlacement();
}
