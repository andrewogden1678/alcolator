#include "../database/Database.h"


///
/// App Utilities
///
class Utilities {

    public:
        // Calculate amount in grams
        static double CalculateGrams(std::vector<std::string> values);

        // Calculate amount as beverage
        static int CalculateBeverage(double amountGrams, double concentration);

        // Authenticate user
        static bool Authenticate(std::string password, std::string hash);

        // Hash password
        static std::string Hash(std::string password);
};