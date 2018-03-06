
#include "ObjectHolder.h"
#include <G4SystemOfUnits.hh>
#include <G4PhysicalConstants.hh>
#include <G4Box.hh>
#include <G4Tubs.hh>
#include <G4Trd.hh>
#include <G4SubtractionSolid.hh>
#include <G4VisAttributes.hh>
#include <G4NistManager.hh>
#include <Utils.h>
#include <MaterialHolder.h>
#include "GeantGeometry.h"

struct SamplePosition {
    double x = 555.0 * mm;
    double y = 0.0 * mm;
};

struct SensorPosition {
    double x = (500 - 232.5/sqrt(2.0)) * mm ;
    double y = - 232.5/sqrt(2.0) * mm;
};

struct LeadPosition {
    double x = (500 - 413/sqrt(2)) * mm;
    double y = - 180 / sqrt(2) * mm;
};

struct SampleSize {
    double l = 110 * mm;
    double w = 110 * mm;
    double h = 110 * mm;
};

struct SensorSize {
    double w = 65 * mm;
    double r = 38 * mm;
};

struct LeadSize {
    double l = 200 * mm;
    double w = 150 * mm;
    double h = 150 * mm;
};

struct TrapezoidSize {
    double z = 500 * mm;
    double startA = 0 * mm;
    double finishA = z * tan(9.22 / 2 * pi / 180) * mm;
};

G4PVPlacement *ObjectHolder::installationPlacement() {
    auto sensorPosition = new SensorPosition;
    auto leadPosition = new LeadPosition;
    auto samplePosition = new SamplePosition;

    G4double size = 50000 * m;
    G4Box *installation = new G4Box("installation", size/2., size/2., size/2.);

    G4NistManager *nist = G4NistManager::Instance();
    G4Material *env_mat = nist->FindOrBuildMaterial("G4_Galactic");
    G4LogicalVolume *installationLogicalVolume = new G4LogicalVolume(installation, env_mat, "Installation");
    installationLogicalVolume->SetVisAttributes(G4VisAttributes::Invisible);

    new G4PVPlacement(0,G4ThreeVector(samplePosition->x, samplePosition->y, 0),sampleLog(),"PVsampleLog",installationLogicalVolume,false,0);
    new G4PVPlacement(Utils::rotate(135, 90, 90),G4ThreeVector(sensorPosition->x, sensorPosition->y, 0),sensorLog(),"PVsampleLog",installationLogicalVolume,false,0);
    new G4PVPlacement(Utils::rotate(0, 0, 45),G4ThreeVector(leadPosition->x, leadPosition->y, 0),leadLog(),"PVsampleLog",installationLogicalVolume,false,0);
    return new G4PVPlacement(0, G4ThreeVector(), installationLogicalVolume, "Installation", 0, false, 0);
}

G4LogicalVolume *ObjectHolder::sensorLog() {
    G4NistManager *nist = G4NistManager::Instance();
    auto *sensorSize = new SensorSize;
    G4Tubs *sensorTube = new G4Tubs("sensor_tube", 0, sensorSize->r, sensorSize->w / 2., 0, 2. * pi);
    G4Material *sensorMaterial = nist->FindOrBuildMaterial("G4_BGO");
    G4LogicalVolume *sensorLogicalVolume = new G4LogicalVolume(sensorTube, sensorMaterial, "sensor_log");
    sensorLogicalVolume->SetVisAttributes(G4Colour::Blue());
    return sensorLogicalVolume;
}

G4LogicalVolume *ObjectHolder::leadLog() {
    auto leadPosition = new LeadPosition;
    G4NistManager *nist = G4NistManager::Instance();
    auto *leadSize = new LeadSize;
    auto *trapezoidSize = new TrapezoidSize;
    G4Box *leadBox = new G4Box("leadBox", leadSize->l/2., leadSize->w/2., leadSize->h/2.);
    G4Trd *trapezoid = new G4Trd("trapezoid", trapezoidSize->startA, trapezoidSize->finishA, trapezoidSize->startA, trapezoidSize->finishA, trapezoidSize->z);
    G4SubtractionSolid *subtractionSolid = new G4SubtractionSolid("defence_sub", leadBox, trapezoid, Utils::rotate(45, 90, 0), G4ThreeVector(0, -leadPosition->y + trapezoidSize->finishA / 2, 0));
    G4Material *leadMaterial = nist->FindOrBuildMaterial("G4_Pb");
    G4LogicalVolume *leadLogicalVolume = new G4LogicalVolume(subtractionSolid, leadMaterial, "lead_box");
    leadLogicalVolume->SetVisAttributes(G4Colour::Red());
    return leadLogicalVolume;
}

G4LogicalVolume *ObjectHolder::sampleLog() {
    auto materialHolder = MaterialHolder();
    auto *sampleSize = new SampleSize;
    G4Box *sampleBox = new G4Box("object", sampleSize->l/2, sampleSize->w/2, sampleSize->h/2);

    // =====================================================================

    G4Material *sampleMaterial = materialHolder.sampleMaterial1(); //TODO: Different materials here

    // =====================================================================

    G4LogicalVolume *sampleLogicalVolume = new G4LogicalVolume(sampleBox, sampleMaterial, "object_log");
    sampleLogicalVolume->SetVisAttributes(G4Colour::Cyan());
    return sampleLogicalVolume;
}

G4LogicalVolume *ObjectHolder::tableLog() {
    return nullptr;
}

G4LogicalVolume *ObjectHolder::planeLog() {
    return nullptr;
}

G4LogicalVolume *ObjectHolder::safeLog() {
    return nullptr;
}

G4LogicalVolume *ObjectHolder::shelfLog() {
    return nullptr;
}

G4LogicalVolume *ObjectHolder::wallsLog() {
    return nullptr;
}

G4LogicalVolume *ObjectHolder::windowLog() {
    return nullptr;
}

G4LogicalVolume *ObjectHolder::bataryLog() {
    return nullptr;
}

G4LogicalVolume *ObjectHolder::doorLog() {
    return nullptr;
}

G4LogicalVolume *ObjectHolder::floorAndCellingLog() {
    return nullptr;
}

