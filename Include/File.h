#pragma once

/*
Class: File
Author: Rounak Paul (paulrounak1999@gmail.com)

A File handle class written in modern C++
*/

#include <fstream>
#include <memory>
#include <string>
#include <stdexcept>
#include <vector>

class File {
public:
    enum class Mode { READ, WRITE, APPEND };
    enum class FileType { TEXT, BINARY };

    File(const std::string& path, Mode mode, FileType fileType = FileType::TEXT) {
        openFile(path, mode, fileType);
    }

    ~File() {
        close();
    }

    // Delete copy constructor and assignment operator to avoid copying file handles
    File(const File&) = delete;
    File& operator=(const File&) = delete;

    // Move constructor and assignment operator
    File(File&& other) noexcept : fileStream(std::move(other.fileStream)) {}

    File& operator=(File&& other) noexcept {
        if (this != &other) {
            close();
            fileStream = std::move(other.fileStream);
        }
        return *this;
    }

    // Write a string to the file (for text files)
    void write(const std::string& data) {
        if (!fileStream || !fileStream->good()) {
            throw std::runtime_error("File not open for writing");
        }
        *fileStream << data;
    }

    // Write binary data to the file
    void write(const std::vector<char>& data) {
        if (!fileStream || !fileStream->good()) {
            throw std::runtime_error("File not open for binary writing");
        }
        fileStream->write(data.data(), data.size());
    }

    // Read the entire file contents into a string (for text files)
    std::string read() {
        if (!fileStream || !fileStream->good()) {
            throw std::runtime_error("File not open for reading");
        }
        std::string content((std::istreambuf_iterator<char>(*fileStream)),
                            std::istreambuf_iterator<char>());
        return content;
    }

    // Read binary data from the file into a vector
    std::vector<char> readBinary() {
        if (!fileStream || !fileStream->good()) {
            throw std::runtime_error("File not open for binary reading");
        }

        // Seek to the end to get the file size
        fileStream->seekg(0, std::ios::end);
        std::streamsize size = fileStream->tellg();
        fileStream->seekg(0, std::ios::beg);

        // Read the file into a vector
        std::vector<char> buffer(size);
        fileStream->read(buffer.data(), size);
        return buffer;
    }

    // Check if the file is open
    bool isOpen() const {
        return fileStream && fileStream->is_open();
    }

    // Close the file
    void close() {
        if (fileStream && fileStream->is_open()) {
            fileStream->close();
        }
    }

private:
    std::unique_ptr<std::fstream> fileStream;

    // Helper function to open file based on the mode and type
    void openFile(const std::string& path, Mode mode, FileType fileType) {
        std::ios_base::openmode openMode;
        switch (mode) {
            case Mode::READ:
                openMode = std::ios::in;
                break;
            case Mode::WRITE:
                openMode = std::ios::out | std::ios::trunc;
                break;
            case Mode::APPEND:
                openMode = std::ios::out | std::ios::app;
                break;
        }

        if (fileType == FileType::BINARY) {
            openMode |= std::ios::binary;
        }

        fileStream = std::make_unique<std::fstream>(path, openMode);
        if (!fileStream->is_open()) {
            throw std::runtime_error("Failed to open file: " + path);
        }
    }
};
