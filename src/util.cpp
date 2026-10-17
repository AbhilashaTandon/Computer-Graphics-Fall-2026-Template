#include "../include/util.h"

void report_file_error(const char *&file_path, std::ifstream &file) {
        if (!file.is_open()) {
                std::cerr << "Error opening file: \"" << file_path << "\"";

                if (file.fail()) {
                        // Print a more detailed error message using
                        // strerror
                        std::cerr << ". " << std::strerror(errno) << std::endl;
                }

                // Check for specific error conditions
                if (file.bad()) {
                        std::cerr << "Fatal error: badbit is set." << std::endl;
                }
        }
}
