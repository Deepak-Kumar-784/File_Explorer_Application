#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <limits>

using namespace std;

// Lists all files and directories inside the given path
void listFiles(const string &path)
{
    DIR *dir = opendir(path.c_str()); // Open directory stream
    if (!dir)
    {
        perror("Unable to open directory"); // Error if cannot open
        return;
    }

    cout << "\nContents of: " << path << endl;
    cout << "-------------------------------------" << endl;

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr) // Read all directory entries
    {
        // Skip current and parent directory entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        string fullPath = path + "/" + entry->d_name;
        struct stat fileStat;
        if (stat(fullPath.c_str(), &fileStat) != 0) // Get file info
        {
            perror(("Error reading file info: " + fullPath).c_str());
            continue;
        }

        // Print [DIR] or [FILE] before name
        if (S_ISDIR(fileStat.st_mode))
            cout << "[DIR]  ";
        else
            cout << "[FILE] ";

        cout << entry->d_name << endl;
    }
    closedir(dir); // Close directory stream
}

// Changes current working directory to given path
void changeDirectory(const string &newDir)
{
    if (chdir(newDir.c_str()) == 0)
        cout << "Changed into directory: " << newDir << endl;
    else
        perror("Error changing directory");
}

// Creates a new empty file with given name
void createFile(const string &filename)
{
    ofstream file(filename); // Create file stream
    if (file)
        cout << "File created: " << filename << endl;
    else
        cerr << "Error creating file!" << endl;
}

// Deletes the specified file
void deleteFile(const string &filename)
{
    if (remove(filename.c_str()) == 0)
        cout << "File deleted: " << filename << endl;
    else
        perror("Error deleting file");
}

// Renames or moves a file from oldName to newName
void renameFile(const string &oldName, const string &newName)
{
    if (rename(oldName.c_str(), newName.c_str()) == 0)
        cout << "File renamed/moved successfully!" << endl;
    else
        perror("Error renaming/moving file");
}

// Copies a file from source to destination
void copyFile(const string &source, const string &destination)
{
    ifstream src(source, ios::binary);
    ofstream dest(destination, ios::binary);

    if (!src || !dest)
    {
        cerr << "Error opening file(s) for copy!" << endl;
        return;
    }

    dest << src.rdbuf(); // Copy data
    cout << "File copied successfully!" << endl;
}

// Recursively searches for file named target starting from dirPath
void searchFile(const string &dirPath, const string &target)
{
    DIR *dir = opendir(dirPath.c_str());
    if (!dir)
        return;

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr)
    {
        // Skip current and parent directories
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        string fullPath = dirPath + "/" + entry->d_name;
        struct stat fileStat;
        if (stat(fullPath.c_str(), &fileStat) == -1)
            continue;

        // If directory, recurse; if file matches target, print path
        if (S_ISDIR(fileStat.st_mode))
            searchFile(fullPath, target);
        else if (target == entry->d_name)
            cout << "Found: " << fullPath << endl;
    }
    closedir(dir);
}

// Shows current permissions of a file and optionally allows changing them
void managePermissions(const string &filename)
{
    struct stat fileStat;
    if (stat(filename.c_str(), &fileStat) != 0)
    {
        perror("Error retrieving file info");
        return;
    }

    mode_t permissions = fileStat.st_mode & 0777; // Extract permission bits

    // Print permissions as rwx for user, group, others
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clean input buffer

    if (choice == 'y' || choice == 'Y')
    {
        string perms;
        cout << "Enter new permissions in octal (e.g., 755): ";
        getline(cin, perms);

        mode_t newPermissions;
        try
        {
            newPermissions = static_cast<mode_t>(stoi(perms, nullptr, 8)); // Convert octal string to number
        }
        catch (...)
        {
            cerr << "Invalid permissions format!" << endl;
            return;
        }

        // Change file permissions
        if (chmod(filename.c_str(), newPermissions) == 0)
            cout << "Permissions updated!" << endl;
        else
            perror("Error updating permissions");
    }
}

int main()
{
    int choice;
    string name, newName;

    while (true)
    {
        // Display menu options
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

        if (!(cin >> choice)) // Validate numeric input
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number (1-9)." << endl;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear newline

        switch (choice)
        {
        case 1:
            listFiles(".");
            break;
        case 2:
            cout << "Enter directory path: ";
            getline(cin, name);
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
            return 0;
        default:
            cout << "Invalid choice! Enter a number between 1–9." << endl;
        }
    }
}
