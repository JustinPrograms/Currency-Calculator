#include <iostream>

#include "cpp-httplib.h"
#include "json.h"

using json = nlohmann::json;

// Referncing &domain and &path to save memory
auto get(const std::string &domain, const std::string &path) -> json {
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
    std::cout << "Enter an amount and the currency of it (eg. 10 EUR)" << std::endl;
    std::cin >> amount >> currency;
    return convert(currency, amount);
}

int main()
{

    // Init variables
    double sumInCAD = 0;
    double input;
    unsigned int more;



    // Getting number of European euros
    std::cout << "Enter number of European euros: ";
    std::cin >> input;
    sumInCAD += convert("EUR", input);

    // Getting number of Russian euros
    std::cout << "Enter number of Russian rubles: ";
    std::cin >> input;
    sumInCAD += convert("RUB", input);

    // Getting number of Singapore dollars
    std::cout << "Enter number of Singapore dollars: ";
    std::cin >> input;
    sumInCAD += convert("SGD", input);

    // Getting number of Philppine pesos
    std::cout << "Enter number of Philppine pesos: ";
    std::cin >> input;
    sumInCAD += convert("PHP", input);

    // Getting number of Mexican pesos
    std::cout << "Enter number of Mexcian pesos: ";
    std::cin >> input;
    sumInCAD += convert("MXN", input);

    // Getting number of Saudi Arabia Riyals
    std::cout << "Enter number of Saudi Arabia Riyals: ";
    std::cin >> input;
    sumInCAD += convert("SAR", input);

    // Getting number of Solomon Islands Dollar
    std::cout << "Enter number of Solomon Islands Dollars: ";
    std::cin >> input;
    sumInCAD += convert("SBD", input);

    // Getting number of Taiwan New Dollar
    std::cout << "Enter number of Taiwan New Dollars: ";
    std::cin >> input;
    sumInCAD += convert("TWD", input);

    // Getting number of Ukraine Hryvnia
    std::cout << "Enter number of Ukraine Hryvnias ";
    std::cin >> input;
    sumInCAD += convert("UAH", input);

    // Getting number of United Kingdom Pound
    std::cout << "Enter number of United Kingdom Pounds ";
    std::cin >> input;
    sumInCAD += convert("GBP", input);

    // Getting how many more curriences the user wants to convert
    std::cout << "How many more different currencies do you have? ";
    std::cin >> more;

    for (int i = 0; i < more; i++) {
        sumInCAD += get_input();
    }



    /* 
     * Printing out the final value in CAD
     * Setting the final value to two decimal places
     */
    
    std::cout << std::fixed << std::setprecision(2) << "CAD = $" << sumInCAD;

    return 0;
}

