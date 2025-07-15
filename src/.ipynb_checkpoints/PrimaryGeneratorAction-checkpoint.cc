#include "PrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh" // Necesario para G4UniformRand()

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0) 
{
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);

  // Definir la partícula
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle("gamma");
  fParticleGun->SetParticleDefinition(particle);

  // --- ¡CAMBIO CLAVE! ---
  // Definir la energía dirección.
  fParticleGun->SetParticleEnergy(1000*keV);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,-1.));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // Genera una posición aleatoria en un disco de 25 cm de radio.
  G4double radius = 25.0 * cm;
  G4double r = radius * std::sqrt(G4UniformRand());
  G4double theta = 2.0 * CLHEP::pi * G4UniformRand();
  
  G4double x0 = r * std::cos(theta);
  G4double y0 = r * std::sin(theta);
  // Colocamos la fuente a 60 cm de altura, delante de la sombrilla.
  G4double z0 = 60 * cm;
  
  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));

  // Crea el vértice primario
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
