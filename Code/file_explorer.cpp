#include <iostream>
#include <dirent.h>   // For directory handling (opendir, readdir, closedir)
#include <sys/stat.h> // For file information and permissions (stat, chmod)
#include <unistd.h>   // For changing directories (chdir)
#include <cstring>    // For string functions (strcmp)
#include <fstream>    // For file input/output streams
#include <string>     // For string class
#include <cstdio>     // For remove and rename functions
#include <cstdlib>    // For general utilities
#include <cerrno>     // For error numbers and perror
#include <limits>     // For numeric limits used in input handling

using namespace std;

// Function to list all files and subdirectories in the given directory path
void listFiles(const string &path)
{
    DIR *dir = opendir(path.c_str()); // Open the directory stream
    if (!dir)

    {
        perror("Unable to open directory"); // Print error if directory cannot be opened
        return;
    }

    cout << "\nContents of: " << path << endl;
    cout << "-------------------------------------" << endl;

    struct dirent *entry;
    // Read each entry in the directory
    while ((entry = readdir(dir)) != nullptr)
    {
        // Skip the special entries "." (current) and ".." (parent)
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        string fullPath = path + "/" + entry->d_name; // Create full path for file/folder
        struct stat fileStat;
        if (stat(fullPath.c_str(), &fileStat) != 0) // Get file status info 
        {
            perror(("Error reading file info: " + fullPath).c_str());
            continue;
        }
        // Check if entry is directory or regular file and print accordingly
        if (S_ISDIR(fileStat.st_mode))
            cout << "[DIR]  ";
        else
            cout << "[FILE] ";
        cout << entry->d_name << endl;
    }
    closedir(dir); // Close directory stream to free resources
}
// Function to change the current directory to the specified path
void changeDirectory(const string &newDir)
{
    // Use chdir system call to change directory
    if (chdir(newDir.c_str()) == 0)
        cout << "Changed into directory: " << newDir << endl;
    else
        perror("Error changing directory"); // Print error if failed
}
// Function to create an empty file with the provided filename
void createFile(const string &filename)
{
    ofstream file(filename); // Open file stream for output (creates file if doesn't exist)
    if (file)
        cout << "File created: " << filename << endl;
    else
        cerr << "Error creating file!" << endl;
}

// Function to delete the specified file
void deleteFile(const string &filename)
{
    // Remove function deletes the file
    if (remove(filename.c_str()) == 0)
        cout << "File deleted: " << filename << endl;
    else
        perror("Error deleting file"); // Print error if deletion fails
}

// Function to rename or move a file from oldName to newName/path
void renameFile(const string &oldName, const string &newName)
{
    // rename function renames or moves the file
    if (rename(oldName.c_str(), newName.c_str()) == 0)
        cout << "File renamed/moved successfully!" << endl;
    else
        perror("Error renaming/moving file");
}

// Function to copy a file from source to destination path
void copyFile(const string &source, const string &destination)
{
    ifstream src(source, ios::binary);       // Open source file in binary mode
    ofstream dest(destination, ios::binary); // Open destination file

    // Check if both files opened successfully
    if (!src || !dest)
    {
        cerr << "Error opening file(s) for copy!" << endl;
        return;
    }

    dest << src.rdbuf(); // Copy all data from source to destination
    cout << "File copied successfully!" << endl;
}

// Function to recursively search for a file by name starting at given directory
void searchFile(const string &dirPath, const string &target)
{
    DIR *dir = opendir(dirPath.c_str());
    if (!dir)
        return; // If cannot open directory, just return

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr)
    {
        // Skip "." and ".." entries to avoid infinite loops
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        string fullPath = dirPath + "/" + entry->d_name;
        struct stat fileStat;
        if (stat(fullPath.c_str(), &fileStat) == -1)
            continue; // Skip if stat fails

        // If entry is a directory, recurse into it
        if (S_ISDIR(fileStat.st_mode))
            searchFile(fullPath, target);
        // If entry is a file and its name matches target, print the path
        else if (target == entry->d_name)
            cout << "Found: " << fullPath << endl;
    }
    closedir(dir);
}

