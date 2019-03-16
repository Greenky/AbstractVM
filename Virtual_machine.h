/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 18:16:46 by vmazurok          #+#    #+#             */
/*   Updated: 2019/02/20 18:35:15 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H
#include <vector>
#include <iostream>
#include "IOperand.h"
#include "OperandFactory.h"

class Virtual_machine {
public:
	Virtual_machine();
	void readInstruction(std::string instruct, bool fromFile, int i);
	void outputWork(void);
    IOperand const *parceOperand(std::string str, int i);
	void push(std::string value, int i);
	void assert(std::string value, int i);
	void dump(int i);
	void pop(int i);
	void add(int i);
	void sub(int i);
	void mul(int i);
	void div(int i);
	void mod(int i);
	void print(int i);
	void exit(bool fromFile);

	class StackIsToSmallException : public std::exception {
    public:
        StackIsToSmallException();
        StackIsToSmallException(StackIsToSmallException &obj);
        StackIsToSmallException &operator=(StackIsToSmallException const &obj);
        virtual const char* what() const throw();
        virtual ~StackIsToSmallException();
    };

    class NoExitFunctionException : public std::exception {
    public:
        NoExitFunctionException();
        NoExitFunctionException(NoExitFunctionException &obj);
        NoExitFunctionException &operator=(NoExitFunctionException const &obj);
        virtual const char* what() const throw();
        virtual ~NoExitFunctionException();
    };

    class InvalidNumberFormatException : public std::exception {
    public:
        InvalidNumberFormatException();
        InvalidNumberFormatException(InvalidNumberFormatException &obj);
        InvalidNumberFormatException &operator=(InvalidNumberFormatException const &obj);
        virtual const char* what() const throw();
        virtual ~InvalidNumberFormatException();
    };

    class AssertErrorException : public std::exception {
    public:
        AssertErrorException();
        AssertErrorException(AssertErrorException &obj);
        AssertErrorException &operator=(AssertErrorException const &obj);
        virtual const char* what() const throw();
        virtual ~AssertErrorException();

    };

private:
	bool exitProperly;
	std::vector<IOperand const *> my_stack;
	std::string output;
	std::string errorOutput;

};


#endif
