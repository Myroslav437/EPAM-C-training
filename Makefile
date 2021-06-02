all: build clean

build: main.o Calculator.o CalculationStrategy.o RPN_converter.o RPN_evaluator.o RPN_strategy.o
	g++ -pthread main.o Calculator.o CalculationStrategy.o RPN_converter.o RPN_evaluator.o RPN_strategy.o -o Calc

main.o: main.cpp
	g++ -pthread -c main.cpp

Calculator.o: 
	g++ -c Calculator/Calculator.cpp

CalculationStrategy.o: 
	g++ -c Calculator/Strategies/CalculationStrategy.cpp

RPN_converter.o:
	g++ -c Calculator/Strategies/RPN_strategy/RPN_converter.cpp

RPN_evaluator.o:
	g++ -c Calculator/Strategies/RPN_strategy/RPN_evaluator.cpp

RPN_strategy.o:
	g++ -c Calculator/Strategies/RPN_strategy/RPN_strategy.cpp

clean:
	find . -name "*.o" -type f -delete