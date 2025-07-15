#include "EventAction.hh"
#include "G4Event.hh"
#include "G4ios.hh"

EventAction::EventAction()
: G4UserEventAction()
{}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event* anEvent)
{
  // Imprime un mensaje cada 1000 eventos para saber que la simulación avanza
  G4int eventID = anEvent->GetEventID();
  if ( eventID % 1000 == 0 ) {
    G4cout << "--> Begin of event: " << eventID << G4endl;
  }
}

// Dejamos EndOfEventAction vacío. El coloreado se maneja en vis.mac.
void EventAction::EndOfEventAction(const G4Event*)
{}
