#include <iostream>
#include<string>
#include <fstream>

struct Fraction {
	int numerator;
	int denominator;
};

struct Equation {
	Fraction expression1;
	Fraction expression2;
	std::string operation;
};

Fraction fractionAddition(Fraction fraction1 , Fraction fraction2) {
	fraction1.numerator *= fraction2.denominator;
	fraction2.numerator *= fraction1.denominator;
	int newDenominator = fraction1.denominator * fraction2.denominator;
	int newNumerator = fraction1.numerator + fraction2.numerator;

	return { newNumerator, newDenominator };
}

Fraction fractionSubtraction(Fraction fraction1, Fraction fraction2) {
	fraction1.numerator *= fraction2.denominator;
	fraction2.numerator *= fraction1.denominator;
	int newDenominator = fraction1.denominator * fraction2.denominator;
	int newNumerator = fraction1.numerator - fraction2.numerator;

	return { newNumerator, newDenominator };
}

Fraction fractionMultiplaction(Fraction fraction1, Fraction fraction2) {
	int newNumberator = fraction1.numerator * fraction2.numerator;
	int newDenominator = fraction1.denominator * fraction2.denominator;

	return { newNumberator, newDenominator };
}

Fraction fractionDivision(Fraction fraction1, Fraction fraction2) {
	int newNumberator = fraction1.numerator * fraction2.denominator;
	int newDenominator = fraction1.denominator * fraction2.numerator;

	return { newNumberator,newDenominator };
}

int gcd(int a, int b) {
	return abs(b) == 0 ? abs(a) : gcd(abs(b), abs(a) % b);	
}

Fraction reduceFraction(Fraction fraction) {
	int GCD = gcd(fraction.numerator, fraction.denominator);
	fraction.denominator = fraction.denominator / GCD;
	fraction.numerator = fraction.numerator / GCD;

	return fraction;
}

std::string fractionToString(Fraction fraction) {
	std::string fractionAsString;
	fractionAsString = std::to_string(fraction.numerator) + "/" + std::to_string(fraction.denominator);

	return fractionAsString;

}

Fraction readFraction(std::string input) {
	try {
		std::string delimiter = "/";
		size_t pos = 0;
		int holder;
		std::string token;
		while ((pos = input.find(delimiter)) != std::string::npos) {
			token = input.substr(0, pos);
			input.erase(0, pos + delimiter.length());
			holder = std::stoi(token);

		}
		int numerator = holder;
		int denominator = std::stoi(input);
		return { numerator, denominator };
	}
	catch (std::invalid_argument) {
	throw "invalid fraction format";
	}
}






Fraction doMath(Equation equation) {
	Fraction answer;
	if (equation.operation == "+") {
		answer = fractionAddition(equation.expression1, equation.expression2);
	}
	if (equation.operation == "-") {
		answer = fractionSubtraction(equation.expression1, equation.expression2);
	}
	if (equation.operation == "*") {
		answer = fractionMultiplaction(equation.expression1, equation.expression2);
	}
	if (equation.operation == "/") {
		answer = fractionDivision(equation.expression1, equation.expression2);
	}
	return answer;
}

Equation asdf(std::istream& input){
	Fraction fraction1, fraction2;
	std::string operation, stringHolder;
	input >> stringHolder;
	fraction1 = readFraction(stringHolder);
	input >> operation;
	input >> stringHolder;
	fraction2 = readFraction(stringHolder);
	return { fraction1, fraction2, operation };
}

void writeToFile(std::string output, std::string fileName) {
	std::ofstream my_output_file(fileName);
	my_output_file << output << std::endl;
	my_output_file.close();
}


int main() {

	std::ifstream my_input_file("inputSheet.txt");
	Fraction fraction1, fraction2;
	std::string inputHolder, answer, operation;
	Equation equation;
	while (my_input_file.good()) {
		if (!my_input_file.eof()) {
			equation = asdf(my_input_file);
			answer = fractionToString(reduceFraction(doMath(equation)));
			writeToFile(answer, "answerSheet.txt");
		}
		my_input_file.close();
		return 0;
	}
}