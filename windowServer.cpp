// windowServer.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <json/json.h>

// Include the necessary headers for modala.js
#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <emscripten/fetch.h>

using namespace std;

string path = "";

EM_ASM( {
        fetch(path)
            .then(response => response.text())
            .then(data => {
                // Handle the response from the PHP script
                console.log(data);
            })
            .catch(error => {
                // Handle any errors
                console.error(error);
            });
    }, path);

// Function to iterate through form elements and create JSON
Json::Value createFormJSON()
{
    Json::Value formData(Json::objectValue);

    // Get all form elements with the value of the key "form-class"
    vector<HWND> formElements;
    EnumChildWindows(
        GetDesktopWindow(), [](HWND hwnd, LPARAM lParam) -> BOOL
        {
        vector<HWND>& formElements = *reinterpret_cast<vector<HWND>*>(lParam);
        char className[256];
        GetClassNameA(hwnd, className, sizeof(className));
        if (strcmp(className, "form-class") == 0) {
            char formClass[256];
            GetWindowTextA(hwnd, formClass, sizeof(formClass));

            // Split the formClass string by spaces
            string formClassStr(formClass);
            istringstream iss(formClassStr);
            vector<string> formClasses{ istream_iterator<string>{iss}, istream_iterator<string>{} };

            // Add the submit button to the formElements vector for each form class
            for (const string& formClass : formClasses) {
                formElements.push_back(hwnd);
            }
        }
        return TRUE; },
        reinterpret_cast<LPARAM>(&formElements));

    // Iterate through form elements and extract information
    for (HWND formElement : formElements)
    {
        char text[256];
        GetWindowTextA(formElement, text, sizeof(text));
        char className[256];
        GetClassNameA(formElement, className, sizeof(className));

        // Create JSON object for each form element
        Json::Value formElementData(Json::objectValue);
        formElementData["text"] = text;
        formElementData["class"] = className;

        // Add form element data to the main form data JSON object
        formData[to_string(reinterpret_cast<uintptr_t>(formElement))] = formElementData;
    }

    return formData;
}
// Function to generate a random content for the window
string generateContent()
{
    string content = "";
    int length = rand() % 6 + 5;
    string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int charactersLength = characters.length();
    for (int i = 0; i < length; i++)
    {
        content += characters[rand() % charactersLength];
    }
    return content;
}

// Function to generate the window server data
Json::Value generateData()
{
    Json::Value data(Json::arrayValue);
    int numWindows = rand() % 4 + 3;
    for (int i = 0; i < numWindows; i++)
    {
        Json::Value window;
        window["id"] = i + 1;
        window["content"] = generateContent();
        data.append(window);
    }
    return data;
}

// Function to write JSON data to a file
void writeJSON(const Json::Value &data, const string &filename)
{
    Json::StreamWriterBuilder writer;
    writer["indentation"] = "\t";
    unique_ptr<Json::StreamWriter> jsonWriter(writer.newStreamWriter());
    ofstream file(filename);
    jsonWriter->write(data, &file);
    file.close();
}

// Function to insert data into the DOM using the insert attribute as the target
void insertToNode(emscripten::val document, emscripten::val tagId)
{
    // Get the injector element
    emscripten::val injector = document.call<emscripten::val>("getElementById", tagId);

    // Get the insert attribute's value
    string targetId = injector["getAttribute"]("insert").as<string>();

    // Get the target element
    emscripten::val target = document.call<emscripten::val>("getElementById", targetId);

    // Get the ajax attribute's value
    string data = injector["getAttribute"]("ajax").as<string>();

    // Inject the data into the target element
    target.set("textContent", data);
}

int main(int argc, char **argv)
{
    // Get the rootNode element
    emscripten::val document = emscripten::val::global("document");
    emscripten::val rootNode = document[argv[1]];

    // Create a new DOM element
    emscripten::val newElement = document.call<emscripten::val>("createElement", "div");
    newElement.set("textContent", "This is the new rootNode element!");

    // Insert the new element as the rootNode
    insertToNode(newElement, rootNode);

    return 0;
}