#include <iostream>
#include <string>
#include <thread>
#include <filesystem>

const auto CURL_COMMAND = "curl";
const std::string OUTPUT_DIR = "./downloads/";

/*
 * Downloads a file from the given URL and saves it to the specified output file.
 * Prints status messages to the console.
 * @param url The URL to download.
 * @param outputFile The name of the file to save the downloaded content.
 */
void downloadFile(const std::string& url, const std::string& outputFile);

/*
 * Extracts the output file name from a URL by taking the substring after the last '/'.
 * If no '/' is found, returns the entire URL as the filename.
 * @param url The URL to extract the filename from.
 * @return The output file name.
 */
std::string getOutputFileName(const std::string& url);