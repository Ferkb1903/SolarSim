//================================================================
// Archivo: src/SensitiveDetector.cc
//================================================================
#include "SensitiveDetector.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

SensitiveDetector::SensitiveDetector(const G4String& name, const G4String& filename)
    : G4VSensitiveDetector(name), 
      fOutputFilename(filename),
      fIsHeaderWritten(false)
{}

SensitiveDetector::~SensitiveDetector() {}

void SensitiveDetector::Initialize(G4HCofThisEvent*)
{
    // La cabecera se escribe una sola vez al principio del run.
    if (!fIsHeaderWritten) {
        std::ofstream headerFile(fOutputFilename, std::ios_base::trunc); // Borra el archivo si existe
        if (headerFile.is_open()) {
            headerFile << "EventID,Edep_keV\n";
            headerFile.close();
            fIsHeaderWritten = true;
        }
    }
    
    // Abrimos el archivo en modo 'append' para cada evento.
    outFile.open(fOutputFilename, std::ios_base::app);
    if (!outFile.is_open()) {
        G4Exception("SensitiveDetector", "FileOpenError", FatalException, "No se pudo abrir el archivo CSV de hits.");
    }
}

G4bool SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*)
{
    G4double edep = step->GetTotalEnergyDeposit();
    if (edep == 0.) return false;

    G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    outFile << eventID << "," << edep / keV << "\n";

    return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{
    if (outFile.is_open()) {
        outFile.close();
    }
}