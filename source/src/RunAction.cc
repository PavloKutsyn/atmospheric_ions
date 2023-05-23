#include "RunAction.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

RunAction::RunAction() : G4UserRunAction(),
                         fTotalIonization(0.)
{}

RunAction::~RunAction()
{}

void RunAction::BeginOfRunAction(const G4Run*)
{
    // Reset total ionization
    fTotalIonization = 0.;
}

void RunAction::EndOfRunAction(const G4Run*)
{
    // Print total ionization
    G4cout << "Total Ionization: "
           << G4BestUnit(fTotalIonization, "Energy")
           << G4endl;
}

/*In this file we reset the total ionization to zero
  * at the beginning of each run, and then print
  * total ionization at the end of each run.

Note: do not update fTotalIonization during runtime.
You need an additional class like SteppingAction,
to track particle steps and update total ionization.

This RunAction class tracks and prints the total ionization energy.
At the start of each run, it resets fTotalIonization to zero.
At the end of each run, it prints fTotalIonization in
the most appropriate energy units.

This current implementation only sets and prints fTotalIonization,
but doesn't update it during the run. Typically,
the updating could be done in SteppingAction based on the energy
deposits in each step, or in EventAction based on the total energy
deposits in each event, and you'll need to provide a public method
in RunAction to add to fTotalIonization.
*/
