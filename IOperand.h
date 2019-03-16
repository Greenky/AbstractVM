/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 19:06:44 by vmazurok          #+#    #+#             */
/*   Updated: 2019/02/22 17:42:53 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERAND_H
#define IOPERAND_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <cmath>
#include <float.h>

enum eOperandType
{
    Int8,
    Int16,
    Int32,
    Float,
    Double
};

class IOperand {
public:
	virtual int getPrecision( void ) const = 0; // Precision of the type of the instance
	virtual eOperandType getType( void ) const = 0; // Type of the instance
	virtual IOperand const * operator+( IOperand const & rhs ) const = 0; // Sum
	virtual IOperand const * operator-( IOperand const & rhs ) const = 0; // Difference
	virtual IOperand const * operator*( IOperand const & rhs ) const = 0; // Product
	virtual IOperand const * operator/( IOperand const & rhs ) const = 0; // Quotient
	virtual IOperand const * operator%( IOperand const & rhs ) const = 0; // Modulo
    virtual bool operator==( IOperand const & rhs ) const = 0; // Equal
    virtual bool operator!=( IOperand const & rhs ) const = 0; // Not equal
	virtual std::string const & toString( void ) const = 0; // String representation of the instance
	virtual long double getValue( void ) const = 0;
	virtual ~IOperand( void ) {}
};


#endif
