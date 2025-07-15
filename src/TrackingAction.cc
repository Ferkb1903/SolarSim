//================================================================
// Archivo: src/TrackingAction.cc
//================================================================
#include "TrackingAction.hh"
#include "Run.hh"
#include "G4Track.hh"
#include "G4RunManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

TrackingAction::TrackingAction() : G4UserTrackingAction() {}
TrackingAction::~TrackingAction() {}

void TrackingAction::PreUserTrackingAction(const G4Track* aTrack) {
    if (aTrack->GetParentID() > 0) {
        Run* myRun = static_cast<Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
        if (myRun) {
            myRun->RecordSecondary(aTrack->GetDefinition()->GetParticleName(), aTrack->GetKineticEnergy());
            G4double theta = aTrack->GetMomentumDirection().theta();
            myRun->RecordSecondaryAngle(theta / deg);
        }
    }
}