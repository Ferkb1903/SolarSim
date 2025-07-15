#include "MyPhysicsList.hh"

#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronPhysicsQGSP_BERT.hh"
#include "G4StoppingPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4NeutronTrackingCut.hh"

// --- ¡CAMBIO CLAVE! ---
// Usaremos la "Opción 3" para la física electromagnética.
// Es otra configuración estándar y validada para baja energía.
#include "G4EmStandardPhysics_option3.hh"

MyPhysicsList::MyPhysicsList()
: G4VModularPhysicsList()
{
  // Física de Decaimientos
  RegisterPhysics(new G4DecayPhysics());

  // Física de Decaimientos Radiactivos
  RegisterPhysics(new G4RadioactiveDecayPhysics());

  // --- ¡LA CLAVE! Física Electromagnética de Baja Energía (Opción 3) ---
  RegisterPhysics(new G4EmStandardPhysics_option3());

  // Física Hadrónica (la misma que en QGSP_BERT)
  RegisterPhysics(new G4HadronElasticPhysics());
  RegisterPhysics(new G4HadronPhysicsQGSP_BERT());
  RegisterPhysics(new G4StoppingPhysics());
  RegisterPhysics(new G4IonPhysics());
  RegisterPhysics(new G4NeutronTrackingCut());
}

MyPhysicsList::~MyPhysicsList()
{}
