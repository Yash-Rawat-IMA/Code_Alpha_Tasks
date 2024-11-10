#include <iostream>
#include <filesystem>   // For filesystem operations (C++17 required)
#include <fstream>      // For file handling
#include <string>

namespace fs = std::filesystem;

void listDirectoryContents(const fs::path& path) {
    if (fs::exists(path) && fs::is_directory(path)) {
        std::cout << "Contents of " << path << ":\n";
        for (const auto& entry : fs::directory_iterator(path)) {
            std::cout << (fs::is_directory(entry) ? "[DIR] " : "[FILE] ");
            std::cout << entry.path().filename().string() << "\n";
        }
    } else {
        std::cout << "Directory does not exist.\n";
    }
}

void createDirectory(const fs::path& path) {
    if (fs::create_directory(path)) {
        std::cout << "Directory created successfully: " << path << "\n";
    } else {
        std::cout << "Failed to create directory. It may already exist.\n";
    }
}

void copyFile(const fs::path& src, const fs::path& dest) {
    try {
        fs::copy_file(src, dest, fs::copy_options::overwrite_existing);
        std::cout << "File copied successfully from " << src << " to " << dest << "\n";
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error copying file: " << e.what() << "\n";
    }
}

void moveFile(const fs::path& src, const fs::path& dest) {
    try {
        fs::rename(src, dest);
        std::cout << "File moved successfully from " << src << " to " << dest << "\n";
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error moving file: " << e.what() << "\n";
    }
}

int main() {
    std::string command;
    fs::path currentPath = fs::current_path();

    std::cout << "Welcome to the Basic Command-Line File Manager\n";
    std::cout << "Current directory: " << currentPath << "\n\n";

    while (true) {
        std::cout << "Enter a command (list, cd, mkdir, copy, move, exit): ";
        std::cin >> command;

        if (command == "list") {
            listDirectoryContents(currentPath);
        } else if (command == "cd") {
            std::string newDir;
            std::cout << "Enter directory path: ";
            std::cin >> newDir;
            fs::path newPath = currentPath / newDir;
            if (fs::exists(newPath) && fs::is_directory(newPath)) {
                currentPath = newPath;
                std::cout << "Changed directory to " << currentPath << "\n";
            } else {
                std::cout << "Directory does not exist.\n";
            }
        } else if (command == "mkdir") {
            std::string dirName;
            std::cout << "Enter new directory name: ";
            std::cin >> dirName;
            createDirectory(currentPath / dirName);
        } else if (command == "copy") {
            std::string src, dest;
            std::cout << "Enter source file path: ";
            std::cin >> src;
            std::cout << "Enter destination file path: ";
            std::cin >> dest;
            copyFile(currentPath / src, currentPath / dest);
        } else if (command == "move") {
            std::string src, dest;
            std::cout << "Enter source file path: ";
            std::cin >> src;
            std::cout << "Enter destination file path: ";
            std::cin >> dest;
            moveFile(currentPath / src, currentPath / dest);
        } else if (command == "exit") {
            std::cout << "Exiting the file manager.\n";
            break;
        } else {
            std::cout << "Unknown command. Please try again.\n";
        }
    }

    return 0;
}
