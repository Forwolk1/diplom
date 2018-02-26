
#ifndef DIPLOM_OBJECTHOLDER_H
#define DIPLOM_OBJECTHOLDER_H


#include <G4LogicalVolume.hh>

class ObjectHolder {
public:
    G4LogicalVolume *installationLog();
    G4LogicalVolume *tableLog();
    G4LogicalVolume *planeLog();
    G4LogicalVolume *safeLog();
    G4LogicalVolume *shelfLog();
    G4LogicalVolume *wallsLog();
    G4LogicalVolume *windowLog();
    G4LogicalVolume *bataryLog();
    G4LogicalVolume *doorLog();
    G4LogicalVolume *floorAndCellingLog();
};


#endif //DIPLOM_OBJECTHOLDER_H
