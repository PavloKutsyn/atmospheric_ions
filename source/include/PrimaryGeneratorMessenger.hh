#ifndef PrimaryGeneratorMessenger_h
#define PrimaryGeneratorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class PrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithoutParameter;

// Class for setting macro command for CRY generator values
class PrimaryGeneratorMessenger: public G4UImessenger
{
  public:
    PrimaryGeneratorMessenger(PrimaryGeneratorAction*);
   ~PrimaryGeneratorMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    PrimaryGeneratorAction*      Action; //an indicator of the action of the primary generator, which controls the actual generation of particles.
    G4UIdirectory*               CRYDir; //a pointer to the directory where the commands for the CRY generator are located.
    G4UIcmdWithAString*          FileCmd; //the command to enter the name of the file with CRY settings.
    G4UIcmdWithAString*          InputCmd; //a command to enter CRY parameters directly through the command line.
    G4UIcmdWithoutParameter*     UpdateCmd; //command to update CRY parameters.
    std::string* MessInput;                 //a pointer to a row that stores the entered parameters until they are updated.
};


#endif

