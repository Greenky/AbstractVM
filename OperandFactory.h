/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 19:04:26 by vmazurok          #+#    #+#             */
/*   Updated: 2019/02/22 17:01:28 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERANDFACTORY_H
#define OPERANDFACTORY_H
#include "IOperand.h"
#include "TypeClass.h"

class OperandFactory{
public:
	IOperand const * createOperand( eOperandType type, std::string const & value ) const;
	IOperand const * createOperand( eOperandType type, long double value ) const;

private:
	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt8( long double value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt16( long double value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createInt32( long double value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createFloat( long double value ) const;
	IOperand const * createDouble( std::string const & value ) const;
	IOperand const * createDouble( long double value ) const;
};


#endif
