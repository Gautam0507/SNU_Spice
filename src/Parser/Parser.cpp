/*
 * Copyright (c) 2022, Shiv Nadar University, Delhi NCR, India. All Rights
 * Reserved. Permission to use, copy, modify and distribute this software for
 * educational, research, and not-for-profit purposes, without fee and without a
 * signed license agreement, is hereby granted, provided that this paragraph and
 * the following two paragraphs appear in all copies, modifications, and
 * distributions.
 *
 * IN NO EVENT SHALL SHIV NADAR UNIVERSITY BE LIABLE TO ANY PARTY FOR DIRECT,
 * INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST
 * PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE.
 *
 * SHIV NADAR UNIVERSITY SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT
 * NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE. THE SOFTWARE PROVIDED HEREUNDER IS PROVIDED "AS IS". SHIV
 * NADAR UNIVERSITY HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES,
 * ENHANCEMENTS, OR MODIFICATIONS.
 */
/**
 * @file Parser.cpp
 *
 * @brief Contains the implementation of the Parser class
 */

#include "../../include/Parser.hpp"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <sstream>

using std::cout, std::endl;

int Parser::parse(const std::string &fileName)
{
    cout << "\nFile Name: " + fileName << endl;

    std::ifstream fileStream(fileName);
    if (!fileStream) {
        cout << "Error: Netlist not avialable in the project directory" << endl;
        return 1;
    }
    std::string line;
    int lineNumber = 1, v_count = 0, i_count = 0, r_count = 0, c_count = 0,
        vc_count = 0, ic_count = 0, error = 0, l_count = 0;

    // Stores pointer of all independent sources and resistors
    // for assigning to controlling_element variable later
    std::map<std::string, std::shared_ptr<CircuitElement>> elementMap;

    while (getline(fileStream, line)) {
        lineNumber++;

        std::transform(line.begin(), line.end(), line.begin(), ::toupper);

        std::stringstream ss(line);
        std::vector<std::string> tokens;
        std::string buf;

        while (ss >> buf) tokens.push_back(buf);

        // Skips empty lines and comments
        if (tokens.size() == 0 || tokens.at(0).find("%") == 0) continue;

        // Both nodes can't be same
        if (tokens.at(1) == tokens.at(2)) {
            cout << "Warning: Two nodes of a element can't be same. Line "
                    "number: "
                 << (lineNumber - 1) << ": " + line << endl;
            continue;
        }

        // Checks whether the value is actual double and not zero
        char *end = 0;
        double value = strtod(tokens.at(3).c_str(), &end);
        if (end == tokens.at(3).c_str() || *end != '\0' || value == HUGE_VAL ||
            value == 0) {
            cout << "Error: Illegal argument for value at line number "
                 << (lineNumber - 1) << ": " + line << end;
            error += 1;
            value = 1;
        }

        // Dependent Current Source (contains two data validation condidtions)
        if ((tokens.at(0).find("IC") == 0) && (tokens.size() >= 6)) {
            std::shared_ptr<CircuitElement> temp =
                std::make_shared<CircuitElement>();
            temp->name = tokens.at(0);
            temp->type = Ic;
            temp->nodeA = tokens.at(1);
            temp->nodeB = tokens.at(2);
            temp->group = G1;
            temp->value = value;
            temp->controlling_variable = (tokens.at(4) == "V") ? v : i;

            // Data Validation: Illegal controlling variable argument
            if (tokens.at(4) != "V" && tokens.at(4) != "I") {
                cout << "Error: Illegal controlling variable argument at line "
                        "number "
                     << (lineNumber - 1) << ": " + line << end;
                error += 1;
            }

            // Data Validation: Cascading of controlled sources is not allowed
            if (tokens.at(5).find("IC") == 0 || tokens.at(5).find("VC") == 0) {
                cout << "Error: Controlled source " + tokens.at(0) +
                            " cannot be cascaded at line number "
                     << (lineNumber - 1) << ": " + line << end;
                error += 1;

                temp->controlling_variable = none;
                temp->controlling_element = NULL;
            } else {
                temp->controlling_element = std::make_shared<CircuitElement>();
                temp->controlling_element->name = tokens.at(5);
            }

            temp->processed = false;

            nodes_group2.insert(temp->nodeA);
            nodes_group2.insert(temp->nodeB);

            circuitElements.push_back(temp);

            ic_count++;
        }

        // Dependent Voltage Source (contains tow data validation condidtions)
        else if ((tokens.at(0).find("VC") == 0) && (tokens.size() >= 6)) {
            std::shared_ptr<CircuitElement> temp =
                std::make_shared<CircuitElement>();
            temp->name = tokens.at(0);
            temp->type = Vc;
            temp->nodeA = tokens.at(1);
            temp->nodeB = tokens.at(2);
            temp->group = G2;
            temp->value = value;
            temp->controlling_variable = tokens.at(4) == "V" ? v : i;

            // Data Validation: Illegal controlling variable argument
            if (tokens.at(4) != "V" && tokens.at(4) != "I") {
                cout << "Error: Illegal controlling variable argument at line "
                        "number "
                     << (lineNumber - 1) << ": " + line << end;
                error += 1;
            }

            // Data Validation: Cascading of controlled sources is not allowed
            if (tokens.at(5).find("IC") == 0 || tokens.at(5).find("VC") == 0) {
                cout << "Error: Controlled source " + tokens.at(0) +
                            " cannot be cascaded"
                     << end;
                error += 1;

                temp->controlling_variable = none;
                temp->controlling_element = NULL;
            } else {
                temp->controlling_element = std::make_shared<CircuitElement>();
                temp->controlling_element->name = tokens.at(5);
            }

            temp->processed = false;

            nodes_group2.insert(temp->name);
            nodes_group2.insert(temp->nodeA);
            nodes_group2.insert(temp->nodeB);

            circuitElements.push_back(temp);

            vc_count++;
        }

        // Independent Voltage Source
        else if ((tokens.at(0).find("V") == 0) && (tokens.size() >= 4)) {
            std::shared_ptr<CircuitElement> temp =
                std::make_shared<CircuitElement>();
            temp->name = tokens.at(0);
            temp->type = V;
            temp->nodeA = tokens.at(1);
            temp->nodeB = tokens.at(2);
            temp->group = G2;
            temp->value = value;
            temp->controlling_variable = none;
            temp->controlling_element = NULL;
            temp->processed = false;

            circuitElements.push_back(temp);
            elementMap[temp->name] = temp;

            nodes_group2.insert(temp->name);
            nodes_group2.insert(temp->nodeA);
            nodes_group2.insert(temp->nodeB);

            v_count++;
        }

        // Independent Current Source (contains one data validation condition)
        else if ((tokens.at(0).find("I") == 0) && (tokens.size() >= 4)) {
            std::shared_ptr<CircuitElement> temp =
                std::make_shared<CircuitElement>();
            temp->name = tokens.at(0);
            temp->type = I;
            temp->nodeA = tokens.at(1);
            temp->nodeB = tokens.at(2);
            if (tokens.size() >= 5 && tokens.at(4) == "G2") {
                temp->group = G2;
                nodes_group2.insert(temp->name);
            }
            // Data Validation: Correct group declaration
            else if (tokens.size() >= 5 && tokens.at(4) != "G1") {
                cout << "Warning: Mention correct group at line number "
                     << (lineNumber - 1) << ": " + line << end;
                temp->group = G1;
            } else
                temp->group = G1;
            temp->value = value;
            temp->controlling_variable = none;
            temp->controlling_element = NULL;
            temp->processed = false;

            circuitElements.push_back(temp);
            elementMap[temp->name] = temp;

            nodes_group2.insert(temp->nodeA);
            nodes_group2.insert(temp->nodeB);

            i_count++;
        }

        // Resistor (contains one data validation condition)
        else if ((tokens.at(0).find("R") == 0) && (tokens.size() >= 4)) {
            std::shared_ptr<CircuitElement> temp =
                std::make_shared<CircuitElement>();
            temp->name = tokens.at(0);
            temp->type = R;
            temp->nodeA = tokens.at(1);
            temp->nodeB = tokens.at(2);
            if (tokens.size() >= 5 && tokens.at(4) == "G2") {
                temp->group = G2;
                nodes_group2.insert(temp->name);
            }
            // Data Validation: Correct group declaration
            else if (tokens.size() >= 5 && tokens.at(4) != "G1") {
                cout << "Warning: Mention correct group at line number "
                     << (lineNumber - 1) << ": " + line << endl;
                temp->group = G1;
            } else
                temp->group = G1;
            temp->value = value;
            temp->controlling_variable = none;
            temp->controlling_element = NULL;
            temp->processed = false;

            nodes_group2.insert(temp->nodeA);
            nodes_group2.insert(temp->nodeB);

            circuitElements.push_back(temp);
            elementMap[temp->name] = temp;

            r_count++;
        }
        // Capacitor (Contains one data validation condition
        else if ((tokens.at(0).find("C") == 0) && (tokens.size() >= 4)) {
            std::shared_ptr<CircuitElement> temp =
                std::make_shared<CircuitElement>();
            temp->name = tokens.at(0);
            temp->type = C;
            temp->nodeA = tokens.at(1);
            temp->nodeB = tokens.at(2);
            if (tokens.size() >= 5 && tokens.at(4) == "G2") {
                temp->group = G2;
                nodes_group2.insert(temp->name);
            }
            // Data Validation: Correct group declaration
            else if (tokens.size() >= 5 && tokens.at(4) != "G1") {
                cout << "Warning: Mention correct group at line number "
                     << (lineNumber - 1) << ": " + line << endl;
                temp->group = G1;
            } else
                temp->group = G1;
            temp->value = value;
            temp->controlling_variable = none;
            temp->controlling_element = NULL;
            temp->processed = false;

            nodes_group2.insert(temp->nodeA);
            nodes_group2.insert(temp->nodeB);

            circuitElements.push_back(temp);
            elementMap[temp->name] = temp;

            c_count++;
        }  // Inductors (always  group 2)
        else if ((tokens.at(0).find("L") == 0) && (tokens.size() >= 4)) {
            std::shared_ptr<CircuitElement> temp =
                std::make_shared<CircuitElement>();
            temp->name = tokens.at(0);
            temp->type = L;
            temp->nodeA = tokens.at(1);
            temp->nodeB = tokens.at(2);
            temp->group = G2;
            temp->value = value;
            temp->controlling_variable = none;
            temp->controlling_element = NULL;
            temp->processed = false;

            circuitElements.push_back(temp);
            elementMap[temp->name] = temp;

            nodes_group2.insert(temp->name);
            nodes_group2.insert(temp->nodeA);
            nodes_group2.insert(temp->nodeB);

            l_count++;
        }
        // Unknown Element
        else {
            cout << "Error: Unknown element at line number " << (lineNumber - 1)
                 << ": " + line << endl;
            error += 1;
        }
    }

    // Assign controlling_element variable using the pointers stored in the map
    for (std::shared_ptr<CircuitElement> circuitElement : circuitElements) {
        if (circuitElement->controlling_variable != none) {
            // Checks whether the referenced element is present in the netlist
            if (elementMap.find(circuitElement->controlling_element->name) !=
                elementMap.end()) {
                circuitElement->controlling_element =
                    elementMap[circuitElement->controlling_element->name];

                // Make sures that the current controlling element is Group 2
                if (circuitElement->controlling_variable == i &&
                    circuitElement->controlling_element->group != G2) {
                    cout << "Warning: Referenced element " +
                                circuitElement->controlling_element->name +
                                " must be in group 2 as its current variable "
                                "is required "
                                "by " +
                                circuitElement->name
                         << endl;
                    circuitElement->controlling_element->group = G2;
                    nodes_group2.insert(
                        circuitElement->controlling_element->name);
                }
            } else {
                cout << "Error: Referencing element " +
                            circuitElement->controlling_element->name +
                            ", referenced by " + circuitElement->name +
                            " is not present in the netlist"
                     << endl;
                error += 1;
            }
        }
    }

    // Checks if the circuit contains ground (reference node)
    if (nodes_group2.find("0") == nodes_group2.end()) {
        cout << "Error: Circuit must contain ground (0)" << endl;
        error += 1;
    }

    if (error == 0) {
        cout << "\nTotal Independent Voltage Source(s) in the Circuit: "
             << v_count << endl;
        cout << "Total Independent Current Source(s) in the Circuit: "
             << i_count << endl;
        cout << "Total Resistor(s) in the Circuit: " << r_count << endl;
        cout << "Total Dependent Voltage Source(s) in the Circuit: " << vc_count
             << endl;
        cout << "Total Dependent Current Source(s) in the Circuit: " << ic_count
             << endl;
        cout << "Total Capacitor(s) in the Circuit: " << c_count << endl;
        cout << "Total Inductors(s) in the Circuit: " << l_count << endl;
    }

    return error;
}

void Parser::printParser()
{
    for (std::shared_ptr<CircuitElement> circuitElement : circuitElements)
        if (circuitElement->type == V || circuitElement->type == I ||
            circuitElement->type == R)
            cout << circuitElement->name + " " + circuitElement->nodeA + " " +
                        circuitElement->nodeB + " "
                 << circuitElement->value << " " << circuitElement->group
                 << endl;
        else
            cout << circuitElement->name + " " + circuitElement->nodeA + " " +
                        circuitElement->nodeB + " "
                 << circuitElement->value << " " << circuitElement->group << " "
                 << circuitElement->controlling_variable << " "
                 << circuitElement->controlling_element->name + " " +
                        circuitElement->controlling_element->nodeA + " " +
                        circuitElement->controlling_element->nodeB
                 << endl;
}
