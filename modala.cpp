#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <json/json.h>

using namespace std;

void modala(const Json::Value& jsonObj, Json::Value& rootNode) {
    if (jsonObj.isMember("tempTag")) {
        string tempTag = jsonObj["tempTag"].asString();
        if (rootNode.isMember(tempTag)) {
            Json::Value& tempTagNode = rootNode[tempTag];
            if (jsonObj.isMember("root")) {
                string root = jsonObj["root"].asString();
                if (rootNode.isMember(root)) {
                    Json::Value& rootNode = rootNode[root];
                    if (jsonObj.isMember("value")) {
                        Json::Value value = jsonObj["value"];
                        if (tempTagNode.isObject() && value.isObject()) {
                            Json::Value temp(Json::objectValue);
                            temp["tagname"] = value["tagname"];

                            for (const auto& entry : value.getMemberNames()) {
                                const string& k = entry;
                                const Json::Value& v = value[k];

                                if (v.isObject()) {
                                    modala(v, temp, rootNode);
                                }
                                else if (k == "select" && tempTagNode.isObject() && tempTagNode.isMember("tagname") && tempTagNode["tagname"].asString() == "select") {
                                    Json::Value select(Json::objectValue);
                                    temp["select"] = select;
                                    modala(v, temp, rootNode);
                                }
                                else if (k == "options" && tempTagNode.isObject() && tempTagNode.isMember("tagname") && tempTagNode["tagname"].asString() == "select") {
                                    string optsArray = v.asString();
                                    vector<string> opts;
                                    size_t pos = 0;
                                    string delimiter = ";";
                                    while ((pos = optsArray.find(delimiter)) != string::npos) {
                                        string opt = optsArray.substr(0, pos);
                                        opts.push_back(opt);
                                        optsArray.erase(0, pos + delimiter.length());
                                    }
                                    opts.push_back(optsArray);

                                    for (const string& e : opts) {
                                        size_t colonPos = e.find(":");
                                        if (colonPos != string::npos) {
                                            string g1 = e.substr(0, colonPos);
                                            string g2 = e.substr(colonPos + 1);
                                            Json::Value select(Json::objectValue);
                                            select["value"] = g2;
                                            select["textContent"] = g1;
                                            tempTagNode["options"].append(select);
                                        }
                                    }
                                }
                                else if (k == "css") {
                                    string cssvar = v.asString();
                                    tempTagNode["css"] = cssvar;
                                }
                                else if (k == "js") {
                                    string js = v.asString();
                                    tempTagNode["js"] = js;
                                }
                                else if (k != "tagname" && k != "textContent" && k != "innerHTML" && k != "innerText") {
                                    temp[k] = v;
                                }
                                else if (k == "textContent") {
                                    temp["textContent"] = v;
                                }
                                else if (k == "innerHTML") {
                                    temp["innerHTML"] = v;
                                }
                                else if (k == "innerText") {
                                    temp["innerText"] = v;
                                }
                            }

                            rootNode.append(temp);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    // Example usage
    Json::String jsonObj(Json::String);
    Json::Value rootNode(Json::arrayValue);

    // Populate jsonObj with the desired JSON data

    modala(jsonObj, rootNode);

    // Print the resulting JSON
    cout << rootNode << endl;

    return 0;
}