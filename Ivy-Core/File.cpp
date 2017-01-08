#include "File.h"

std::string File::Read(std::string filePath) {
    // Uses the C API for reading files.
    // MSVC wants use to use the secure alternative.
#ifdef _MSC_VER
    fopen_s(&m_pFile, filePath.c_str(), "rb");
#else
    file = fopen(filename.c_str(), "rb");
#endif

    if (!m_pFile)
        return std::string();

    // Get the size of the file so we can preallocate 
    // the correct amount for the vector.
    long pos = ftell(m_pFile);
    fseek(m_pFile, 0, SEEK_END);
    long size = ftell(m_pFile);
    fseek(m_pFile, pos, SEEK_SET);

    std::vector<char>buffer(size + 1);
    fread(buffer.data(), size, 1, m_pFile);
    buffer[size] = '\0';
    fclose(m_pFile);

    // Return string after assignment.
    return std::string(buffer.begin(), buffer.end());
}
