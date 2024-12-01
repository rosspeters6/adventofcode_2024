#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
int main() {
    /*
     * Specify input file parameters.
     * The file is expected to contain a two-column list of uint32s.
     */
    constexpr string_view INPUT_FILENAME = "input";
    using input_elem_t = int;

    /*
     * Open the input file.
     */
    ifstream file_stream(INPUT_FILENAME);
    const bool input_opened = file_stream.is_open();
    if (!input_opened) {
        cerr << "Error: Failed to open input file." << endl;
        return EXIT_FAILURE;
    }

    /*
     * Read the input file.
     */
    input_elem_t col0_number{0}, col1_number{0}, line_number{0};
    vector<input_elem_t> col0, col1;
    while (file_stream >> col0_number >> col1_number) {
        /*
         * Ensure that each line contains two unsigned ints.
         */
        const bool line_parse_failed = file_stream.fail();
        if (line_parse_failed) {
            cerr << "Error: Failed to parse line " << line_number << endl;
            return EXIT_FAILURE;
        }

        /*
         * Line parsed successfully. Add the ints to their respective lists.
         */
        col0.push_back(col0_number);
        col1.push_back(col1_number);

        /*
         * Keep the line number up to date in case of input file parsing errors.
         */
        line_number++;
    }

    /*
     * To calculate the total distance between lists:
     * - Sort lists, so "Nth smallest" share same index across both lists.
     *   - Worst case time complexity with std::sort: O(n*log(n)).
     * - Go through sorted lists and sum up the difference between each elem.
     *   - Worst case time complexity: O(n)
     */
    sort(col0.begin(), col0.end());
    sort(col1.begin(), col1.end());

    int sum_of_distances{0};
    for (size_t i = 0; i < col0.size(); i++) {
        const int distance = abs(col0[i] - col1[i]);
        sum_of_distances += distance;
    }

    /*
     * Print the total distance.
     */
    cout << "Total distance: " << sum_of_distances << endl;
    return EXIT_SUCCESS;
}
