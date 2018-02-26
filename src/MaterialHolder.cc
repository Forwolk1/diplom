
#include "MaterialHolder.h"
#include <G4LogicalVolume.hh>
#include <G4SystemOfUnits.hh>
#include <G4NistManager.hh>

//SiO2 1900
G4Material * MaterialHolder::sampleMaterial1 () {
    G4NistManager *nist = G4NistManager::Instance();
    double density = 1900 * kg / m3;
    G4Material *Si2O3 = new G4Material("Si2O3", density, 2);
    Si2O3->AddElement(nist->FindOrBuildElement("Si"), 1);
    Si2O3->AddElement(nist->FindOrBuildElement("O"), 2);

    return Si2O3;
}

//Al2O3 9950
G4Material * MaterialHolder::sampleMaterial2 () {
    G4NistManager *nist = G4NistManager::Instance();
    double density = 9950 * kg / m3;
    G4Material *Al2O3 = new G4Material("Al2O3", density, 2);
    Al2O3->AddElement(nist->FindOrBuildElement("Al"), 2);
    Al2O3->AddElement(nist->FindOrBuildElement("O"), 3);

    G4Material *SO4 = new G4Material("SO4", density, 2);
    SO4->AddElement(nist->FindOrBuildElement("S"), 1);
    SO4->AddElement(nist->FindOrBuildElement("O"), 4);

    G4Material *sampleMaterial = new G4Material("Al2O3_sample", density, 5);
    sampleMaterial->AddMaterial(Al2O3, 99.2 * perCent);
    sampleMaterial->AddMaterial(SO4, 0.5 * perCent);
    sampleMaterial->AddElement(nist->FindOrBuildElement("Cl"), 0.1 * perCent);
    sampleMaterial->AddElement(nist->FindOrBuildElement("Fe"), 0.1 * perCent);
    sampleMaterial->AddElement(nist->FindOrBuildElement("Si"), 0.1 * perCent);

    return sampleMaterial;
}

//Fe2O3 5240
G4Material * MaterialHolder::sampleMaterial3 () {
    G4NistManager *nist = G4NistManager::Instance();
    double density = 5240 * kg / m3;
    G4Material *Fe2O3 = new G4Material("Fe2O3", density, 2);
    Fe2O3->AddElement(nist->FindOrBuildElement("Fe"), 2);
    Fe2O3->AddElement(nist->FindOrBuildElement("O"), 3);

    G4Material *SO4 = new G4Material("SO4", density, 2);
    SO4->AddElement(nist->FindOrBuildElement("S"), 1);
    SO4->AddElement(nist->FindOrBuildElement("O"), 4);

    G4Material *sampleMaterial = new G4Material("Fe2O3_sample", density, 7);
    sampleMaterial->AddMaterial(Fe2O3, 99.76 * perCent);
    sampleMaterial->AddMaterial(SO4, 0.12 * perCent);
    sampleMaterial->AddElement(nist->FindOrBuildElement("K"), 0.01 * perCent);
    sampleMaterial->AddElement(nist->FindOrBuildElement("Na"), 0.01 * perCent);
    sampleMaterial->AddElement(nist->FindOrBuildElement("Mg"), 0.025 * perCent);
    sampleMaterial->AddElement(nist->FindOrBuildElement("Ca"), 0.025 * perCent);
    sampleMaterial->AddElement(nist->FindOrBuildElement("Si"), 0.05 * perCent);

    return sampleMaterial;
}

