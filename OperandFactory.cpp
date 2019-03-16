/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 19:04:33 by vmazurok          #+#    #+#             */
/*   Updated: 2019/02/22 19:06:24 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandFactory.h"

IOperand const *OperandFactory::createOperand(eOperandType type, long double value) const {

	typedef IOperand const* (OperandFactory::*Functions)(long double value) const;
	Functions func[5] = {
			&OperandFactory::createInt8,
			&OperandFactory::createInt16,
			&OperandFactory::createInt32,
			&OperandFactory::createFloat,
			&OperandFactory::createDouble
	};

	return (this->*(func[type]))(value);
}

IOperand const *OperandFactory::createOperand(eOperandType type, std::string const & value) const {

	typedef IOperand const* (OperandFactory::*Functions)(std::string const & value) const;
	Functions func[5] = {
			&OperandFactory::createInt8,
			&OperandFactory::createInt16,
			&OperandFactory::createInt32,
			&OperandFactory::createFloat,
			&OperandFactory::createDouble
	};

	return (this->*(func[type]))(value);
}

IOperand const *OperandFactory::createInt8(std::string const &value) const {
	IOperand const *newOperand = new TypeClass<Int8>(value);
	return newOperand;
}

IOperand const *OperandFactory::createInt8(long double value) const {
	IOperand *newOperand = new TypeClass<Int8>(value);
	return newOperand;
}

IOperand const *OperandFactory::createInt16(std::string const &value) const {
	IOperand const *newOperand = new TypeClass<Int16>(value);
	return newOperand;
}

IOperand const *OperandFactory::createInt16(long double value) const {
	IOperand const *newOperand = new TypeClass<Int16>(value);
	return newOperand;
}

IOperand const *OperandFactory::createInt32(std::string const &value) const {
	IOperand const *newOperand = new TypeClass<Int32>(value);
	return newOperand;
}

IOperand const *OperandFactory::createInt32(long double value) const {
	IOperand const *newOperand = new TypeClass<Int32>(value);
	return newOperand;
}

IOperand const *OperandFactory::createFloat(std::string const &value) const {
	IOperand const *newOperand = new TypeClass<Float>(value);
	return newOperand;
}

IOperand const *OperandFactory::createFloat(long double value) const {
	IOperand const *newOperand = new TypeClass<Float>(value);
	return newOperand;
}

IOperand const *OperandFactory::createDouble(std::string const &value) const {
	IOperand const *newOperand = new TypeClass<Double>(value);
	return newOperand;
}

IOperand const *OperandFactory::createDouble(long double value) const {
	IOperand const *newOperand = new TypeClass<Double>(value);
	return newOperand;
}
