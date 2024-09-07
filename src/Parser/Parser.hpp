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

#pragma once

#include <memory>
#include <set>
#include <string>
#include <vector>

#include "../CircuitElement/CircuitElement.hpp"

class Parser
{
   public:
    std::vector<std::shared_ptr<CircuitElement>>
        circuitElements;  // Stores the circuit elements in form of a vector
    std::set<std::string> nodes_group2;  // Stores all node names and group_2
                                         // circuit element names

    /*
     * @brief		Parses the file (netlist) into a vector
     *
     * @param[ref]	file string
     *
     * @return		number of errors in the netlist
     */
    int parse(const std::string &file);

    /*
     * @brief		Prints the vectors which contains the circuit elements
     *
     * @return		void
     */
    void print();
};
