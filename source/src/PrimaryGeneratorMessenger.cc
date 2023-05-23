#include "PrimaryGeneratorMessenger.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"

PrimaryGeneratorMessenger::PrimaryGeneratorMessenger(PrimaryGeneratorAction* Gun)
  :Action(Gun)
{
    /*creates a new G4UIdirectory object named "/CRY/".
     * All commands created later will be in this directory.*/
  CRYDir = new G4UIdirectory("/CRY/");
  CRYDir->SetGuidance("CRY initialization");

   /*creates a new command that takes a string as an argument.
    * This command is associated with the CRY settings file.*/
  FileCmd = new G4UIcmdWithAString("/CRY/file",this);
  FileCmd->SetGuidance("This reads the CRY definition from a file");
  FileCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
   
  /*creates a new command that also takes a string as an argument.
   * This command is related to entering CRY parameters.*/
  InputCmd = new G4UIcmdWithAString("/CRY/input",this);
  InputCmd->SetGuidance("CRY input lines");
  InputCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  /*creates a new command that takes no arguments.
   * This command is used to update CRY settings.*/
  UpdateCmd = new G4UIcmdWithoutParameter("/CRY/update",this);
  UpdateCmd->SetGuidance("Update CRY definition.");
  UpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  UpdateCmd->SetGuidance("if you changed the CRY definition.");
  UpdateCmd->AvailableForStates(G4State_Idle);

  /*creates a new std::string.*/
  MessInput = new std::string;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorMessenger::~PrimaryGeneratorMessenger()
{
  delete CRYDir;
  delete InputCmd;
  delete UpdateCmd;
  delete FileCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorMessenger::SetNewValue(
                                        G4UIcommand* command, G4String newValue)
{ 
  if( command == InputCmd )
   {
     Action->InputCRY();
     (*MessInput).append(newValue);
     (*MessInput).append(" ");
   }

  if( command == UpdateCmd )
   { 
     Action->UpdateCRY(MessInput); 
     *MessInput = "";
   }


}

/*The PrimaryGeneratorMessenger destructor frees the memory
 * allocated for all those objects that were created via new.

The SetNewValue method is called when the user executes one of
the commands defined in the constructor. It checks which command
was executed and calls the appropriate methods in PrimaryGeneratorAction.

if( command == InputCmd ) - if the input command is executed,
it passes the input data to the action of the primary generator
and stores the entered string.
if( command == UpdateCmd ) - If the update command is executed,
 it passes the collected input to the primary generator action
to update the CRY parameters and clears the input string.*/
