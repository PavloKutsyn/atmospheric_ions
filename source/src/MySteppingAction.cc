/*The MySteppingAction class implements the actions to take
 *  at each simulation step. It's main function
 *  UserSteppingAction() checks each particle at every step.
 *  If the particle is a primary particle, it writes its
 *  details to a file. If the particle is an ion, it also
 *  writes its details to a separate file. This information
 *  is written to CSV files, with one row per ion or primary
 *  particle.*/

#include "MySteppingAction.hh"
#include "G4SystemOfUnits.hh"                  // Geant4 units
#include "G4Step.hh"                           // Class representing a single step of a particle
#include "G4Track.hh"                          // Class representing the track of a particle
#include "G4ParticleDefinition.hh"             // Class defining a particle
#include <fstream>                             // Standard C++ library for file input/output
#include <string>                              // Standard C++ library string

// Constructor takes two pointers to CsvWriter - for ions and particles
MySteppingAction::MySteppingAction(CsvWriter* ionWriter, CsvWriter* particleWriter)
    : ionWriter(ionWriter), particleWriter(particleWriter) {}

// Destructor
MySteppingAction::~MySteppingAction() {}

// Function called at each simulation step
void MySteppingAction::UserSteppingAction(const G4Step* step)
{
  // Get the track and particle definition from the step
  G4Track* track = step->GetTrack();
  G4ParticleDefinition* particle = track->GetDefinition();

  // If the track is a primary particle, write it to the generated particles file
  if (track->GetParentID() == 0) {
    particleWriter->WriteRow(track->GetTrackID(),
      particle->GetParticleName(),
      track->GetKineticEnergy(),
      track->GetPosition());
  }

  // If the particle is an ion, record its details in an IonInfo structure and write it to file
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
