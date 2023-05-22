#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
#include "CRYSetup.h"
#include "CRYGenerator.h"
#include "CRYParticle.h"
#include "CRYUtils.h"
#include "vector"
#include "RNGWrapper.hh"
#include "G4ThreeVector.hh"
#include "G4DataVector.hh"
#include "G4ParticleTable.hh"
#include "Randomize.hh"
#include "PrimaryGeneratorMessenger.hh"

class G4GeneralParticleSource;
class G4Event;
class DetectorConstruction;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction(const char * filename);
    ~PrimaryGeneratorAction();

  public:
    virtual void GeneratePrimaries(G4Event* anEvent);
    void InputCRY();                                 // CRY method for activating input commands feature
    void UpdateCRY(std::string* MessInput);


  private:

    DetectorConstruction* fDetector;
    std::vector<CRYParticle*> *vect;
    G4ParticleTable* particleTable;
    G4ParticleGun* particleGun;
    CRYGenerator* gen;
    G4int InputState;
    PrimaryGeneratorMessenger* gunMessenger;

};

#endif
