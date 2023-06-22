
#include "DetectorConstruction.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(),
  fAtmosphereLogical(nullptr)
{ }

DetectorConstruction::~DetectorConstruction()
{ }

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    // Define Materials
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* air = nist->FindOrBuildMaterial("G4_AIR");//("G4_AIR");
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic"); // New material for the world

    // Define volumes
    G4double size = 1*m;  // Size of the box is 1m x 1m x 1m

    // World
    G4Box* worldBox = new G4Box("World", size, size, size);
    G4LogicalVolume* worldLog = new G4LogicalVolume(worldBox, world_mat, "World"); // Use new material
    G4VPhysicalVolume* worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLog, "World", 0, false, 0);

    // Atmosphere cube
    G4double atmosphereSize = size / 2.0; // Change this to suit the size of the atmosphere cube you want
    G4Box* atmosphereBox = new G4Box("Atmosphere", atmosphereSize, atmosphereSize, atmosphereSize);
    fAtmosphereLogical = new G4LogicalVolume(atmosphereBox, air, "Atmosphere");
    new G4PVPlacement(0, G4ThreeVector(), fAtmosphereLogical, "Atmosphere", worldLog, false, 0);

    // Print materials
    G4cout << *(G4Material::GetMaterialTable()) << G4endl;

    return worldPhys;
}
