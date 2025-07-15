//================================================================
// Archivo: src/Run.cc
//================================================================
#include "Run.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4ios.hh"
#include <iomanip>
#include <numeric>
#include <fstream>
#include <cmath>

Run::Run() : G4Run() {
  // Configuración de la rejilla para el perfil 3D
  G4double skinSizeXY = 50.0 * cm;
  G4double skinSizeZ = 1.0 * cm;
  fNx = 50; fNy = 50; fNz = 100;
  fVoxelSizeX = skinSizeXY / fNx;
  fVoxelSizeY = skinSizeXY / fNy;
  fVoxelSizeZ = skinSizeZ / fNz;
  fDetectorOffsetX = skinSizeXY / 2.0;
  fDetectorOffsetY = skinSizeXY / 2.0;
  fDetectorOffsetZ = skinSizeZ / 2.0;
}

Run::~Run() {}

// --- Métodos para registrar datos ---
void Run::RecordProcess(const G4String& processName) { fProcessCounter[processName]++; }
void Run::RecordSecondary(const G4String& particleName, G4double energy) {
  fSecondaryCounter[particleName]++;
  if (particleName == "e-") {
    fSecondaryElectronSpectrum.push_back(energy);
  }
}
void Run::CountPrimaryInSkin(G4int eventID) { fPrimaryEventsInSkin.insert(eventID); }
void Run::CountSecondaryInSkin(G4int trackID) { fSecondaryTracksInSkin.insert(trackID); }
void Run::RecordEnergyInSkin(G4double energy) { fEnergySpectrumInSkin.push_back(energy); }
void Run::RecordTimeOfFlight(G4double time) { fTimeOfFlightToSkin.push_back(time); }
void Run::RecordSecondaryAngle(G4double angle) { fSecondaryAngularDistribution.push_back(angle); }

void Run::FillEnergyGrid(const G4ThreeVector& position, G4double energy) {
    G4int i = std::floor((position.x() + fDetectorOffsetX) / fVoxelSizeX);
    G4int j = std::floor((position.y() + fDetectorOffsetY) / fVoxelSizeY);
    G4int k = std::floor((position.z() + fDetectorOffsetZ) / fVoxelSizeZ);
    if (i < 0 || i >= fNx || j < 0 || j >= fNy || k < 0 || k >= fNz) return;
    G4int index = i + j*fNx + k*fNx*fNy;
    fEnergyGrid[index] += energy;
}

void Run::SaveEnergyGrid(const G4String& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) { return; }
    G4cout << ">>> Guardando el perfil de dosis 3D en " << filename << "..." << G4endl;
    file << "i,j,k,x_cm,y_cm,z_cm,edep_keV\n";
    for (std::map<G4int, G4double>::const_iterator it = fEnergyGrid.begin(); it != fEnergyGrid.end(); ++it) {
        if (it->second > 0) {
            G4int index = it->first;
            G4int i = index % fNx;
            G4int j = (index / fNx) % fNy;
            G4int k = index / (fNx * fNy);
            G4double x = (i + 0.5) * fVoxelSizeX - fDetectorOffsetX;
            G4double y = (j + 0.5) * fVoxelSizeY - fDetectorOffsetY;
            G4double z = (k + 0.5) * fVoxelSizeZ - fDetectorOffsetZ;
            file << i << "," << j << "," << k << "," << x/cm << "," << y/cm << "," << z/cm << "," << it->second/keV << "\n";
        }
    }
    file.close();
}

void Run::SaveSecondarySpectrum(const G4String& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) { return; }
    G4cout << ">>> Guardando el espectro de electrones secundarios en " << filename << "..." << G4endl;
    file << "Energy_keV\n";
    for (const auto& energy : fSecondaryElectronSpectrum) {
        file << energy / keV << "\n";
    }
    file.close();
}

