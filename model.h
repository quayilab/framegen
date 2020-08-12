#include <string>
#include <vector>
#include <fstream>
#include <tinyxml2.h>

using namespace std;
using namespace tinyxml2;

namespace model {
    const string VERSION_STRING = "0.0.1 alpha";
}

string getVersion() {
    return model::VERSION_STRING;
}

struct Path {
    string ID;
    string Command;
    string Style;
};

struct Component {
    string ID;
    vector<Path> Paths;
};

vector<Path> getPaths(XMLElement* elComp) {
    vector<Path> paths;
    XMLElement* path = elComp->FirstChildElement();
    do {
        Path p{};
        p.ID = string(path->Attribute("id"));
        p.Command = string(path->Attribute("d"));
        p.Style = string(path->Attribute("style"));
        path = path->NextSiblingElement(); 
        paths.push_back(p);
    } while (path != NULL);
    return paths;
}

Component getComponent(string fileName) {
    Component component = Component{};
    XMLDocument elDoc;
    elDoc.LoadFile(fileName.c_str());
    XMLElement* elComp = elDoc.FirstChildElement("svg")->FirstChildElement("g");
    if (!elComp->NoChildren()) {
        component.ID = string(elComp->Attribute("data-component-id"));
        component.Paths = getPaths(elComp);
    }
    return component;
}

void stripSvg(string srcFile, string destFile, string version) {
    ofstream output;
    Component c = getComponent(srcFile);
    output.open(destFile);
    output << "<svg><g version=\"" << version << "\" data-component-id=\"" << c.ID << "\">";
    for (int i=0; i <c.Paths.size(); i++) {
        Path p = c.Paths[i];
        output << "<path id=\"" << p.ID << "\" d=\"" << p.Command << "\" style=\"" << p.Style << "\"/>";
    }
    output << "</g></svg>";
    output.close();
}

void saveToYaml(string srcFile, string destFile, string version) {
    ofstream output;
    Component c = getComponent(srcFile);
    output.open(destFile);
    output << "version: \"" << version << "\"\n";
    output << "id: \"" << c.ID << "\"\n";
    output << "paths:\n";
    for (int i=0; i <c.Paths.size(); i++) {
        Path p = c.Paths[i];
        output << "  - id: \"" << p.ID << "\"\n";
        output << "    command: \"" << p.Command << "\"\n";
        output << "    style: \"" << p.Style << "\"\n";
    }
    output.close();
}