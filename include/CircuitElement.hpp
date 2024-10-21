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
 * @file CircuitElement.hpp
 *
 * @brief Contains the definition of the CircuitElement struct
 */

#pragma once

#include <memory>
#include <string>

/** @enum Component
 *
 * Specifies the type of element that are supported by CircuitElement
 * */
enum Component
{
    V,  /**<  Voltage source */
    I,  /**<  Current source */
    R,  /**<  Resistor */
    Ic, /**<  Current controlled current source */
    Vc, /**<  Voltage controlled voltage source */
    C,  /**<  Capacitor */
    L,  /**< Inductor */

};

/** @enum Gruoup
 *
 * Specifies the group of element that are supported by CircuitElement
 * */
enum Group
{
    G1 /**< Group 1: the currents for these elements need to be eliminated */,
    G2 /** Group 2: Elements not in G1. Other methods must be employed*/
};

/** @enum ControlVariable
 *
 * @brief Specifies the controlling variable for controlled sources
 * */
enum ControlVariable
{
    none, /**<  No controlling variable */
    v,    /**<  Voltage */
    i     /**< Current */
};

/** @struct CircuitElement
 *
 * @brief Represents the properties of any element in the circuit
 * */

struct CircuitElement
{
    std::string name;  /**< Name of the element*/
    Component type;    /**< Specifies the type of the circuit element  */
    std::string nodeA; /**< Starting node */
    std::string nodeB; /**< Ending node */
    Group group;       /**< Specifier if it belongs to  Group 1 or Group 2   */
    double value; /**< Value of the element (or scale factor if it is controlled
                     source)*/
    ControlVariable controlling_variable; /**< Only for controlled sources,
                                     variable that the element depends on  */
    std::shared_ptr<CircuitElement>
        controlling_element; /**< Only for controlled sources, element whose
                                value that the current element depends on  */
    bool processed;          /**< Flag value to know whether it is processed */
};
