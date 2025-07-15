//================================================================
// Archivo: src/SteppingAction.cc (Lógica de Conteo Corregida)
//================================================================
#include "SteppingAction.hh"
#include "Run.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4VProcess.hh"
#include "G4Track.hh"
#include "G4Event.hh" // Necesario para GetEventID
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"

SteppingAction::SteppingAction() : G4UserSteppingAction() {}
SteppingAction::~SteppingAction() {}

void SteppingAction::UserSteppingAction(const G4Step* step) {
    Run* myRun = static_cast<Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
    if (!myRun) return;

    // Contar procesos físicos
    const G4VProcess* process = step->GetPostStepPoint()->GetProcessDefinedStep();
    if (process) {
        myRun->RecordProcess(process->GetProcessName());
    }

    // Medir variables en la piel
    G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
    if (volume && volume->GetName() == "Skin") {
        G4Track* track = step->GetTrack();
        if (track->GetParentID() == 0) {
            // Si es primaria, contamos el ID del evento para evitar duplicados entre eventos.
            G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
            myRun->CountPrimaryInSkin(eventID);
        } else {
            // Si es secundaria, contamos su ID de track, que es único dentro de un evento.
            myRun->CountSecondaryInSkin(track->GetTrackID());
        }

        // Registramos la energía y el tiempo solo la primera vez que la partícula toca la piel
        if (step->GetPreStepPoint()->GetStepStatus() == fGeomBoundary) {
            myRun->RecordEnergyInSkin(step->GetPreStepPoint()->GetKineticEnergy());
            myRun->RecordTimeOfFlight(step->GetPreStepPoint()->GetGlobalTime());
        }
    }
}