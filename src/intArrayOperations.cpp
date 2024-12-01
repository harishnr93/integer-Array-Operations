"""
Date: 29.Nov.2024
Author: Harish Natarajan Ravi
Email: harrish.nr@gmail.com
"""

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <limits>
#include <ranges>

class IntArrProcessor {
public:
    enum class OrderPreservation {
        ORIGINAL,    // 'o' - Preserve original order
        ASCENDING,   // 'a' - Sort in ascending order
        DESCENDING   // 'd' - Sort in descending order
    };

    static std::string processInt(const std::string& in, OrderPreservation orderType = OrderPreservation::ORIGINAL) {
        // Handle empty input case
        if (in.empty()) {
            return "0; 0; 0";
        }

        // Parse input string into vector of integers
        std::vector<int> numbers = parseInput(in);
        
        // Count occurrences of each number
        std::unordered_map<int, int> countMap;
        for (int num : numbers) {
            countMap[num]++;
        }

        // Find duplicates and unique order
        std::vector<int> duplicates;
        std::vector<int> uniqueOrder = preserveUniqueOrder(numbers, orderType);
        
        // Count duplicates
        int duplicateCount = 0;
        int lowestDuplicate = std::numeric_limits<int>::max();
        int highestDuplicate = std::numeric_limits<int>::min();

        for (int num : numbers) {
            if (countMap[num] > 1) {
                // Track duplicates
                if (std::find(duplicates.begin(), duplicates.end(), num) == duplicates.end()) {
                    duplicates.push_back(num);
                    duplicateCount++;
                    
                    // Update lowest and highest duplicates
                    lowestDuplicate = std::min(lowestDuplicate, num);
                    highestDuplicate = std::max(highestDuplicate, num);
                }
            }
        }

        // Handle no duplicates case
        if (duplicateCount == 0) {
            lowestDuplicate = 0;
            highestDuplicate = 0;
        }

        // Construct output string
        std::stringstream result;
        result << duplicateCount << "; ";
        result << (duplicateCount > 0 ? lowestDuplicate : 0) << "; ";
        result << (duplicateCount > 0 ? highestDuplicate : 0) << "; ";

        // Add unique order numbers
        for (size_t i = 0; i < uniqueOrder.size(); ++i) {
            result << uniqueOrder[i];
            if (i < uniqueOrder.size() - 1) {
                result << "; ";
            }
        }

        return result.str();
    }

private:
    static std::vector<int> parseInput(const std::string& in) {
        std::vector<int> numbers;
        std::stringstream ss(in);
        std::string token;

        while (std::getline(ss, token, ';')) {
            // Trim whitespace
            token.erase(0, token.find_first_not_of(" "));
            token.erase(token.find_last_not_of(" ") + 1);

            if (!token.empty()) {
                numbers.push_back(std::stoi(token));
            }
        }

        return numbers;
    }

    static std::vector<int> preserveUniqueOrder(const std::vector<int>& numbers, OrderPreservation orderType) {
        std::vector<int> uniqueOrder;
        std::unordered_map<int, bool> seen;

        // Collect unique numbers in original order
        for (int num : numbers) {
            if (!seen[num]) {
                uniqueOrder.push_back(num);
                seen[num] = true;
            }
        }

        // Apply sorting based on order type
        switch (orderType) {
            case OrderPreservation::ORIGINAL:
                // No additional sorting needed
                break;
            case OrderPreservation::ASCENDING:
                std::sort(uniqueOrder.begin(), uniqueOrder.end());
                break;
            case OrderPreservation::DESCENDING:
                std::sort(uniqueOrder.begin(), uniqueOrder.end(), std::greater<int>());
                break;
        }

        return uniqueOrder;
    }
};

// Main function updated to handle command-line input and order type
int main(int argc, char* argv[]) {
    // Check if input is provided via command line
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " \"input_string\" [o|a|d]" << std::endl;
        std::cerr << "Example: " << argv[0] << " \"5; 2; 5; 5; 6; 6; 10\" o" << std::endl;
        std::cerr << "Order types:" << std::endl;
        std::cerr << "  o - Original order" << std::endl;
        std::cerr << "  a - Ascending order" << std::endl;
        std::cerr << "  d - Descending order" << std::endl;
        return 1;
    }

    // Determine order preservation type
    IntArrProcessor::OrderPreservation orderType = IntArrProcessor::OrderPreservation::ORIGINAL;
    if (argc > 2) {
        std::string orderFlag = argv[2];
        if (orderFlag == "a") {
            orderType = IntArrProcessor::OrderPreservation::ASCENDING;
        }
        else if (orderFlag == "d") {
            orderType = IntArrProcessor::OrderPreservation::DESCENDING;
        }
        else if (orderFlag != "o") {
            std::cerr << "Invalid order type. Use 'o', 'a', or 'd'." << std::endl;
            return 1;
        }
    }

    // Combine all command-line arguments into a single string
    std::string in = argv[1];
    /*for (int i = 1; i < argc && i < 3; ++i) {
        in += std::string(argv[i]) + (i < argc - 1 ? " " : "");
    }*/

    // Process the input
    try {
        std::string result = IntArrProcessor::processInt(in, orderType);
        std::cout << "Input: " << in << std::endl;
        std::cout << "Output: " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error processing input: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}