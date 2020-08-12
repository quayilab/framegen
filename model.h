#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include <tinyxml2.h>
#include <cairo/cairo.h>

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

vector<Path> getPaths(XMLElement* elComp, bool verbose) {
    vector<Path> paths;
    XMLElement* path = elComp->FirstChildElement();
    do {
        if (verbose)
            cout << "  get child... OK\n";
        Path p{};
        const char* id = path->Attribute("id");
        if (id == NULL) {
            id = "";
            if (verbose)
                cout << "  no id provided for path";
        }
        p.ID = string(id);

        const char* d = path->Attribute("d");
        if (d == NULL) {
            d = "";
            if (verbose)
                cout << "  path is empty, skipping";
            path = path->NextSiblingElement(); 
            continue;
        }
        p.Command = string(d);

        const char* style = path->Attribute("style");
        if (style == NULL) {
            d = "";
            if (verbose)
                cout << "  style is empty, using default";
        }
        p.Style = string(style);

        path = path->NextSiblingElement(); 
        paths.push_back(p);
    } while (path != NULL);
    return paths;
}

Component getComponent(string fileName, bool verbose) {
    Component component = Component{};
    XMLDocument elDoc;
    XMLError err = elDoc.LoadFile(fileName.c_str());
    if (err == XML_SUCCESS) {
        if (verbose)
            cout << "  opening source file (\"" << fileName << "\")... OK" << endl;
        XMLElement* elComp = elDoc.FirstChildElement("svg")->FirstChildElement("g");
        if (elComp != NULL) {
            if (verbose)
                cout << "  getting document structure... OK" << endl;
            if (!elComp->NoChildren()) {
                const char* compId = elComp->Attribute("data-component-id");
                if (compId == NULL) {
                    if (verbose)
                        cout << "  getting data-component-id... OK" << endl;
                    compId = "";
                }
                component.ID = string(compId);

                if (verbose)
                    cout << "  getting data-component-id... OK" << endl;
                component.Paths = getPaths(elComp, verbose);
            }
        } else {
            if (verbose)
                cout << "  getting document structure... ERROR" << endl;
        }
    }
    else {
        if (verbose)
            cout << "  opening source file (\"" << fileName << "\")... ERROR" << endl;
    }
    return component;
}

void stripSvg(string srcFile, string destFile, string version, bool verbose = false) {
    ofstream output;
    if (verbose) {
        cout << "processing..." << endl;
    }
    Component c = getComponent(srcFile, verbose);
    output.open(destFile);
    output << "<svg><g version=\"" << version << "\" data-component-id=\"" << c.ID << "\">";
    if (verbose) 
        cout << "  reading paths..." << endl;
    for (int i=0; i <c.Paths.size(); i++) {
        Path p = c.Paths[i];
        output << "<path id=\"" << p.ID << "\" d=\"" << p.Command << "\" style=\"" << p.Style << "\"/>";
        if (verbose) 
            cout << "  reading paths \"" << p.ID << "\"" << endl;
    }
    output << "</g></svg>";
    if (verbose) {
        cout << "  saving to destination file (\"" << destFile << "\")..." << endl;
        cout << "processing finished\n";
    }
    output.close();
}

void saveToYaml(string srcFile, string destFile, string version, bool verbose = false) {
    ofstream output;
    if (verbose) {
        cout << "processing..." << endl;
    }
    Component c = getComponent(srcFile, verbose);
    output.open(destFile);
    output << "version: \"" << version << "\"\n";
    output << "id: \"" << c.ID << "\"\n";
    output << "paths:\n";
    if (verbose) 
        cout << "  reading paths..." << endl;
    for (int i=0; i <c.Paths.size(); i++) {
        Path p = c.Paths[i];
        output << "  - id: \"" << p.ID << "\"\n";
        output << "    command: \"" << p.Command << "\"\n";
        output << "    style: \"" << p.Style << "\"\n";
        if (verbose) 
            cout << "  reading paths \"" << p.ID << "\"" << endl;
    }
    if (verbose) 
        cout << "  saving to destination file (\"" << destFile << "\")..." << endl;
    if (verbose)
        cout << "processing finished\n";
    output.close();
}

/*void renderPath(cairo_t* cr, string path, string style) {
    double r, g, b, a;
    cairo_set_source_rgba(cr, r, g, b, a);
    //cairo_rende
}

void renderComponent(cairo_surface_t* sfc, Component* component, double x, double y) {
    cairo_t* cr = cairo_create(sfc);
    for (int i = 0; i < component->Paths.size(); i++) {
        Path p = component->Paths[i];
        renderPath(cr, p.Command, p.Style);
    }
}*/