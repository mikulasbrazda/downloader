#include <iostream>
#include <string>


const auto CURL_COMMAND = "curl";
const std::string OUTPUT_DIR = "./downloads/";
const auto THREAD_COUNT = 3;
/*
 * Downloads a file from the given URL and saves it to the specified output file.
 * Prints status messages to the console.
 * @param threadId The identifier for the thread performing the download. This is used for 
 * suffixing the output file name. So multiple threads can download files with same names concurrently.
 */
void downloadFile(const std::string threadId);

/*
 * Extracts the output file name from a URL by taking the substring after the last '/'.
 * If no '/' is found, returns the entire URL as the filename.
 * @param url The URL to extract the filename from.
 * @return The output file name.
 */
std::string getOutputFileName(const std::string& url);