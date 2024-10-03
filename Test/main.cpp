#include "File.h"
#include <iostream>
#include <vector>

void testTextMode() {
    try {
        std::cout << "Testing Text Mode...\n";

        // Writing text data to a file
        {
            std::cout << "Writing text data to file...\n";
            File textFile("example.txt", File::Mode::WRITE);
            textFile.write("Hello, world!\nThis is a text file.\n");
        }

        // Reading text data from the file
        {
            std::cout << "Reading text data from file...\n";
            File textFile("example.txt", File::Mode::READ);
            std::string content = textFile.read();
            std::cout << "Text file content:\n" << content << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Text Mode Error: " << e.what() << std::endl;
    }
}

void testBinaryMode() {
    try {
        std::cout << "Testing Binary Mode...\n";

        // Binary data to write (e.g., a string with null bytes)
        std::vector<char> binaryData = { 'H', 'e', 'l', 'l', 'o', 0x00, 'B', 'i', 'n', 'a', 'r', 'y' };

        // Writing binary data to a file
        {
            std::cout << "Writing binary data to file...\n";
            File binaryFile("example.bin", File::Mode::WRITE, File::FileType::BINARY);
            binaryFile.write(binaryData);
        }

        // Reading binary data from the file
        {
            std::cout << "Reading binary data from file...\n";
            File binaryFile("example.bin", File::Mode::READ, File::FileType::BINARY);
            std::vector<char> readData = binaryFile.readBinary();

            std::cout << "Binary file content: ";
            for (char c : readData) {
                if (c == '\0') {
                    std::cout << "\\0 ";  // To display the null character
                } else {
                    std::cout << c << " ";
                }
            }
            std::cout << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Binary Mode Error: " << e.what() << std::endl;
    }
}

int main() {
    testTextMode();
    testBinaryMode();
    return 0;
}
