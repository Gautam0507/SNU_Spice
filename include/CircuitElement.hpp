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
#include <string>

/** @enum Component
 *
 * Specifies the type of element that are supported by CircuitElement
 * */
enum Component {
    V,  /**<  Voltage source */
    I,  /**<  Current source */
    R,  /**<  Resistor */
    Ic, /**<  Current controlled current source */
    Vc  /**<  Voltage controlled voltage source */
};

/** @enum Gruoup
 * Specifies the group of element that are supported by CircuitElement
 * */
enum Group { G1, G2 };  // Groups element based on output required

/** \enum  Specifies the controlling variable for controlled sources */
enum ControlVariable {
    none, /**<  No controlling variable */
    v,    /**<  Voltage */
    i     /**< Current */
};

struct CircuitElement
{
    std::string name;  /**< Name of the element*/
    Component type;    /**< Type of the element */
    std::string nodeA; /**< Starting node */
    std::string nodeB; /**< Ending node */
    Group group;       /**< Group of the element */
    double value; /**< Value of the element (or scale factor if it is controlled
                     source*/
    ControlVariable controlling_variable; /**< Only for controlled sources,
                                     variable that controls the source */
    std::shared_ptr<CircuitElement>
        controlling_element; /**< Only for controlled sources, element that
                                controls the source */
    bool processed;          /**< Flag value to know whether it is processed */
};
