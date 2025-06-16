#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>

#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#define mkdir(path, mode) _mkdir(path)
#define PATH_SEP "\\"
#else
#define PATH_SEP "/"
#endif

#define GITHUB_REPO "https://github.com/chocoOnEstrogen/lgbt.git"
#define TMP_DIR "tmp" PATH_SEP "lgbt"
#define BINARY_PATH TMP_DIR PATH_SEP "bin" PATH_SEP "lgbt"
#define MAN_PAGE_PATH TMP_DIR PATH_SEP "resources" PATH_SEP "lgbt.1"

#ifdef _WIN32
#define DEFAULT_INSTALL_PATH "C:\\Program Files\\lgbt"
#define DEFAULT_MAN_PATH "C:\\Program Files\\lgbt\\man"
#elif defined(__APPLE__)
#define DEFAULT_INSTALL_PATH "/usr/local/bin"
#define DEFAULT_MAN_PATH "/usr/local/share/man/man1"
#else
#define DEFAULT_INSTALL_PATH "/usr/bin"
#define DEFAULT_MAN_PATH "/usr/share/man/man1"
#endif

// Global variables for cleanup
char installed_binary[512] = "";
char installed_man_page[512] = "";
int tmp_dir_created = 0;

void print_help(const char *program_name) {
    printf("LGBT Flag Display Tool Installer\n");
    printf("===============================\n\n");
    printf("Usage: %s [OPTIONS]\n\n", program_name);
    printf("Options:\n");
    printf("  --help                 Show this help message\n");
    printf("  --path=PATH           Set the binary installation path (default: %s)\n", DEFAULT_INSTALL_PATH);
    printf("  --man-path=PATH       Set the man page installation path (default: %s)\n", DEFAULT_MAN_PATH);
    printf("  --prefix=PATH         Set the installation prefix\n");
    printf("\nExamples:\n");
    printf("  %s --path=%s\n", program_name, DEFAULT_INSTALL_PATH);
    printf("  %s --man-path=%s\n", program_name, DEFAULT_MAN_PATH);
    printf("\nNote: The installer requires administrator privileges to install files.\n");
}

void cleanup(void) {
    // Remove installed files if they exist
    if (installed_binary[0] != '\0') {
        char cmd[1024];
#ifdef _WIN32
        snprintf(cmd, sizeof(cmd), "del /F /Q \"%s\"", installed_binary);
#else
        snprintf(cmd, sizeof(cmd), "sudo rm -f \"%s\"", installed_binary);
#endif
        if (system(cmd) != 0) {
            fprintf(stderr, "Warning: Failed to remove binary file\n");
        }
    }
    if (installed_man_page[0] != '\0') {
        char cmd[1024];
#ifdef _WIN32
        snprintf(cmd, sizeof(cmd), "del /F /Q \"%s\"", installed_man_page);
#else
        snprintf(cmd, sizeof(cmd), "sudo rm -f \"%s\"", installed_man_page);
#endif
        if (system(cmd) != 0) {
            fprintf(stderr, "Warning: Failed to remove man page\n");
        }
    }
    // Remove temporary directory if it was created
    if (tmp_dir_created) {
        char cmd[1024];
#ifdef _WIN32
        snprintf(cmd, sizeof(cmd), "rmdir /S /Q \"%s\"", TMP_DIR);
#else
        snprintf(cmd, sizeof(cmd), "rm -rf \"%s\"", TMP_DIR);
#endif
        if (system(cmd) != 0) {
            fprintf(stderr, "Warning: Failed to remove temporary directory\n");
        }
    }
}

void signal_handler(int signum __attribute__((unused))) {
    printf("\n\nInstallation interrupted. Cleaning up...\n");
    cleanup();
    exit(1);
}

void print_error(const char *message) {
    fprintf(stderr, "Error: %s\n", message);
    cleanup();
    exit(1);
}

int check_command_exists(const char *command) {
    char path[256];
#ifdef _WIN32
    snprintf(path, sizeof(path), "where %s >nul 2>&1", command);
#else
    snprintf(path, sizeof(path), "which %s >/dev/null 2>&1", command);
#endif
    return system(path) == 0;
}

