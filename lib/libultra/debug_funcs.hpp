/********************************************************************************
 * File: debug_funcs.hpp
 * Author: ppkantorski
 * Description:
 *   This header file contains debugging functions for the Ultrahand Overlay project.
 *   These functions allow logging messages with timestamps to a log file.
 *
 *   For the latest updates and contributions, visit the project's GitHub repository.
 *   (GitHub Repository: https://github.com/ppkantorski/Ultrahand-Overlay)
 *
 *   Note: Please be aware that this notice cannot be altered or removed. It is a part
 *   of the project's documentation and must remain intact.
 * 
 *  Licensed under both GPLv2 and CC-BY-4.0
 *  Copyright (c) 2024 ppkantorski
 ********************************************************************************/

#pragma once
#include <fstream>

// Specify the log file path
const std::string logFilePath = "sdmc:/config/ultrahand/log.txt";


// Global mutex for thread-safe logging
std::mutex logMutex;

/**
 * @brief Logs a message with a timestamp to a log file in a thread-safe manner.
 *
 * @param message The message to be logged.
 */
void logMessage(const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex); // Locks the mutex for the duration of this function

    std::time_t currentTime = std::time(nullptr);
    std::string logEntry = std::asctime(std::localtime(&currentTime));
    size_t lastNonNewline = logEntry.find_last_not_of("\r\n");
    if (lastNonNewline != std::string::npos)
        logEntry.erase(lastNonNewline + 1);
    
    logEntry = "[" + logEntry + "] " + message + "\n";
    
    // Open the file with std::ofstream in append mode
    std::ofstream file(logFilePath, std::ios::app);
    if (file.is_open()) {
        file << logEntry;
        file.close(); // Explicitly closing the file, though it will automatically close upon destruction
    } else {
        // Handle error when file opening fails, such as logging to an alternative output or retrying
        //std::cerr << "Failed to open log file: " << logFilePath << std::endl;
    }
}