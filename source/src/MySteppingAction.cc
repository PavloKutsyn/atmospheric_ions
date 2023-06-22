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

// Constructor
MySteppingAction::MySteppingAction() {}

// Destructor
MySteppingAction::~MySteppingAction() {}

// Function called at each simulation step
void MySteppingAction::UserSteppingAction(const G4Step* step)
{
  // Obtain track and particle definition from the step
  G4Track* track = step->GetTrack();
  G4ParticleDefinition* particle = track->GetDefinition();

  // If the track is a primary particle, write it to the generated particles file
  if (track->GetParentID() == 0) {
    WriteGeneratedParticleToFile(track);
  }

  // Print the particle name
  std::cout << "Checking particle: " << particle->GetParticleName() << "\n";

  // If the particle is an ion, print a message and record its details
  if (particle->GetParticleType() == "nucleus" && particle->GetParticleSubType() == "generic") {
    std::cout << "Ion detected: " << particle->GetParticleName() << "\n";

    IonInfo ion;  // Create ion structure to hold ion details
    ion.trackID = track->GetTrackID();
    ion.name = particle->GetParticleName();
    ion.kineticEnergy = track->GetKineticEnergy();
    ion.position = track->GetPosition();

    // Write the ion data to file immediately
    WriteIonToFile(ion);
  }
}

// Function to write ion information to a file
void MySteppingAction::WriteIonToFile(const IonInfo& ion)
{
  std::ofstream csvFile;  // Create file output stream
  csvFile.open("created_ions.csv", std::ios::app);  // Open the file in append mode

  if (!csvFile) {  // If unable to open file, print error message
    std::cerr << "Unable to open file\n";
  }
  else {
    if (!headerWritten) {  // If the header hasn't been written yet, write it
      csvFile << "Track ID,Name,Kinetic Energy (keV),Position X (mm),Position Y (mm),Position Z (mm)\n";
      headerWritten = true;  // Remember that the header has been written
    }
    // Write ion details to file
    csvFile << ion.trackID << ","
            << ion.name << ","
            << ion.kineticEnergy/keV << ","
            << ion.position.x() << ","
            << ion.position.y() << ","
            << ion.position.z() << "\n";
  }

  csvFile.close();  // Close the file
}

// Function to write generated particle information to a file
void MySteppingAction::WriteGeneratedParticleToFile(const G4Track* track)
{
  std::ofstream csvFile;  // Create file output stream
  csvFile.open("generated_particles.csv", std::ios::app);  // Open the file in append mode

  if (!csvFile) {  // If unable to open file, print error message
    std::cerr << "Unable to open file\n";
  }
  else {
    if (!headerWritten) {  // If the header hasn't been written yet, write it
      csvFile << "Track ID,Name,Kinetic Energy (keV),Position X (mm),Position Y (mm),Position Z (mm)\n";
      headerWritten = true;  // Remember that the header has been written
    }
    // Write particle details to file
    G4ParticleDefinition* particle = track->GetDefinition();
    csvFile << track->GetTrackID() << ","
            << particle->GetParticleName() << ","
            << track->GetKineticEnergy()/keV << ","
            << track->GetPosition().x() << ","
            << track->GetPosition().y() << ","
            << track->GetPosition().z() << "\n";
  }

  csvFile.close();  // Close the file
}
