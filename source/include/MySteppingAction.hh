/*In general, the MySteppingAction class is a custom class
 * derived from G4UserSteppingAction. It's used to customize
 * the actions to be performed at each step of the simulation.
 * It includes functionality to write ion and generated
 * particle information to a file. It includes a struct
 * IonInfo to store ion information like track ID, name,
 * kinetic energy, and position.*/

#ifndef MySteppingAction_hh                       // Preprocessor directives to prevent multiple inclusions of header file
#define MySteppingAction_hh

#include "G4UserSteppingAction.hh"               // Base class that provides the stepping action interface
#include "G4Step.hh"                             // Class representing a single step of a particle
#include "G4String.hh"                           // Geant4 string class
#include "G4Track.hh"                            // Class representing the track of a particle

struct IonInfo {                                  // Structure to store relevant information about ions
  G4int trackID;                                  // Track ID of the ion
  G4String name;                                  // Name of the ion
  G4double kineticEnergy;                         // Kinetic energy of the ion
  G4ThreeVector position;                         // Position of the ion
};

class MySteppingAction : public G4UserSteppingAction  // Class that provides user customization for each simulation step
{
public:
  MySteppingAction();                              // Constructor
  ~MySteppingAction();                             // Destructor

  void UserSteppingAction(const G4Step* step) override;  // Function to override for custom actions at each simulation step
  void WriteIonToFile(const IonInfo& ion);         // Function to write ion information to a file
  void WriteGeneratedParticleToFile(const G4Track* track);  // Function to write generated particle information to a file

private:
  void WriteHeaderToFile();                        // Function to write the header to a file
  bool headerWritten = false;                      // Flag to check if the header has been written
};

#endif
