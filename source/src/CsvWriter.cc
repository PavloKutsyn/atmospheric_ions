#include "CsvWriter.hh"
#include "G4SystemOfUnits.hh"
#include <stdexcept>

CsvWriter::CsvWriter(const std::string& filename)
{
    csvFile.open(filename, std::ios::app);
    if (!csvFile) {
        throw std::runtime_error("Unable to open file: " + filename);
    }
}

CsvWriter::~CsvWriter()
{
    Close();
}

void CsvWriter::WriteHeader()
{
    if (!headerWritten) {
        csvFile << "Track ID,Name,Kinetic Energy (keV),Position X (mm),Position Y (mm),Position Z (mm)\n";
        headerWritten = true;
    }
}

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

void CsvWriter::Close()
{
    if (csvFile.is_open()) {
        csvFile.close();
    }
}
