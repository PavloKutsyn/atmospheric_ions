#ifndef MySteppingAction_hh
#define MySteppingAction_hh

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "G4String.hh"

struct IonInfo {
  G4String name;
  G4double kineticEnergy;
  G4ThreeVector position;
};

class MySteppingAction : public G4UserSteppingAction
{
public:
  MySteppingAction();
  ~MySteppingAction();

  void UserSteppingAction(const G4Step* step) override;
  void PrintCreatedIons();

private:
  std::vector<IonInfo> createdIons;
};

#endif
