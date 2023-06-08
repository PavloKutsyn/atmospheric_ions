#include "MySteppingAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include <fstream>

MySteppingAction::MySteppingAction() {}

MySteppingAction::~MySteppingAction() {}

void MySteppingAction::UserSteppingAction(const G4Step* step)
{
  G4Track* track = step->GetTrack();
  G4ParticleDefinition* particle = track->GetDefinition();

  if (particle->GetParticleType() == "nucleus" && particle->GetParticleSubType() == "generic") {
    IonInfo ion;
    ion.name = particle->GetParticleName();
    ion.kineticEnergy = track->GetKineticEnergy();
    ion.position = track->GetPosition();

    createdIons.push_back(ion);
  }
}

void MySteppingAction::PrintCreatedIons()
{
  std::ofstream csvFile;
  csvFile.open("created_ions.csv", std::ios::app);
  if (!csvFile) {
      std::cerr << "Unable to open file\n";
  }

  csvFile <<std::setiosflags(std::ios::fixed)
          << "PavloKutsyn-trye\n"
          << "Ion Name,Kinetic Energy,Position X,Position Y,Position Z\n";

  for (auto& ion : createdIons) {
    csvFile << ion.name << ",";
    csvFile << ion.kineticEnergy / MeV << ",";
    csvFile << ion.position.x() / cm << ",";
    csvFile << ion.position.y() / cm << ",";
    csvFile << ion.position.z() / cm << "\n";
  }

  csvFile.close();
}
