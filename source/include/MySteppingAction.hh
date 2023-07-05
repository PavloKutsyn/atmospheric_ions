#ifndef MySteppingAction_hh
#define MySteppingAction_hh

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "G4String.hh"
#include "G4Track.hh"

struct IonInfo {
  G4int stepNumber;
  G4int trackID;
  G4String name;
  G4double kineticEnergy;
  G4ThreeVector position;
  G4double charge;
};

class MySteppingAction : public G4UserSteppingAction
{
public:
  MySteppingAction();
  ~MySteppingAction();

  void UserSteppingAction(const G4Step* step) override;
  void WriteIonToFile(const IonInfo& ion);
//  void WriteGeneratedParticleToFile(const G4Step* step);
  void WriteGeneratedParticleToFile(const G4Track* track);

private:
//  void WriteHeaderToFile();
//  bool headerWritten = false;
  bool ionHeaderWritten = false;
  bool genParticleHeaderWritten = false;
};

#endif
