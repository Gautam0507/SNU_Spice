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
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../lib/external/Eigen/Dense"
#include "Node.hpp"
#include "Parser.hpp"

/**
 * @brief		Creates map of nodes and group_2 element to
 *				index position of in MNA and RHS matrices
 *
 * @param		indexMap map<string, int>
 * @param		parser Parser
 *
 * @return		void
 */
void makeIndexMap(std::map<std::string, int> &indexMap, Parser &parser);

/**
 * @brief		Prints the MNA, x and RHS matrices
 *
 * @param		mna vector<vector<double>>
 * @param		indexmap map<string, int>
 * @param		rhs vector<double>
 *
 * @return		void
 */
void printMNAandRHS(std::vector<std::vector<double>> &mna,
                    std::map<std::string, int> &indexMap,
                    std::vector<double> &rhs);

/**
 * @brief		Creates graph from the vector for traversal
 *
 * @param[ref]	nodeMap map<string, shared_ptr<Node>>
 * @param		parser Parser
 *
 * @return		void
 */
void makeGraph(std::map<std::string, std::shared_ptr<Node>> &nodeMap,
               Parser &parser);

/**
 * @brief		Print the solution of x along with unknown variables
 *
 * @param   	indexMap map<string, int>
 * @param		X Eigen::MatrixXd
 *
 * @return		void
 */
void printxX(std::map<std::string, int> &indexMap, Eigen::MatrixXd &X);
