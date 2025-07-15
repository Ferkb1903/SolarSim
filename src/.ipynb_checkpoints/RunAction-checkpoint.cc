//================================================================
// Archivo: src/RunAction.cc
//================================================================
#include "RunAction.hh"
#include "Run.hh"
#include "G4Run.hh"
#include "G4ios.hh"

RunAction::RunAction() : G4UserRunAction() {}
RunAction::~RunAction() {}

G4Run* RunAction::GenerateRun() { return new Run; }

void RunAction::BeginOfRunAction(const G4Run* aRun) { 
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
}

void RunAction::EndOfRunAction(const G4Run* aRun) {
  const Run* myRun = static_cast<const Run*>(aRun);
  if (myRun) {
      myRun->PrintResults();
      myRun->SaveEnergyGrid("perfil_dosis_3d.csv");
      myRun->SaveSecondarySpectrum("secondary_electron_spectrum.csv");
  }
  G4cout << "### Run " << aRun->GetRunID() << " end." << G4endl;
}