// Function to display current permissions of a file and optionally change them
void managePermissions(const string &filename)
{
    struct stat fileStat;
    if (stat(filename.c_str(), &fileStat) != 0)
    {
        perror("Error retrieving file info");
        return;
    }

    mode_t permissions = fileStat.st_mode & 0777; // Extract permission bits only

    // Show permissions as readable rwx for user, group, others
    cout << "\nCurrent Permissions for " << filename << ": ";
    cout << ((permissions & S_IRUSR) ? "r" : "-")
         << ((permissions & S_IWUSR) ? "w" : "-")
         << ((permissions & S_IXUSR) ? "x" : "-")
         << ((permissions & S_IRGRP) ? "r" : "-")
         << ((permissions & S_IWGRP) ? "w" : "-")
         << ((permissions & S_IXGRP) ? "x" : "-")
         << ((permissions & S_IROTH) ? "r" : "-")
         << ((permissions & S_IWOTH) ? "w" : "-")
         << ((permissions & S_IXOTH) ? "x" : "-") << endl;

    cout << "\nDo you want to change permissions? (y/n): ";
    char choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

    if (choice == 'y' || choice == 'Y')
    {
        string perms;
        cout << "Enter new permissions in octal (e.g., 755): ";
        getline(cin, perms);

        mode_t newPermissions;
        try
        {
            // Convert the octal string input to a number for chmod
            newPermissions = static_cast<mode_t>(stoi(perms, nullptr, 8));
        }
        catch (...)
        {
            cerr << "Invalid permissions format!" << endl;
            return;
        }

        // Change file permissions with chmod system call
        if (chmod(filename.c_str(), newPermissions) == 0)
            cout << "Permissions updated!" << endl;
        else
            perror("Error updating permissions");
    }
}

// Main function that shows menu and accepts user choices to perform file operations
// Main function that shows menu and accepts user choices to perform file operations
int main()
{
    int choice;
    string name, newName;

    while (true)
    {
        // Display menu options to user
        cout << "\n=============================" << endl;
        cout << "      FILE EXPLORER MENU      " << endl;
        cout << "=============================" << endl;
        cout << "1. List Files" << endl;
        cout << "2. Change Directory" << endl;
        cout << "3. Create File" << endl;
        cout << "4. Delete File" << endl;
        cout << "5. Rename/Move File" << endl;
        cout << "6. Copy File" << endl;
        cout << "7. Search File" << endl;
        cout << "8. Manage Permissions" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter choice: ";

        if (!(cin >> choice)) // Check for valid number input
        {
            cin.clear();                                         // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input! Please enter a number (1-9)." << endl;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear newline for next input

        // Execute user choice using switch case
        switch (choice)
        {
        case 1:
            listFiles("."); // List files of current directory
            break;
        case 2:
            cout << "Enter directory path: ";
            getline(cin, name); // Get path from user
            changeDirectory(name);
            break;
        case 3:
            cout << "Enter file name: ";
            getline(cin, name);
            createFile(name);
            break;
        case 4:
            cout << "Enter file name to delete: ";
            getline(cin, name);
            deleteFile(name);
            break;
        case 5:
            cout << "Enter current file name: ";
            getline(cin, name);
            cout << "Enter new file name/path: ";
            getline(cin, newName);
            renameFile(name, newName);
            break;
        case 6:
            cout << "Enter source file: ";
            getline(cin, name);
            cout << "Enter destination file: ";
            getline(cin, newName);
            copyFile(name, newName);
            break;
        case 7:
            cout << "Enter file name to search: ";
            getline(cin, name);
            searchFile(".", name);
            break;
        case 8:
            cout << "Enter file name: ";
            getline(cin, name);
            managePermissions(name);
            break;
        case 9:
            cout << "Exiting File Explorer..." << endl;
            return 0; // Exit the program
        default:
            cout << "Invalid choice! Enter a number between 1–9." << endl;
        }
    }
}
