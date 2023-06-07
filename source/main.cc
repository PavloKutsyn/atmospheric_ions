#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "QGSP_BERT.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "MySteppingAction.hh"

int main (int argc,char** argv)
{
    // Create and set the random number generation engine
    CLHEP::RanecuEngine * engine = new CLHEP::RanecuEngine();
    G4Random::setTheEngine(engine);

    // Create the run manager
    G4RunManager* theRunManager = new G4RunManager;

    // Set the mandatory initialization classes
    theRunManager->SetUserInitialization(new DetectorConstruction());  // Construct the geometry
    G4VModularPhysicsList* physicsList = new QGSP_BERT;  // Use the QGSP_BERT physics list
    theRunManager->SetUserInitialization(physicsList);  // Set the physics list
    theRunManager->SetUserAction(new PrimaryGeneratorAction(""));  // Set the primary particle generation
    theRunManager->Initialize();  // Initialize the run manager

    RunAction* runAction = new RunAction;  // Create a new run action
    theRunManager->SetUserAction(runAction);  // Set the run action
    EventAction* eventAction = new EventAction();  // Create a new event action
    theRunManager->SetUserAction(eventAction);  // Set the event action

    // Register the stepping action
    MySteppingAction* steppingAction = new MySteppingAction();
    theRunManager->SetUserAction(steppingAction);

    // Create the visualization manager and initialize it
    auto visManager = new G4VisExecutive;
    visManager->Initialize();

    // Get a pointer to the UI manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    if ( argc == 1 ) {  // If no command line arguments, start an interactive session
        G4UIExecutive* ui = new G4UIExecutive(argc, argv);
        UImanager->ApplyCommand("/control/execute vis.mac");  // Execute the vis.mac macro
        ui->SessionStart();  // Start the UI session
        delete ui;
    }
    else {  // If command line arguments are provided, execute a macro
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);  // Execute the macro
    }

    delete visManager;  // Delete the visualization manager
    delete theRunManager;  // Delete the run manager
    return 0;
}
