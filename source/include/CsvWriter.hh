#ifndef CsvWriter_hh
#define CsvWriter_hh

#include "G4ThreeVector.hh"
#include <fstream>
#include <string>

// The CsvWriter class is designed for writing data of particle
// simulations into CSV format. It provides functionality to create a file,
// write a header, write a row of data for each particle, and close the file.
class CsvWriter {
public:
    // Constructor: opens the file with the given filename in append mode.
    CsvWriter(const std::string& filename);

    // Destructor: ensures that the file is closed.
    ~CsvWriter();

    // Writes the header line to the CSV file. This function will only write
    // the header once even if it is called multiple times.
    void WriteHeader();

    // Writes a row of particle data to the CSV file. It writes the trackID,
    // particle name, kinetic energy, and position (x, y, z).
    void WriteRow(int trackID, const std::string& name, double kineticEnergy, const G4ThreeVector& position);

    // Closes the CSV file. It's safe to call this function even if the file
    // is already closed.
    void Close();

private:
    std::ofstream csvFile;  // The CSV file stream.
    bool headerWritten = false;  // Flag to ensure the header is only written once.
};

#endif
