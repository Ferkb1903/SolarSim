#ifndef MYPHYSICSLIST_HH
#define MYPHYSICSLIST_HH

#include "G4VModularPhysicsList.hh"

/// Una lista de física personalizada para simulaciones de baja energía.
///
/// Hereda de una lista de física estándar (QGSP_BERT) pero reemplaza
/// el paquete de física electromagnética por uno de baja energía (Livermore).
class MyPhysicsList : public G4VModularPhysicsList
{
public:
  MyPhysicsList();
  virtual ~MyPhysicsList();
};

#endif
