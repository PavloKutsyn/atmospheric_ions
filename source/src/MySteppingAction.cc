#include "MySteppingAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include <fstream>
#include <string>

MySteppingAction::MySteppingAction() {}

MySteppingAction::~MySteppingAction() {}

void MySteppingAction::UserSteppingAction(const G4Step* step)
{
  G4Track* track = step->GetTrack();
  G4ParticleDefinition* particle = track->GetDefinition();

  if (track->GetParentID() == 0) {
    WriteGeneratedParticleToFile(track);
  }

  std::cout << "Checking particle: " << particle->GetParticleName() << "\n";

  if (particle->GetParticleType() == "nucleus" && particle->GetParticleSubType() == "generic") {
    std::cout << "Ion detected: " << particle->GetParticleName() << "\n";

    IonInfo ion;
    ion.stepNumber = step->GetTrack()->GetCurrentStepNumber();
    ion.trackID = track->GetTrackID();
    ion.name = particle->GetParticleName();
    ion.kineticEnergy = track->GetKineticEnergy();
    ion.position = track->GetPosition();
    ion.charge = particle->GetPDGCharge();

    WriteIonToFile(ion);
  }
}

void MySteppingAction::WriteIonToFile(const IonInfo& ion)
{
  std::ofstream csvFile;
  csvFile.open("created_ions.csv", std::ios::app);

  if (!csvFile) {
    std::cerr << "Unable to open file\n";
  }
  else {
    if (!ionHeaderWritten) {
      csvFile << "Step Number,Track ID,Name,Charge,Kinetic Energy (keV),Position X (mm),Position Y (mm),Position Z (mm)\n";
      ionHeaderWritten = true;
    }

    csvFile << ion.stepNumber << ","
            << ion.trackID << ","
            << ion.name << ","
            << ion.charge << ","
            << ion.kineticEnergy/keV << ","
            << ion.position.x() << ","
            << ion.position.y() << ","
            << ion.position.z() << "\n";
  }

  csvFile.close();
}

void MySteppingAction::WriteGeneratedParticleToFile(const G4Track* track)
{
  std::ofstream csvFile;
  csvFile.open("generated_particles.csv", std::ios::app);

  if (!csvFile) {
    std::cerr << "Unable to open file\n";
  }
  else {
    if (!genParticleHeaderWritten) {
      csvFile << "Step Number,Track ID,Name,Kinetic Energy (keV),Position X (mm),Position Y (mm),Position Z (mm)\n";
      genParticleHeaderWritten = true;
    }
    G4ParticleDefinition* particle = track->GetDefinition();

    csvFile << track->GetCurrentStepNumber() << ","
            << track->GetTrackID() << ","
            << particle->GetParticleName() << ","
            << track->GetKineticEnergy()/keV << ","
            << track->GetPosition().x() << ","
            << track->GetPosition().y() << ","
            << track->GetPosition().z() << "\n";
  }

  csvFile.close();
}
