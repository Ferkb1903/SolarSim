//================================================================
// Archivo: src/DetectorConstruction.cc (Actualizado)
//================================================================
#include "DetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4UserLimits.hh"
#include "SensitiveDetector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

DetectorConstruction::DetectorConstruction(G4bool withUmbrella, G4String filename)
 : G4VUserDetectorConstruction(),
   fWithUmbrella(withUmbrella),
   fOutputFilename(filename)
{}

DetectorConstruction::~DetectorConstruction() {}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4NistManager* nist = G4NistManager::Instance();
    auto air = nist->FindOrBuildMaterial("G4_AIR");
    auto skin = nist->FindOrBuildMaterial("G4_SKIN_ICRP");
    auto umbrellaMaterial = nist->FindOrBuildMaterial("G4_POLYETHYLENE");

    G4double worldSize = 2.0 * m;
    G4double umbrellaSize = 50.0 * cm;
    G4double umbrellaThickness = 1.0 * cm;
    G4double skinSize = 50.0 * cm;
    G4double skinThickness = 20.0 * cm;

    G4Box* solidWorld = new G4Box("World", worldSize/2, worldSize/2, worldSize/2);
    auto logicWorld = new G4LogicalVolume(solidWorld, air, "World");

    if (fWithUmbrella) {
        G4cout << ">>> Construyendo la sombrilla." << G4endl;
        G4Box* solidUmbrella = new G4Box("Umbrella", umbrellaSize/2, umbrellaSize/2, umbrellaThickness/2);
        auto logicUmbrella = new G4LogicalVolume(solidUmbrella, umbrellaMaterial, "Umbrella");
        G4ThreeVector posUmbrella(0, 0, 50.*cm);
        new G4PVPlacement(0, posUmbrella, logicUmbrella, "UmbrellaPhys", logicWorld, false, 0, true);

        // --- ¡CAMBIO CLAVE! ---
        // Hacemos que la sombrilla también sea un detector sensible.
        // Creamos una nueva instancia de SensitiveDetector para ella.
        G4cout << ">>> Registrando detector sensible para la sombrilla..." << G4endl;
        auto umbrellaSD = new SensitiveDetector("UmbrellaSD", "umbrella_hits.csv");
        G4SDManager::GetSDMpointer()->AddNewDetector(umbrellaSD);
        logicUmbrella->SetSensitiveDetector(umbrellaSD);
    }

    G4Box* solidSkin = new G4Box("Skin", skinSize/2, skinSize/2, skinThickness/2);
    auto logicSkin = new G4LogicalVolume(solidSkin, skin, "Skin");
    logicSkin->SetUserLimits(new G4UserLimits(1.*mm));
    G4ThreeVector posSkin(0, 0, -skinThickness/2.0);
    new G4PVPlacement(0, posSkin, logicSkin, "SkinPhys", logicWorld, false, 0, true);

    // Asignamos un detector sensible a la piel, usando el nombre de archivo que nos pasaron.
    auto skinSD = new SensitiveDetector("SkinSD", fOutputFilename);
    G4SDManager::GetSDMpointer()->AddNewDetector(skinSD);
    logicSkin->SetSensitiveDetector(skinSD);

    return new G4PVPlacement(0, G4ThreeVector(), logicWorld, "WorldPhys", 0, false, 0, true);
}
