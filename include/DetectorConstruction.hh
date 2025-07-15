#ifndef DETECTOR_CONSTRUCTION_HH
#define DETECTOR_CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "globals.hh"
#include "G4String.hh"

class DetectorConstruction : public G4VUserDetectorConstruction {
public:
    DetectorConstruction(G4bool withUmbrella = true, G4String filename = "energy_deposit.csv");
    virtual ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct() override;

private:
    G4bool fWithUmbrella;
    G4String fOutputFilename;
    G4LogicalVolume* fLogicWorld;
};

#endif
