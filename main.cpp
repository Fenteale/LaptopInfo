#include <iostream>
#include <string>
#include <curl/curl.h>
using namespace std;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main()
{
    string userInput;

    bool isScanned = false;

    cout << "Hello, please input model number of laptop" << endl;
    cin >> userInput;
    string scannedChk = userInput.substr(0, 2);
    if(scannedChk=="1P"||scannedChk=="1p")
    {
        isScanned == true;
        userInput = userInput.substr(2, userInput.length()-2);
        cout << "This unit's part number was scanned in." << endl;
    }
    else
    {
        cout << "This unit's part number was typed in." << endl;
        isScanned = false;
    }

    cout << "Part Number: " << userInput << endl;
    cout << "Model Name: ";


    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    string urlToAccess = "https://support.dynabook.com/support/modelHome?freeText=" + userInput;

    curl = curl_easy_init();
    
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, urlToAccess.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        //std::cout << readBuffer << std::endl;
        size_t foundName = readBuffer.find("    <title>");
        size_t foundNameEnd = readBuffer.find(" Support | Dynabook");
        if(foundName!=string::npos&&foundNameEnd!=string::npos)
            cout << readBuffer.substr(foundName+11, foundNameEnd- (foundName+11)) << endl;
    }
    return 0;

}