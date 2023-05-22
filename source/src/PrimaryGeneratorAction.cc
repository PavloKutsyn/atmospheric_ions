#include "PrimaryGeneratorAction.hh"

#include "DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4ios.hh"
#include <iomanip>
#include <random>

using namespace std;

PrimaryGeneratorAction::PrimaryGeneratorAction(const char *inputfile)
:G4VUserPrimaryGeneratorAction()
{
    // define a particle gun
    particleGun = new G4ParticleGun();


    // Read the cry input file
    std::ifstream inputFile;
    inputFile.open(inputfile,std::ios::in);
    char buffer[1000];

    if (inputFile.fail()) {
      if( *inputfile !=0)
        G4cout << "PrimaryGeneratorAction: Failed to open CRY input file= " << inputfile << G4endl;
      InputState=-1;
    }else{
      std::string setupString("");
      while ( !inputFile.getline(buffer,1000).eof()) {
        setupString.append(buffer);
        setupString.append(" ");
      }

      CRYSetup *setup=new CRYSetup(setupString,"../data");

      gen = new CRYGenerator(setup);

      RNGWrapper<CLHEP::HepRandomEngine>::set(CLHEP::HepRandom::getTheEngine(),&CLHEP::HepRandomEngine::flat);
      setup->setRandomFunction(RNGWrapper<CLHEP::HepRandomEngine>::rng);
      InputState=0;
    }


    // create a vector to store the CRY particle properties
    vect=new std::vector<CRYParticle*>;

    // Create the table containing all particle names
    particleTable = G4ParticleTable::GetParticleTable();


    gunMessenger = new PrimaryGeneratorMessenger(this);
}
void PrimaryGeneratorAction::InputCRY()
{
  InputState=1;
}

void PrimaryGeneratorAction::UpdateCRY(std::string* MessInput)
{
  CRYSetup *setup=new CRYSetup(*MessInput,"../data");
  gen = new CRYGenerator(setup);
  // set random number generator

  RNGWrapper<CLHEP::HepRandomEngine>::set(CLHEP::HepRandom::getTheEngine(),&CLHEP::HepRandomEngine::flat);
  setup->setRandomFunction(RNGWrapper<CLHEP::HepRandomEngine>::rng);
  InputState=0;
}


PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
}

//void ALARAPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  if (InputState != 0) {
    G4String* str = new G4String("CRY library was not successfully initialized");

    G4Exception("PrimaryGeneratorAction", "1",
                RunMustBeAborted, *str);
  }
  G4String particleName;
  vect->clear();
  gen->genEvent(vect);

  for ( unsigned j=0; j<vect->size(); j++) {
    particleName=CRYUtils::partName((*vect)[j]->id());

    cout << "  "          << particleName << " "
         << "charge="      << (*vect)[j]->charge() << " "

      << endl;

    particleGun->SetParticleDefinition(particleTable->FindParticle((*vect)[j]->PDGid()));
    particleGun->SetParticleEnergy((*vect)[j]->ke()*MeV);
    particleGun->SetParticlePosition(G4ThreeVector((*vect)[j]->x()*m, (*vect)[j]->y()*m, 50*cm)); //(*vect)[j]->z()*m));
    particleGun->SetParticleMomentumDirection(G4ThreeVector((*vect)[j]->u(), (*vect)[j]->v(), (*vect)[j]->w()));
    particleGun->SetParticleTime((*vect)[j]->t());
    particleGun->GeneratePrimaryVertex(anEvent);
    delete (*vect)[j];
  }
}


//void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
//{
//    if (InputState != 0) {
//      G4String* str = new G4String("CRY library was not successfully initialized");

//      G4Exception("PrimaryGeneratorAction", "1",
//                  RunMustBeAborted, *str);
//    }
//    G4String particleName;
//    vect->clear();
//    gen->genEvent(vect);

//    for ( unsigned j=0; j<vect->size(); j++) {
//      particleName=CRYUtils::partName((*vect)[j]->id());

//      // applying CRY source values to partical generator
//      particleGun->SetParticleDefinition(particleTable->FindParticle((*vect)[j]->PDGid()));       // particle type
//      particleGun->SetParticleEnergy(1.5*GeV);                                       // particle energy
//      particleGun->SetParticlePosition(G4ThreeVector((*vect)[j]->x()*m, (*vect)[j]->y()*m, (*vect)[j]->z()*m)); // particle initial points 100*cm
//      particleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, -1)); // particle initial momentums
//      particleGun->SetParticleTime((*vect)[j]->t()); // particle time
//      particleGun->GeneratePrimaryVertex(anEvent); //method of primary generator to make primaries
//      delete (*vect)[j];
//    }

//}