//Ca(OH)2 2210
G4Material * MaterialHolder::sampleMaterial4 () {
    G4NistManager *nist = G4NistManager::Instance();
    double density = 2210 * kg / m3;
    G4Material *CaOH2 = new G4Material("Ca(OH)2", density, 3);
    CaOH2->AddElement(nist->FindOrBuildElement("Ca"), 1);
    CaOH2->AddElement(nist->FindOrBuildElement("O"), 2);
    CaOH2->AddElement(nist->FindOrBuildElement("H"), 2);

    G4Material *CaCO3 = new G4Material("CaCO3", density, 3);
    CaCO3->AddElement(nist->FindOrBuildElement("Ca"), 1);
    CaCO3->AddElement(nist->FindOrBuildElement("C"), 1);
    CaCO3->AddElement(nist->FindOrBuildElement("O"), 3);

    G4Material *sampleMaterial = new G4Material("Ca(OH)2_sample", density, 4);
    sampleMaterial->AddMaterial(CaOH2, 97.44 * perCent);
    sampleMaterial->AddMaterial(CaCO3, 1.5 * perCent);
    sampleMaterial->AddElement(nist->FindOrBuildElement("Fe"), 0.01 * perCent);
    sampleMaterial->AddElement(nist->FindOrBuildElement("N"), 0.05 * perCent);

    return sampleMaterial;
}

//MgO 3580
G4Material * MaterialHolder::sampleMaterial5 () {
    G4NistManager *nist = G4NistManager::Instance();
    double density = 3580 * kg / m3;
    G4Material *MgO = new G4Material("MgO", density, 2);
    MgO->AddElement(nist->FindOrBuildElement("Mg"), 1);
    MgO->AddElement(nist->FindOrBuildElement("O"), 1);

    G4Material *sampleMaterial = new G4Material("MgO_sample", density, 3);
    sampleMaterial->AddMaterial(MgO, 99.97 * perCent);
    sampleMaterial->AddElement(nist->FindOrBuildElement("Al"), 0.01 * perCent);
    sampleMaterial->AddElement(nist->FindOrBuildElement("Si"), 0.02 * perCent);

    return sampleMaterial;
}

//NaOH 2130
G4Material * MaterialHolder::sampleMaterial6 () {
    G4NistManager *nist = G4NistManager::Instance();
    double density = 2130 * kg / m3;
    G4Material *NaOH = new G4Material("NaOH", density, 3);
    NaOH->AddElement(nist->FindOrBuildElement("Na"), 1);
    NaOH->AddElement(nist->FindOrBuildElement("O"), 1);
    NaOH->AddElement(nist->FindOrBuildElement("H"), 1);


    G4Material *Na2CO3 = new G4Material("Na2CO3", density, 3);
    Na2CO3->AddElement(nist->FindOrBuildElement("Na"), 2);
    Na2CO3->AddElement(nist->FindOrBuildElement("C"), 1);
    Na2CO3->AddElement(nist->FindOrBuildElement("O"), 3);

    G4Material *sampleMaterial = new G4Material("NaOH_sample", density, 2);
    sampleMaterial->AddMaterial(NaOH, 99.37 * perCent);
    sampleMaterial->AddMaterial(Na2CO3, 0.43 * perCent);

    return sampleMaterial;
}

//KOH 2120
G4Material * MaterialHolder::sampleMaterial7 () {
    G4NistManager *nist = G4NistManager::Instance();
    double density = 2120 * kg / m3;
    G4Material *KOH = new G4Material("KOH", density, 3);
    KOH->AddElement(nist->FindOrBuildElement("K"), 1);
    KOH->AddElement(nist->FindOrBuildElement("O"), 1);
    KOH->AddElement(nist->FindOrBuildElement("H"), 1);

    G4Material *K2CO3 = new G4Material("K2CO3", density, 3);
    K2CO3->AddElement(nist->FindOrBuildElement("K"), 2);
    K2CO3->AddElement(nist->FindOrBuildElement("C"), 1);
    K2CO3->AddElement(nist->FindOrBuildElement("O"), 3);

    G4Material *sampleMaterial = new G4Material("KOH_sample", density, 2);
    sampleMaterial->AddMaterial(KOH, 99.27 * perCent);
    sampleMaterial->AddMaterial(K2CO3, 0.83 * perCent);

    return sampleMaterial;
}

MaterialHolder & MaterialHolder::getInstance() {
    static MaterialHolder instance;
    return instance;
}

