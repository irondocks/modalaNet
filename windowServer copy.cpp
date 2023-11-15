// windowServer.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <json/json.h>

using namespace std;

// Function to generate a random content for the window
string generateContent() {
    string content = "";
    int length = rand() % 6 + 5;
    string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int charactersLength = characters.length();
    for (int i = 0; i < length; i++) {
        content += characters[rand() % charactersLength];
    }
    return content;
}

// Function to generate the window server data
Json::Value generateData() {
    Json::Value data(Json::arrayValue);
    int numWindows = rand() % 4 + 3;
    for (int i = 0; i < numWindows; i++) {
        Json::Value window;
        window["id"] = i + 1;
        window["content"] = generateContent();
        data.append(window);
    }
    return data;
}

// Function to write JSON data to a file
void writeJSON(const Json::Value& data, const string& filename) {
    Json::StreamWriterBuilder writer;
    writer["indentation"] = "\t";
    unique_ptr<Json::StreamWriter> jsonWriter(writer.newStreamWriter());
    ofstream file(filename);
    jsonWriter->write(data, &file);
    file.close();
}

int main() {
    srand(time(0));

    // Generate the data
    Json::Value data = generateData();

    // Write the data to JSON file
    writeJSON(data, "data.json");

    // Read the data from JSON file
    ifstream file("data.json");
    Json::CharReaderBuilder reader;
    Json::Value jsonData;
    JSONCPP_STRING errors;
    Json::parseFromStream(reader, file, &jsonData, &errors);
    file.close();

    // Update the DOM with the fetched data
    HWND hwnd = GetConsoleWindow();
    HDC hdc = GetDC(hwnd);
    RECT rect;
    GetClientRect(hwnd, &rect);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    for (const auto& window : jsonData) {
        string content = window["content"].asString();
        TextOut(hdc, rand() % (width - 100), rand() % (height - 50), content.c_str(), content.length());
    }

    // Release the device context
    ReleaseDC(hwnd, hdc);

    return 0;
}