void execute_command(const char *command) {
    if (system(command) != 0) {
        char error[512];
        snprintf(error, sizeof(error), "Failed to execute: %s", command);
        print_error(error);
    }
}

void create_directory(const char *path) {
    if (mkdir(path, 0755) != 0 && errno != EEXIST) {
        char error[512];
        snprintf(error, sizeof(error), "Failed to create directory: %s", path);
        print_error(error);
    }
    tmp_dir_created = 1;
}

int main(int argc, char *argv[]) {
    // Set up signal handlers for cleanup
#ifndef _WIN32
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
#endif
    atexit(cleanup);

    char install_path[256] = DEFAULT_INSTALL_PATH;
    char man_path[256] = DEFAULT_MAN_PATH;
    
    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            print_help(argv[0]);
            return 0;
        } else if (strncmp(argv[i], "--path=", 7) == 0) {
            strncpy(install_path, argv[i] + 7, sizeof(install_path) - 1);
        } else if (strncmp(argv[i], "--man-path=", 11) == 0) {
            strncpy(man_path, argv[i] + 11, sizeof(man_path) - 1);
        }
    }

    printf("LGBT Flag Display Tool Installer\n");
    printf("===============================\n\n");

    // Check if git is installed
    printf("Checking for git... ");
    if (!check_command_exists("git")) {
        print_error("git is not installed. Please install git first.");
    }
    printf("Found!\n");

    // Create temporary directory
    printf("Creating temporary directory... ");
    create_directory(TMP_DIR);
    printf("Done!\n");

    // Clone repository
    printf("Cloning repository... ");
    char clone_cmd[512];
    snprintf(clone_cmd, sizeof(clone_cmd), "git clone %s %s", GITHUB_REPO, TMP_DIR);
    execute_command(clone_cmd);
    printf("Done!\n");

    // Change to repository directory
    if (chdir(TMP_DIR) != 0) {
        print_error("Failed to change to repository directory");
    }

    // Run make install
    printf("Building and installing... ");
    execute_command("make install");
    printf("Done!\n");

    // Copy binary
    printf("Installing binary... ");
    char copy_binary_cmd[512];
#ifdef _WIN32
    snprintf(copy_binary_cmd, sizeof(copy_binary_cmd), 
             "xcopy /Y \"%s\" \"%s\\\"", BINARY_PATH, install_path);
#else
    snprintf(copy_binary_cmd, sizeof(copy_binary_cmd), 
             "sudo cp \"%s\" \"%s/\"", BINARY_PATH, install_path);
#endif
    execute_command(copy_binary_cmd);
    snprintf(installed_binary, sizeof(installed_binary), "%s" PATH_SEP "lgbt", install_path);
    printf("Done!\n");

    // Copy man page
    printf("Installing man page... ");
    char copy_man_cmd[512];
#ifdef _WIN32
    snprintf(copy_man_cmd, sizeof(copy_man_cmd), 
             "xcopy /Y \"%s\" \"%s\\\"", MAN_PAGE_PATH, man_path);
#else
    snprintf(copy_man_cmd, sizeof(copy_man_cmd), 
             "sudo cp \"%s\" \"%s/\"", MAN_PAGE_PATH, man_path);
#endif
    execute_command(copy_man_cmd);
    snprintf(installed_man_page, sizeof(installed_man_page), "%s" PATH_SEP "lgbt.1", man_path);
    printf("Done!\n");

    // Clean up temporary files
    printf("Cleaning up temporary files... ");
    char cleanup_cmd[512];
#ifdef _WIN32
    snprintf(cleanup_cmd, sizeof(cleanup_cmd), "rmdir /S /Q \"%s\"", TMP_DIR);
#else
    snprintf(cleanup_cmd, sizeof(cleanup_cmd), "rm -rf \"%s\"", TMP_DIR);
#endif
    execute_command(cleanup_cmd);
    tmp_dir_created = 0;
    printf("Done!\n");

    printf("\nInstallation completed successfully!\n");
    printf("The lgbt command is now available at: %s" PATH_SEP "lgbt\n", install_path);
    printf("The man page is available at: %s" PATH_SEP "lgbt.1\n", man_path);

    return 0;
}
