#ifndef PRIMARYGENERATORACTION_HH
#define PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

/// Generador Primario que usa G4ParticleGun.
///
/// Esta es una versión simplificada para depuración, similar
/// a la que se usa en el ejemplo B1.
class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();
    virtual ~PrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event* anEvent);

  private:
    G4ParticleGun* fParticleGun;
};

#endif
