//================================================================
// Archivo: include/TrackingAction.hh
//================================================================
#ifndef TRACKINGACTION_HH
#define TRACKINGACTION_HH

#include "G4UserTrackingAction.hh"
#include "globals.hh"

class G4Track;

class TrackingAction : public G4UserTrackingAction
{
  public:
    TrackingAction();
    virtual ~TrackingAction();

    virtual void PreUserTrackingAction(const G4Track* aTrack);
};

#endif
