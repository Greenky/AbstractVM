/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 18:16:51 by vmazurok          #+#    #+#             */
/*   Updated: 2019/02/22 15:46:32 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Virtual_machine.h"
#include "OperandFactory.h"

int main(int argc, char** argv)
{
//	std::cmatch res;
//	std::string str = "push int8(-412)";
//	std::regex rx("((push|assert)[\\s]+(int8)\\(([-]?[0-9]+)\\))");
//	if (regex_match(str.c_str(), res, rx))
//		std::cout << res[3] << std::endl;
//
//	Virtual_machine vm;
//
//	vm.push(Virtual_machine::int8, 2);
//	vm.push(Virtual_machine::float_vm, 14);
//	vm.push(Virtual_machine::int16, 15);
//
//	vm.dump();

//	std::cerr << std::numeric_limits<float>::max() << "  " << std::numeric_limits<float>::min() << std::endl;

	Virtual_machine VM;
	std::ifstream file;
	std::string str;
	std::string instructions;
	std::cmatch res;
	int i = 0;

	if (argc > 1) {
		file.open(argv[1]);
		if (!file.is_open())
		{
			std::cerr << "Error opening file" << std::endl;
			exit(1);
		}
	}

	while (std::getline(file.is_open() ? file : std::cin, str))
	{
		if (!file.is_open() && str == ";;")
			break ;
		while (regex_match(str.c_str(), res, std::regex("(.*);(.*)")))
			str.erase(res[1].length(), str.length());
		if (str == "" || regex_match(str.c_str(), res, std::regex("\\s*")))
			continue ;
		else
			instructions.append(str + "\n");
	}
//
//	std::cout << "-----------------------------------" << std::endl;
//	std::cout << instructions << std::endl;
//	std::cout << "-----------------------------------" << std::endl;
//	std::cout << "VM output:\n";
	while (instructions.length() != 0)
	{
		i++;
		str = instructions.substr(0, instructions.find('\n'));
		instructions.erase(0, str.length() + 1);
		VM.readInstruction(str, file.is_open(), i);
	}
	VM.outputWork();
	return (0);
}