void Run::Merge(const G4Run* run) {
  const Run* localRun = static_cast<const Run*>(run);
  for (std::map<G4String, G4int>::const_iterator it = localRun->fProcessCounter.begin(); it != localRun->fProcessCounter.end(); ++it) { fProcessCounter[it->first] += it->second; }
  for (std::map<G4String, G4int>::const_iterator it = localRun->fSecondaryCounter.begin(); it != localRun->fSecondaryCounter.end(); ++it) { fSecondaryCounter[it->first] += it->second; }
  fPrimaryEventsInSkin.insert(localRun->fPrimaryEventsInSkin.begin(), localRun->fPrimaryEventsInSkin.end());
  fSecondaryTracksInSkin.insert(localRun->fSecondaryTracksInSkin.begin(), localRun->fSecondaryTracksInSkin.end());
  fEnergySpectrumInSkin.insert(fEnergySpectrumInSkin.end(), localRun->fEnergySpectrumInSkin.begin(), localRun->fEnergySpectrumInSkin.end());
  fTimeOfFlightToSkin.insert(fTimeOfFlightToSkin.end(), localRun->fTimeOfFlightToSkin.begin(), localRun->fTimeOfFlightToSkin.end());
  fSecondaryAngularDistribution.insert(fSecondaryAngularDistribution.end(), localRun->fSecondaryAngularDistribution.begin(), localRun->fSecondaryAngularDistribution.end());
  fSecondaryElectronSpectrum.insert(fSecondaryElectronSpectrum.end(), localRun->fSecondaryElectronSpectrum.begin(), localRun->fSecondaryElectronSpectrum.end());
  for (std::map<G4int, G4double>::const_iterator it = localRun->fEnergyGrid.begin(); it != localRun->fEnergyGrid.end(); ++it) { fEnergyGrid[it->first] += it->second; }
  G4Run::Merge(run); 
} 

void Run::PrintResults() const {
    G4cout << "\n ======================== INFORME DE PROCESOS FÍSICOS ========================" << G4endl;
    for (std::map<G4String, G4int>::const_iterator it = fProcessCounter.begin(); it != fProcessCounter.end(); ++it) { G4cout << "  " << std::setw(30) << std::left << it->first << " | " << it->second << G4endl; }
    G4cout << "\n ======================= PARTÍCULAS SECUNDARIAS CREADAS ======================" << G4endl;
    for (std::map<G4String, G4int>::const_iterator it = fSecondaryCounter.begin(); it != fSecondaryCounter.end(); ++it) { G4cout << "  " << std::setw(30) << std::left << it->first << " | " << it->second << G4endl; }
    G4cout << "\n =========================== ANÁLISIS EN LA PIEL ===========================" << G4endl;
    G4cout << "  Eventos donde una Partícula PRIMARIA tocó la piel: " << fPrimaryEventsInSkin.size() << G4endl;
    G4cout << "  Partículas SECUNDARIAS únicas que tocaron la piel: " << fSecondaryTracksInSkin.size() << G4endl;
    G4cout << "  ----------------------------------------------------------------------" << G4endl;
    G4cout << "  Flujo Total de partículas únicas en la piel: " << fPrimaryEventsInSkin.size() + fSecondaryTracksInSkin.size() << G4endl;
    if (!fEnergySpectrumInSkin.empty()) {
        G4double sum_E = std::accumulate(fEnergySpectrumInSkin.begin(), fEnergySpectrumInSkin.end(), 0.0);
        G4cout << "  Energía Cinética Media de partículas en la piel: " << G4BestUnit(sum_E / fEnergySpectrumInSkin.size(), "Energy") << G4endl;
    }
    if (!fTimeOfFlightToSkin.empty()) {
        G4double sum_T = std::accumulate(fTimeOfFlightToSkin.begin(), fTimeOfFlightToSkin.end(), 0.0);
        G4cout << "  Tiempo de Vuelo Medio hasta la piel: " << G4BestUnit(sum_T / fTimeOfFlightToSkin.size(), "Time") << G4endl;
    }
    if (!fSecondaryAngularDistribution.empty()) {
        G4double sum_A = std::accumulate(fSecondaryAngularDistribution.begin(), fSecondaryAngularDistribution.end(), 0.0);
        G4cout << "  Ángulo de Salida Medio de secundarias: " << sum_A / fSecondaryAngularDistribution.size() << " grados" << G4endl;
    }
    G4cout << " ============================================================================\n" << G4endl;
}