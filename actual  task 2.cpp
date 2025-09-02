#include <iostream>
#include <curl/curl.h>
#include <string>
using namespace std;

static size_t writeFunc(void* contents, size_t size, size_t nmemb, void* userp) {
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main() {
    string text, src, tgt;

    cout << "Text: ";
    getline(cin, text);

    cout << "From (lang code): ";
    cin >> src;
    cout << "To (lang code): ";
    cin >> tgt;

    string key = "YOUR_API_KEY";  // replace with your actual key
    string url = "https://translation.googleapis.com/language/translate/v2?key=" + key;
    string body = "q=" + text + "&source=" + src + "&target=" + tgt + "&format=text";

    CURL* curl = curl_easy_init();
    string buffer;
    if (curl) {
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);

        cout << "Result (raw JSON): " << buffer << endl;
    }
    return 0;
}