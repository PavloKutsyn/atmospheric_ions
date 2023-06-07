#include "MySteppingAction.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4IonTable.hh"

MySteppingAction::MySteppingAction() : G4UserSteppingAction() {}

MySteppingAction::~MySteppingAction() {}

void MySteppingAction::UserSteppingAction(const G4Step* step) {
    G4Track* track = step->GetTrack();
    G4ParticleDefinition* particle = track->GetDefinition();
    G4String particleName = particle->GetParticleName();

    // Check if the particle is an ion
    if(particle->GetParticleType() == "nucleus") {
        G4cout << "Ion created: " << particleName
               << ", kinetic energy: " << track->GetKineticEnergy() << G4endl;
    }
}
