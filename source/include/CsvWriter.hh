#ifndef CsvWriter_hh
#define CsvWriter_hh

#include "G4ThreeVector.hh"
#include <fstream>
#include <string>

class CsvWriter {
public:
    CsvWriter(const std::string& filename);
    ~CsvWriter();

    void WriteHeader();
    void WriteRow(int trackID, const std::string& name, double kineticEnergy, const G4ThreeVector& position);
    void Close();

private:
    std::ofstream csvFile;
    bool headerWritten = false;
};

#endif
