/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TypeClass.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 16:33:46 by vmazurok          #+#    #+#             */
/*   Updated: 2019/02/22 19:25:57 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPECLASS_H
#define TYPECLASS_H

#include "IOperand.h"
#include "OperandFactory.h"

template <eOperandType Type>
class TypeClass: public IOperand{
public:
	TypeClass(std::string const &value)
	{
		type = Type;
		try {
			if (type < Float)
				this->value = std::stoll(value);
			else
				this->value = std::stold(value);
			parceLimits();
		}
		catch (OverflowException &e){
			std::cerr << e.what() << std::endl;
			exit(5);
		}
		catch (UnderflowException &e){
			std::cerr << e.what() << std::endl;
			exit(5);
		}
	}

	TypeClass(long double value)
	{
		type = Type;
		try {
			this->value = value;
			parceLimits();
		}
		catch (OverflowException &e){
			std::cerr << e.what() << std::endl;
			exit(5);
		}
		catch (UnderflowException &e){
			std::cerr << e.what() << std::endl;
			exit(5);
		}
	}

	long double getValue(void) const
	{
		return value;
	}

	int getPrecision(void) const
	{
		return type;
	}

	eOperandType getType(void) const
	{
		return type;
	}

	IOperand const *operator+(IOperand const &rhs) const
	{
		(void)rhs;
		return nullptr;
	}

	IOperand const *operator-(IOperand const &rhs) const
	{
		(void)rhs;
		return nullptr;
	}

	IOperand const *operator*(IOperand const &rhs) const
	{
		(void)rhs;
		return nullptr;
	}

	IOperand const *operator/(IOperand const &rhs) const
	{
		(void)rhs;
		return nullptr;
	}

	IOperand const *operator%(IOperand const &rhs) const
	{
		(void)rhs;
		return nullptr;
	}

	TypeClass &operator=(TypeClass const &rhs)
	{
		this->value = rhs.value;
		this->type = rhs.type;
		return *this;
	}

	bool operator==(IOperand const &rhs) const
	{
		if (value == rhs.getValue() && type == rhs.getType())
			return true;
		return false;
	}

	bool operator!=(IOperand const &rhs) const
	{
		if (operator==(rhs))
			return false;
		return true;
	}

	std::string const &toString(void) const
	{
		std::string const *s;

		if (type < Float)
			s = new std::string(std::to_string(static_cast<int>(value)));
		else {
			//std::string raw(std::to_string(value));
			//raw.erase(raw.find('.') + 3, raw.size());
			s = new std::string(std::to_string(value));
		}
		return *s;
	}

	class OverflowException : public std::exception{
	public:
		OverflowException(void)
		{
			return ;
		}
		OverflowException(OverflowException const &obj)
		{
			*this = obj;
			return ;
		}
		OverflowException &operator=(OverflowException const &obj)
		{
			(void)obj;
			return *this;
		}
		virtual const char* what() const throw()
		{
			return "Overflow of the value";
		}
	};

	class UnderflowException : public std::exception{
	public:
		UnderflowException(void)
		{
			return ;
		}
		UnderflowException(UnderflowException const &obj)
		{
			*this = obj;
			return ;
		}
		UnderflowException &operator=(UnderflowException const &obj)
		{
			(void)obj;
			return *this;
		}
		virtual const char* what() const throw()
		{
			return "Underflow of the value";
		}
	};

private:
	long double value;
	eOperandType type;

	void parceLimits(void)
	{
		if (type < Float) {
			if (type == Int8) {
				if ( this->value > CHAR_MAX || this->value < CHAR_MIN) {
					throw OverflowException();
				}
			} else if (type == Int16) {
				if (this->value > SHRT_MAX || this->value < SHRT_MIN) {
					throw OverflowException();
				}
			} else {
				if (this->value > INT_MAX || this->value < INT_MIN) {
					throw OverflowException();
				}
			}
		} else {
			if (type == Float) {
				if (std::abs(this->value) > std::numeric_limits<float>::max()) {
					throw OverflowException();
				} else if (this->value != 0 && std::abs(this->value) < std::numeric_limits<float>::min()) {
					throw UnderflowException();
				}
			} else {
				if (std::abs(this->value) > std::numeric_limits<double>::max()) {
					throw OverflowException();
				} else if (this->value != 0 && std::abs(this->value) < std::numeric_limits<double>::min()) {
					throw UnderflowException();
				}
			}
		}
	}

};

#endif
