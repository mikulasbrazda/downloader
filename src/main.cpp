#include "main.h"
#include <thread>
#include <filesystem>
#include <condition_variable>
#include <queue>

std::queue<std::string> downloadQueue;
std::condition_variable queueCondition;
bool stop = false;
std::mutex queueMutex;
std::mutex coutMutex;
std::mutex cerrMutex;

int main(void) {

    if (!std::filesystem::exists(OUTPUT_DIR)) {
        std::filesystem::create_directories(OUTPUT_DIR);
    }

    std::cout << "Enter URL to download (or 'quit' to quit): ";

    std::string url;
    std::vector<std::thread> downloadThreads;
    for (auto i = 0; i < THREAD_COUNT; i++) {
		downloadThreads.push_back(std::thread(downloadFile, std::to_string(i)));
    }
    while (std::cin >> url) {
        if (url.empty()) {
			std::lock_guard<std::mutex> lock(coutMutex);
            std::cout << "Please enter a valid URL." << std::endl;
            continue;
        }
        if (url == "quit") {
            std::lock_guard<std::mutex> lock(queueMutex);
            stop = true;
            queueCondition.notify_all();
            break;
        }
        else {
            std::lock_guard<std::mutex> lock(queueMutex);
            downloadQueue.push(url);
            queueCondition.notify_one();
        }
    }

    for (auto& thread : downloadThreads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    return 0;
}

void downloadFile(const std::string threadId) {
    
    std::string url;
    while (true) {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            queueCondition.wait(lock, [] { return !downloadQueue.empty() || stop; });
            if (stop) {
                std::lock_guard<std::mutex> lock(cerrMutex);
                std::cerr << "Stopping download thread." << std::endl;
                return;
            }
            url = downloadQueue.front();
            downloadQueue.pop();
        }
        std::string outputFile = getOutputFileName(url);
        std::string command = CURL_COMMAND;
        command += " -s -o \"" + OUTPUT_DIR + outputFile + "_" + threadId + "\" \"" + url + "\"";
        
        {
            std::lock_guard<std::mutex> lock(coutMutex);
            std::cout << "Downloading " << url << " to " << OUTPUT_DIR << outputFile << "_" << threadId << "..." << std::endl;
        }
		// Warning: Thread safety is not guaranteed with system calls.
		// Consider using a library like libcurl or boost::beast for better thread safety.
		// For demonstration purposes, we use system() here.
        int result = system(command.c_str());

        if (result == 0) {
			std::lock_guard<std::mutex> lock(coutMutex);
            std::cout << "Download completed successfully." << std::endl;
        }
        else {
			std::lock_guard<std::mutex> lock(cerrMutex);
            std::cerr << "Error downloading file. Command returned: " << result << std::endl;
        }
    }
}

std::string getOutputFileName(const std::string& url) {
    auto pos = url.find_last_of('/');
    if (pos == std::string::npos) {
		return url;
    }
    return url.substr(pos + 1);
}
