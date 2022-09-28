#include <iostream>

#include "cpp-httplib.h"
#include "json.h"

using json = nlohmann::json;

// Referncing &domain and &path to save memory
auto get(const std::string& domain, const std::string& path) -> json {
	// @return json

	auto cli = httplib::Client(domain);
	return json::parse(cli.Get(path)->body);
}

// Gets the currency symbol and the amount 
auto convert(const std::string& from, double amount) -> double {
	// @return double

	if (amount <= 0)
		return 0;
	return get("http://api.exchangerate.host",
		"/convert?"
		"from=" + from +
		"&to=CAD&amount=" +
		std::to_string(amount))["result"];
}


auto get_input() -> double {
	// @return double

	double amount;
	std::string currency;
	std::cout << "\nEnter an amount and the currency of it (eg. 10 EUR)" << std::endl;
	std::cin >> amount >> currency;
	return convert(currency, amount);
}

int main()
{

	// Init variables
	double sumInCAD = 0;


	while (true) {
		sumInCAD += get_input();
		std::cout << std::fixed << std::setprecision(2) << "\tCAD = $" << sumInCAD;
	}

	return 0;
}

