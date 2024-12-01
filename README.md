# integer-Array-Operations

## IntArrProcessor: Process Integer Array with duplicates

This package processes an array of integers separated by semicolons (`;`).

**Functionality**

- Takes a string containing an array of integers separated by semicolons.
- Analyzes the occurrences of each integer.
- Returns a string containing:
    - Number of integers occurring multiple times.
    - Lowest duplicate integer (0 if no duplicates).
    - Highest duplicate integer (0 if no duplicates).
    - Elements of the input array without duplicates, preserving the original order (unless specified otherwise).

**Features**

- Supports different order types for the unique elements:
    - `ORIGINAL`: Preserves the original order (default).
    - `ASCENDING`: Sorts the unique elements in ascending order.
    - `DESCENDING`: Sorts the unique elements in descending order.

**Usage**

**Command Line:**

```
./IntArrProcessor "input_string" [o|a|d]
```

- `input_string`: String containing the integer array separated by semicolons.
- `[o|a|d]`: order type flag.

**Example:**

```
./IntArrProcessor "5; 2; 5; 5; 6; 6; 10" o  # Output with original order
./IntArrProcessor "5; 2; 5; 5; 6; 6; 10" a  # Output with ascending order
```

**Code Structure**

- `IntArrProcessor`: Class containing the processing logic.
    - `processInt`: Main function for processing the input string and returning the result.
        - Handles empty input.
        - Parses the input string into a vector.
        - Counts occurrences of each integer using an unordered_map.
        - Identifies duplicates and unique order.
        - Constructs the output string with counts, duplicates, and unique elements.
    - `parseInput`: Parses the input string into a vector of integers, handling leading/trailing whitespaces.
    - `preserveUniqueOrder`: Collects unique elements in the input order and applies sorting based on the order type.
- `main`: Entry point for the program.
    - Handles command-line arguments and validates input format.
    - Determines the order type flag.
    - Processes the input string using `IntArrProcessor::processInt`.

**Notes**

- The time complexity of this solution is O(N), which meets the desired efficiency target.
- The code utilizes standard C++ libraries for string manipulation, containers, and algorithms.

**Further Enhancements**

- Consider adding support for handling invalid input formats (e.g., non-numeric characters).
- Explore alternative approaches to improve performance if dealing with very large datasets.

