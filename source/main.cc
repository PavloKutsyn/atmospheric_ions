#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "QGSP_BERT.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"


int main (int argc,char** argv)
{
    // Setting randomizer
    CLHEP::RanecuEngine * engine = new CLHEP::RanecuEngine();
    G4Random::setTheEngine(engine);

    // Create the run manager
    G4RunManager* theRunManager = new G4RunManager;

    // Set the mandatory initialization classes
    theRunManager->SetUserInitialization(new DetectorConstruction());
    G4VModularPhysicsList* physicsList = new QGSP_BERT;
    theRunManager->SetUserInitialization(physicsList);
    theRunManager->SetUserAction(new PrimaryGeneratorAction(""));
    theRunManager->Initialize();

    RunAction* runAction = new RunAction;
    theRunManager->SetUserAction(runAction);
    EventAction* eventAction = new EventAction();
    theRunManager->SetUserAction(eventAction);

    // Start the visualization driver
    auto visManager = new G4VisExecutive;
    visManager->Initialize();

    // Process macro or start UI session
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    if ( argc == 1 ) {
        G4UIExecutive* ui = new G4UIExecutive(argc, argv);
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
        delete ui;
    }
    else {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);
    }

    delete visManager;
    delete theRunManager;
    return 0;
}
