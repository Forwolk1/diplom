#include <G4LogicalVolume.hh>
#include <G4SystemOfUnits.hh>
#include <G4PhysicalConstants.hh>
#include <G4Box.hh>
#include <G4PVPlacement.hh>
#include <G4Tubs.hh>
#include <G4Trd.hh>
#include <G4SubtractionSolid.hh>
#include <G4VisAttributes.hh>
#include <G4NistManager.hh>
#include "GeantGeometry.h"

struct SourcePosition {
    double x = 0.0 * mm;
    double y = 0.0 * mm;
};

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

//SiO2 1900
G4Material * sampleMaterial1 () {
    G4NistManager *nist = G4NistManager::Instance();
    double density = 1900 * kg / m3;
    G4Material *Si2O3 = new G4Material("Si2O3", density, 2);
    Si2O3->AddElement(nist->FindOrBuildElement("Si"), 1);
    Si2O3->AddElement(nist->FindOrBuildElement("O"), 2);

    return Si2O3;
}

G4RotationMatrix *rotateX (double phi) {
    phi *= deg;
    G4ThreeVector u = G4ThreeVector(1, 0, 0);
    G4ThreeVector v = G4ThreeVector(0, std::cos(phi), -std::sin(phi));
    G4ThreeVector w = G4ThreeVector(0, std::sin(phi), cos(phi));
    return new G4RotationMatrix(u, v, w);
}

G4RotationMatrix *rotateY (double phi) {
    phi *= deg;
    G4ThreeVector u = G4ThreeVector(std::cos(phi), 0, std::sin(phi));
    G4ThreeVector v = G4ThreeVector(0, 1, 0);
    G4ThreeVector w = G4ThreeVector(-std::sin(phi), 0, std::cos(phi));
    return new G4RotationMatrix(u, v, w);
}

G4RotationMatrix *rotateZ (double phi) {
    phi *= deg;
    G4ThreeVector u = G4ThreeVector(std::cos(phi), -std::sin(phi), 0);
    G4ThreeVector v = G4ThreeVector(std::sin(phi), std::cos(phi),0.);
    G4ThreeVector w = G4ThreeVector(0, 0, 1.);
    return new G4RotationMatrix(u, v, w);
}

G4RotationMatrix *rotate (double axisX, double axisY, double axisZ) {
    axisX *= deg;
    axisY *= deg;
    axisZ *= deg;
    return new G4RotationMatrix(axisX, axisY, axisZ);
}

G4VPhysicalVolume *GeantGeometry::Construct() {
    auto leadPosition = new LeadPosition;
    auto samplePosition = new SamplePosition;
    auto sensorPosition = new SensorPosition;

    G4double size = 50000 * m;
    G4Box *world = new G4Box("world", size/2., size/2., size/2.);

    G4NistManager *nist = G4NistManager::Instance();
    G4Material *world_mat = nist->FindOrBuildMaterial("G4_Galactic");
    G4LogicalVolume *worldLogicalVolume = new G4LogicalVolume(world, world_mat, "World");
    worldLogicalVolume->SetVisAttributes(G4VisAttributes::Invisible);

    auto *sampleSize = new SampleSize;
    G4Box *sampleBox = new G4Box("object", sampleSize->l/2, sampleSize->w/2, sampleSize->h/2);

    // =====================================================================

    G4Material *sampleMaterial = sampleMaterial1(); //TODO: Different materials here

    // =====================================================================

    G4LogicalVolume *sampleLogicalVolume = new G4LogicalVolume(sampleBox, sampleMaterial, "object_log");
    sampleLogicalVolume->SetVisAttributes(G4Colour::Cyan());
    new G4PVPlacement(0,G4ThreeVector(samplePosition->x, samplePosition->y, 0),sampleLogicalVolume,"PVsampleLog",worldLogicalVolume,false,0);

    auto *sensorSize = new SensorSize;
    G4Tubs *sensorTube = new G4Tubs("sensor_tube", 0, sensorSize->r, sensorSize->w / 2., 0, 2. * pi);
    G4Material *sensorMaterial = nist->FindOrBuildMaterial("G4_BGO");
    G4LogicalVolume *sensorLogicalVolume = new G4LogicalVolume(sensorTube, sensorMaterial, "sensor_log");
    sensorLogicalVolume->SetVisAttributes(G4Colour::Blue());
    new G4PVPlacement(rotate(135, 90, 90),G4ThreeVector(sensorPosition->x, sensorPosition->y, 0),sensorLogicalVolume,"PVsampleLog",worldLogicalVolume,false,0);

    auto *leadSize = new LeadSize;
    auto *trapezoidSize = new TrapezoidSize;
    G4Box *leadBox = new G4Box("leadBox", leadSize->l/2., leadSize->w/2., leadSize->h/2.);
    G4Trd *trapezoid = new G4Trd("trapezoid", trapezoidSize->startA, trapezoidSize->finishA, trapezoidSize->startA, trapezoidSize->finishA, trapezoidSize->z);
    G4SubtractionSolid *subtractionSolid = new G4SubtractionSolid("defence_sub", leadBox, trapezoid, rotate(45, 90, 0), G4ThreeVector(0, -leadPosition->y + trapezoidSize->finishA / 2, 0));
    G4Material *leadMaterial = nist->FindOrBuildMaterial("G4_Pb");
    G4LogicalVolume *leadLogicalVolume = new G4LogicalVolume(subtractionSolid, leadMaterial, "lead_box");
    leadLogicalVolume->SetVisAttributes(G4Colour::Red());

    new G4PVPlacement(rotate(0, 0, 45),G4ThreeVector(leadPosition->x, leadPosition->y, 0),leadLogicalVolume,"PVsampleLog",worldLogicalVolume,false,0);
    return new G4PVPlacement(0, G4ThreeVector(), worldLogicalVolume, "World", 0, false, 0);
}
