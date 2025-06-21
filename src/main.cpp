#include "main.h"

int main(void) {
    std::cout << "Enter URL to download (or 'quit' to quit): ";
    std::string url;
    
    if (!std::filesystem::exists(OUTPUT_DIR)) {
        std::filesystem::create_directories(OUTPUT_DIR);
    }

    while (std::cin >> url) {
        
        if (url == "quit") {
            break;
        }
		std::string outputFile = getOutputFileName(url);
        downloadFile(url, outputFile);
    }
    return 0;
}

void downloadFile(const std::string& url, const std::string& outputFile) {
	std::string command = CURL_COMMAND; 
	command += " -o \"" + OUTPUT_DIR + outputFile + "\" \"" + url + "\"";
    std::cout << "Downloading " << url << " to "  << OUTPUT_DIR << outputFile << "..." << std::endl;
    
    int result = system(command.c_str());
    
    if (result == 0) {
        std::cout << "Download completed successfully." << std::endl;
    } else {
        std::cerr << "Error downloading file. Command returned: " << result << std::endl;
	}
}

std::string getOutputFileName(const std::string& url) {
    auto pos = url.find_last_of('/');
    if (pos == std::string::npos) {
		return url;
    }
    return url.substr(pos + 1);
}
