#include "Utilities.h"

double Utilities::CalculateGrams(std::vector<std::string> values) {
    double bac = atof(values.at(0).c_str()); // Blood alcohol concentration
    double w = atof(values.at(1).c_str()); // Body weight (kg)
    double h = atof(values.at(2).c_str()) / 100; // Height (m)
    int a = std::stoi(values.at(3).c_str()); // Age (years)
    bool gender = std::stoi(values.at(4).c_str()); // Gender (male/female)
    int elimRate = 10; // Alcohol elimination rate (g/h)
    double time = atof(values.at(5).c_str()); // Time to reach target BAC
    double r; // Widmark factor (average)

    // Total body water (TBW) formulae
    double rWidmark;
    double rWatson;
    double rForrest;
    double rSeidl;
    double rUlrich;

    // Calculate R factor
    if (gender) { // Subject is male
        // Set formulae
        rWidmark = 0.68;
        rWatson = 0.39834 + ((12.725 * h) / w) - ((0.11275 * a) / w) + (2.8993 / w);
        rForrest = 1.0178 - ((0.012127 * w) / (h * h));
        rSeidl = 0.31608 - (0.004821 * w) + (0.4632 * (h));
        rUlrich = 0.715 - (0.00462 * w) + (0.22 * h);

        // Average together to produce r value
        r = 0.2 * (rWidmark + rWatson + rForrest + rSeidl + rUlrich);

    }
    else { // Subject is female
     // Set formulae
        rWidmark = 0.55;
        rWatson = 0.29218 + ((12.666 * h) / w) - (2.4846 / w);
        rForrest = 0.8736 - ((0.0124 * w) / (h * h));
        rSeidl = 0.31223 - (0.006446 * w) + (0.4466 * (h));
        
        // Average together to produce r value
        r = 0.25 * (rWidmark + rWatson + rForrest + rSeidl);
    }

    // Substitute into Widmark's formula and return
    return (bac * 10) * (r * w) + (elimRate * time);
}

int Utilities::CalculateBeverage(double amountGrams, double concentration) {
    // Return mililitres of drink calculated with the specific gravity of alcohol (0.7935)
    return round((amountGrams / concentration) / 0.7935);
}

int Utilities::Authenticate(std::string username, std::string password) {

    return 1.0;
}