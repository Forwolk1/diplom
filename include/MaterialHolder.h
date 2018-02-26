
#ifndef DIPLOM_MATERIALHOLDER_H
#define DIPLOM_MATERIALHOLDER_H


#include <G4Material.hh>

class MaterialHolder {
private:
    MaterialHolder();
    ~MaterialHolder();
public:
    G4Material * sampleMaterial1 ();
    G4Material * sampleMaterial2 ();
    G4Material * sampleMaterial3 ();
    G4Material * sampleMaterial4 ();
    G4Material * sampleMaterial5 ();
    G4Material * sampleMaterial6 ();
    G4Material * sampleMaterial7 ();
    static MaterialHolder &getInstance();
};


#endif //DIPLOM_MATERIALHOLDER_H
