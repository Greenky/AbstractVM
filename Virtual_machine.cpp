/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Virtual_machine.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 18:16:54 by vmazurok          #+#    #+#             */
/*   Updated: 2019/02/22 16:08:19 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Virtual_machine.h"

//void Virtual_machine::push(Virtual_machine::types type, double value)
//{
//	my_stack.push_back(std::pair<double, types>(value, type));
//}

//void Virtual_machine::dump()
//{
//	for(int i = 0; i < my_stack.size(); i++)
//		std::cout << my_stack.at(i).first << std::endl;
//}
Virtual_machine::Virtual_machine() {
	exitProperly = false;
	output = "";
	errorOutput = "";
}

void Virtual_machine::readInstruction(std::string instruct, bool fromFile, int i) {

	std::cmatch res;
	std::regex comm("\\s*(push|assert|pop|dump|add|sub|mul|div|mod|print|exit)(\\s+.*)?");

	if (regex_match(instruct.c_str(), res, comm))
	{
		try {
			if (res[1] == "push")
				push(instruct, i);
			else if (res[1] == "assert")
				assert(instruct, i);
			else if (res[1] == "pop")
				pop(i);
			else if (res[1] == "dump")
				dump(i);
			else if (res[1] == "add")
				add(i);
			else if (res[1] == "sub")
				sub(i);
			else if (res[1] == "mul")
				mul(i);
			else if (res[1] == "div")
				div(i);
			else if (res[1] == "mod")
				mod(i);
			else if (res[1] == "print")
				print(i);
			else if (res[1] == "exit")
				exit(fromFile);
		}
		catch (AssertErrorException &e)
		{
			::exit(1);
		}
	}
	else
	{
		std::cerr << "Error in line " << i << ": An instruction is unknown" << std::endl;
		::exit(1);
	}

}

void Virtual_machine::push(std::string str, int i) {
    if (my_stack.size() == 0)
	    my_stack.push_back(parceOperand(str, i));
    else
        my_stack.insert(my_stack.begin(), parceOperand(str, i));
}

void Virtual_machine::assert(std::string str, int i){
    if (*my_stack.at(0) != *parceOperand(str, i)) {
    	throw AssertErrorException();
	}
}

void Virtual_machine::dump(int i) {
	if (my_stack.size() == 0) {
		//output.append("Error in line " + i + ": Dump on empty stack");
		std::cerr << "Error in line " << i << ": Dump on empty stack" << std::endl;
		::exit(6);
	}
	for (int i = 0; i < my_stack.size(); i++) {
		output.append(my_stack.at(i)->toString() + "\n");
	}
}

void Virtual_machine::pop(int i) {
	if (my_stack.size() == 0) {
        //output.append("Error in line " + i + ": Pop on empty stack");
		std::cerr << "Error in line " << i << ": Pop on empty stack" << std::endl;
        ::exit(6);
	} else {
	    my_stack.erase(my_stack.begin());
	}
}

void Virtual_machine::add(int i) {
	OperandFactory operandFactory;

	if (my_stack.size() < 2) {
		std::cerr << "Error in line " << i  << ": Adding error - stack size is too small" << std::endl;
		::exit(7);
	}

	const IOperand * new_oper = operandFactory.createOperand(
			std::max<eOperandType >(my_stack.at(0)->getType(), my_stack.at(1)->getType()),
			my_stack.at(0)->getValue() + my_stack.at(1)->getValue()
	);

	my_stack.erase(my_stack.begin(), my_stack.begin() + 2);
	my_stack.insert(my_stack.begin(), new_oper);
}

void Virtual_machine::sub(int i) {
	OperandFactory operandFactory;

	if (my_stack.size() < 2) {
		std::cerr << "Error in line " << i  << ": Subtracting error - stack size is too small" << std::endl;
		::exit(7);
	}
	const IOperand * new_oper = operandFactory.createOperand(
			std::max<eOperandType>(my_stack.at(0)->getType(), my_stack.at(1)->getType()),
			my_stack.at(1)->getValue() - my_stack.at(0)->getValue()
	);
	my_stack.erase(my_stack.begin(), my_stack.begin() + 2);
	my_stack.insert(my_stack.begin(), new_oper);
}

void Virtual_machine::mul(int i) {
	OperandFactory operandFactory;

	if (my_stack.size() < 2) {
		std::cerr << "Error in line " << i  << ": Multiplication error - stack size is too small" << std::endl;
		::exit(7);
	}

	const IOperand * new_oper = operandFactory.createOperand(
			std::max<eOperandType >(my_stack.at(0)->getType(), my_stack.at(1)->getType()),
			my_stack.at(0)->getValue() * my_stack.at(1)->getValue()
	);
	my_stack.erase(my_stack.begin(), my_stack.begin() + 2);
	my_stack.insert(my_stack.begin(), new_oper);
}

void Virtual_machine::div(int i) {
	OperandFactory operandFactory;

	if (my_stack.size() < 2) {
		std::cerr << "Error in line " << i  << ": Division error - stack size is too small" << std::endl;
		::exit(7);
	}
	else if (my_stack.at(0)->getValue() == 0) {
		std::cerr << "Error in line " << i  << ": Division by zero" << std::endl;
		::exit(7);
	}
	const IOperand * new_oper = operandFactory.createOperand(
			std::max<eOperandType >(my_stack.at(0)->getType(), my_stack.at(1)->getType()),
			my_stack.at(1)->getValue() / my_stack.at(0)->getValue()
	);
	my_stack.erase(my_stack.begin(), my_stack.begin() + 2);
	my_stack.insert(my_stack.begin(), new_oper);
}

void Virtual_machine::mod(int i) {
	OperandFactory operandFactory;

	if (my_stack.size() < 2) {
		std::cerr << "Error in line " << i  << ": Modulo error - stack size is too small" << std::endl;
		::exit(7);
	}
	else if (my_stack.at(0)->getValue() == 0) {
		std::cerr << "Error in line " << i  << ": Modulo by zero" << std::endl;
		::exit(7);
	}
	const IOperand * new_oper = operandFactory.createOperand(
			std::max<eOperandType >(my_stack.at(0)->getType(), my_stack.at(1)->getType()),
			std::fmod(my_stack.at(1)->getValue(), my_stack.at(0)->getValue())
	);
	my_stack.erase(my_stack.begin(), my_stack.begin() + 2);
	my_stack.insert(my_stack.begin(), new_oper);
}

void Virtual_machine::print(int i) {
	if (my_stack.at(0)->getType() == Int8) {
		std::cerr << "Error in line " << i  << ": Top element is not Int8" << std::endl;
		::exit(7);
	}
	std::cout << static_cast<char>(my_stack.at(0)->getValue()) << std::endl;
}

void Virtual_machine::exit(bool fromFile) {
	exitProperly = true;
	outputWork();
}

IOperand const *Virtual_machine::parceOperand(std::string value, int i) {
	OperandFactory operandFactory;
	std::regex num("\\s*(assert|push)\\s+(int8|int16|int32|float|double)\\(([-]?[0-9]+(\\.[0-9]+)?)\\)\\s*");
	std::cmatch res;

	if (regex_match(value.c_str(), res, num)) {
		if  (res[2] == "int8") {
			if (res[4] != "") {
				std::cerr << "Error in line " << i << ": Invalid Integer number format" << std::endl;
				::exit(1);
			}
			return (operandFactory.createOperand(Int8, res[3]));
		}
		else if (res[2] == "int16") {
			if (res[4] != "") {
				std::cerr << "Error in line " << i << ": Invalid Integer number format" << std::endl;
				::exit(1);
			}
			return (operandFactory.createOperand(Int16, res[3]));
		}
		else if (res[2] == "int32") {
			if (res[4] != "") {
				std::cerr << "Error in line " << i << ": Invalid Integer number format" << std::endl;
				::exit(1);
			}
			return (operandFactory.createOperand(Int32, res[3]));
		}
		else if (res[2] == "float") {
			if (res[4] == "") {
				std::cerr << "Error in line " << i << ": Invalid float number format" << std::endl;
				::exit(1);
			}
			return (operandFactory.createOperand(Float, res[3]));
		}
		else {
			if (res[4] == "") {
				std::cerr << "Error in line " << i << ": Invalid double number format" << std::endl;
				::exit(1);
			}
			return (operandFactory.createOperand(Double, res[3]));
		}
	}
	else {
		std::cerr << "Error in line " << i << ": Invalid type or value is not numeric" << std::endl;
		::exit(1);
	}
}

void Virtual_machine::outputWork(void) {
	if (exitProperly)
		std::cout << output;
	else
		std::cerr << "Error, no exit function" << std::endl;

//	if (!exitProperly)
//		output.append("Error, no exit function\n");
//	std::cout << output;

	::exit(0);
}

Virtual_machine::StackIsToSmallException::StackIsToSmallException() {
	;
}

Virtual_machine::StackIsToSmallException::~StackIsToSmallException() {
	;
}

Virtual_machine::StackIsToSmallException::StackIsToSmallException(Virtual_machine::StackIsToSmallException &obj) {
	*this = obj;
	return ;
}

Virtual_machine::StackIsToSmallException & Virtual_machine::StackIsToSmallException::operator=(const Virtual_machine::StackIsToSmallException &obj) {
	(void)obj;
	return *this;
}

const char *Virtual_machine::StackIsToSmallException::what() const throw() {
	return "Stack is too small for this action";
}

Virtual_machine::NoExitFunctionException::NoExitFunctionException() {
	;
}

Virtual_machine::NoExitFunctionException::NoExitFunctionException(Virtual_machine::NoExitFunctionException &obj) {
	*this = obj;
	return ;
}

Virtual_machine::NoExitFunctionException & Virtual_machine::NoExitFunctionException::operator=(const Virtual_machine::NoExitFunctionException &obj) {
	(void)obj;
	return *this;
}

const char *Virtual_machine::NoExitFunctionException::what() const throw(){
	return "Error: No exit function";
}

Virtual_machine::NoExitFunctionException::~NoExitFunctionException() {
	;
}

Virtual_machine::InvalidNumberFormatException::InvalidNumberFormatException() {
	;
}

Virtual_machine::InvalidNumberFormatException::InvalidNumberFormatException(Virtual_machine::InvalidNumberFormatException &obj) {
	*this = obj;
	return ;
}

Virtual_machine::InvalidNumberFormatException &Virtual_machine::InvalidNumberFormatException::operator=(const Virtual_machine::InvalidNumberFormatException &obj) {
	(void)obj;
	return *this;
}

const char *Virtual_machine::InvalidNumberFormatException::what() const throw(){
	return "Invalid number format";
}

Virtual_machine::InvalidNumberFormatException::~InvalidNumberFormatException() {
	;
}

Virtual_machine::AssertErrorException::AssertErrorException() {
	;
}

Virtual_machine::AssertErrorException::AssertErrorException(Virtual_machine::AssertErrorException &obj) {
	*this = obj;
	return ;
}

Virtual_machine::AssertErrorException &Virtual_machine::AssertErrorException::operator=(const Virtual_machine::AssertErrorException &obj) {
	(void)obj;
	return *this;
}

const char *Virtual_machine::AssertErrorException::what() const throw(){
	return "Assert is failed";
}

Virtual_machine::AssertErrorException::~AssertErrorException() {
	;
}
