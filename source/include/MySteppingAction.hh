#ifndef MySteppingAction_hh
#define MySteppingAction_hh

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "G4String.hh"
#include "G4Track.hh"
#include "CsvWriter.hh"

struct IonInfo {
  G4int trackID;
  G4String name;
  G4double kineticEnergy;
  G4ThreeVector position;
};

class MySteppingAction : public G4UserSteppingAction
{
public:
  MySteppingAction(CsvWriter* ionWriter, CsvWriter* particleWriter);
  ~MySteppingAction();

  void UserSteppingAction(const G4Step* step) override;

private:
  CsvWriter* ionWriter;
  CsvWriter* particleWriter;
};

#endif
