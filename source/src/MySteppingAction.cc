#include "MySteppingAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include <fstream>
#include <string>

MySteppingAction::MySteppingAction(CsvWriter* ionWriter, CsvWriter* particleWriter)
    : ionWriter(ionWriter), particleWriter(particleWriter) {}

MySteppingAction::~MySteppingAction() {}

void MySteppingAction::UserSteppingAction(const G4Step* step)
{
  G4Track* track = step->GetTrack();
  G4ParticleDefinition* particle = track->GetDefinition();

  if (track->GetParentID() == 0) {
    particleWriter->WriteRow(track->GetTrackID(),
      particle->GetParticleName(),
      track->GetKineticEnergy(),
      track->GetPosition());
  }

  if (particle->GetParticleType() == "nucleus" && particle->GetParticleSubType() == "generic") {
    IonInfo ion;
    ion.trackID = track->GetTrackID();
    ion.name = particle->GetParticleName();
    ion.kineticEnergy = track->GetKineticEnergy();
    ion.position = track->GetPosition();

    ionWriter->WriteRow(ion.trackID,
      ion.name,
      ion.kineticEnergy,
      ion.position);
  }
}
