// CsvWriter.cc

#include "CsvWriter.hh"
#include "G4SystemOfUnits.hh"
#include <stdexcept>

// Constructor: Opens the file with the given filename in append mode.
CsvWriter::CsvWriter(const std::string& filename)
{
    csvFile.open(filename, std::ios::app);
    if (!csvFile) {
        throw std::runtime_error("Unable to open file: " + filename);
    }
}

// Destructor: Ensures that the file is closed.
CsvWriter::~CsvWriter()
{
    Close();
}

// Writes the header line to the CSV file. This function will only write
// the header once even if it is called multiple times.
void CsvWriter::WriteHeader()
{
    if (!headerWritten) {
        csvFile << "Track ID,Name,Kinetic Energy (keV),Position X (mm),Position Y (mm),Position Z (mm)\n";
        headerWritten = true;
    }
}

// Writes a row of particle data to the CSV file. It writes the trackID,
// particle name, kinetic energy, and position (x, y, z).
void CsvWriter::WriteRow(int trackID, const std::string& name, double kineticEnergy, const G4ThreeVector& position)
{
    if (!csvFile) {
        throw std::runtime_error("Unable to write to file.");
    }
    else {
        csvFile << trackID << ","
                << name << ","
                << kineticEnergy/keV << ","
                << position.x() << ","
                << position.y() << ","
                << position.z() << "\n";
    }
}

// Closes the CSV file. It's safe to call this function even if the file
// is already closed.
void CsvWriter::Close()
{
    if (csvFile.is_open()) {
        csvFile.close();
    }
}
