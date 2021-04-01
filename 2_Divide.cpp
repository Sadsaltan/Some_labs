

#include <iostream>
#include <bitset>

int main()
{
    std::cout << "Hello World!\n";
	unsigned int dividend, divisor;
	unsigned long reminder_left;
	std::cout << "Please enter dividend\n";
	std::cin >> dividend;
	std::cout << "Please enter divisor\n";
	std::cin >> divisor;

	std::bitset<64> Reminder(dividend);
	std::bitset<64> Divisor_64(divisor);
	Divisor_64 <<= 32;

	Reminder <<= 1;
	std::cout << "Reminder register: " << Reminder.to_string().substr(0, 32) + " " + Reminder.to_string().substr(32, 32) << '\n';
	reminder_left = stoul(Reminder.to_string().substr(0, 32), 0, 2);
	for (int count = 1; count != 33; count++)
	{
		std::cout << "Repetition " << count << '\n';
		//check left part of reminder and divisor
		std::cout << "Reminder_left: " << Reminder.to_string().substr(0, 32) << '\n';
		std::cout << "Divisor      : " << Divisor_64.to_string().substr(0, 32) << '\n';
		reminder_left = stoul(Reminder.to_string().substr(0,32), 0, 2);
		if (reminder_left >= divisor)
		{
			std::cout << "Set quotient bit to 1 \n";
			unsigned long long Reminder_update = stoull(Reminder.to_string(), 0, 2) - stoull(Divisor_64.to_string(), 0, 2);
			Reminder = std::bitset<64>(Reminder_update);
			Reminder <<= 1;
			Reminder[0] = 1;
		}
		else
		{
			std::cout << "Set quotient bit to 0 \n";
			Reminder <<= 1;
			Reminder[0] = 0;
		}
		std::cout << "Reminder register: "<< Reminder.to_string().substr(0, 32)+ " " + Reminder.to_string().substr(32, 32) << '\n';
		
	}
	std::cout << "\n\nFinal result: " << '\n';
	std::cout << "\n\nQuotient part " << Reminder.to_string().substr(32, 32) << '\n';
	unsigned long Quotient = stoul(Reminder.to_string().substr(32, 32), 0, 2);
	std::cout << "\nQuotient = " << Quotient << '\n';
	std::cout << "\nReminder part " << Reminder.to_string().substr(0, 31).insert(0, 1, '0') << '\n';
	unsigned long Reminder_result = stoul(Reminder.to_string().substr(0, 31).insert(0, 1, '0'), 0, 2);
	std::cout << "\nReminder = " << Reminder_result << '\n';

}

