//================================================================
// Archivo: include/Run.hh
//================================================================
#ifndef RUN_HH
#define RUN_HH

#include "G4Run.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include <map>
#include <set>
#include <vector>

class G4Track;

/// Clase Run personalizada para un análisis físico completo.
class Run : public G4Run
{
  public:
    Run();
    virtual ~Run();

    // Métodos para registrar datos
    void RecordProcess(const G4String& processName);
    void RecordSecondary(const G4String& particleName, G4double energy);
    void CountPrimaryInSkin(G4int eventID);
    void CountSecondaryInSkin(G4int trackID);
    void RecordEnergyInSkin(G4double energy);
    void RecordTimeOfFlight(G4double time);
    void RecordSecondaryAngle(G4double angle);
    void FillEnergyGrid(const G4ThreeVector& position, G4double energy);

    virtual void Merge(const G4Run*);
    void PrintResults() const;
    void SaveEnergyGrid(const G4String& filename) const;
    void SaveSecondarySpectrum(const G4String& filename) const;

  private:
    // Contadores para el informe de texto
    std::map<G4String, G4int> fProcessCounter;
    std::map<G4String, G4int> fSecondaryCounter;
    std::set<G4int> fPrimaryEventsInSkin; 
    std::set<G4int> fSecondaryTracksInSkin;
    std::vector<G4double> fEnergySpectrumInSkin;
    std::vector<G4double> fTimeOfFlightToSkin;
    std::vector<G4double> fSecondaryAngularDistribution;
    std::vector<G4double> fSecondaryElectronSpectrum;

    // Voxelización para el mapa de calor 3D
    G4int fNx, fNy, fNz;
    G4double fVoxelSizeX, fVoxelSizeY, fVoxelSizeZ;
    G4double fDetectorOffsetX, fDetectorOffsetY, fDetectorOffsetZ;
    std::map<G4int, G4double> fEnergyGrid;
};

#endif