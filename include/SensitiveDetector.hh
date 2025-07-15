//================================================================
// Archivo: include/SensitiveDetector.hh
//================================================================
#ifndef SENSITIVEDETECTOR_HH
#define SENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4String.hh"
#include <fstream>

class G4Step;
class G4TouchableHistory;
class G4Run;

/// Detector Sensible que ahora escribe cada "hit" a un archivo CSV.
class SensitiveDetector : public G4VSensitiveDetector
{
public:
    SensitiveDetector(const G4String& name, const G4String& filename);
    virtual ~SensitiveDetector();

    virtual void Initialize(G4HCofThisEvent*);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history) override;
    virtual void EndOfEvent(G4HCofThisEvent*);

private:
    std::ofstream outFile;
    G4String fOutputFilename;
    G4bool fIsHeaderWritten;
};

#endif