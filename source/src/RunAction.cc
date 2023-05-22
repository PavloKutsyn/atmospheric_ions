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
/*У цьому файлі ми скидаємо загальну іонізацію до нуля
 *   на початку кожного прогона, а потім друкуємо
 *   загальну іонізацію в кінці кожного прогона.

Примітка: Наразі ми не оновлюємо fTotalIonization під час прогона.
Ви будете потребуватися додатковий клас, як SteppingAction,
для відстеження кроків частинок та оновлення загальної іонізації.
*/
