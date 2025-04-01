// Copyright Citra Emulator Project / Lime3DS Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include <stdio.h>
#include <string.h>
#ifdef WIN32
#include <process.h>
#include <stdlib.h>
#include <windows.h>
#else
#include <unistd.h>
#endif

int main(int argc, char* argv[]) {
    char exe_file[12] = "/azahar";
    char exe_path[FILENAME_MAX];

    // Get the directory which contains the currently running executable
#ifdef WIN32
    GetModuleFileNameA(NULL, exe_path, FILENAME_MAX);
    char* last_slash = strrchr(exe_path, '\\');
    strcat(exe_file, ".exe");
#else
    ssize_t result = readlink("/proc/self/exe", exe_path, FILENAME_MAX);
    if (result == -1) {
        printf("Failed to start: Couldn't read /proc/self/exe");
    }
    char* last_slash = strrchr(exe_path, '/');
#endif
    if (last_slash != NULL) {
        last_slash[0] = '\0';
    }

    // Append the Azahar executable filename to the current executable's directory
    strcat(exe_path, exe_file);

    // Construct ARGV to be used in execv
    char room_option[] = "--room";
#ifdef _MSC_VER
    char* new_argv[100];
#else
    char* new_argv[argc + 2];
#endif
    new_argv[0] = exe_path;
    new_argv[1] = room_option;
    new_argv[argc + 1] = NULL;
    for (int i = 1; i < argc; i++) {
        new_argv[i + 1] = argv[i];
    }

    // Attempt to replace current process with the main Azahar executable
#ifdef WIN32
    intptr_t spawnv_result = _spawnv(_P_WAIT, exe_path, new_argv);
    if (spawnv_result == -1) {
        perror("Failed to start main Azahar executable");
    }
    return 1;
#else
    execv(exe_path, new_argv); // If we go past here, execv failed, so print an error and die
    perror("Failed to start main Azahar executable");
    return 1;
#endif
}
