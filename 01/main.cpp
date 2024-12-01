#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

/*
 * Specify input file parameters.
 * The file is expected to contain a two-column list of uint32s.
 */
static constexpr string_view INPUT_FILENAME = "input";
using input_elem_t = int;

void read_file(vector<input_elem_t> &col0, vector<input_elem_t> &col1) {
    /*
     * Open the input file.
     */
    ifstream file_stream(INPUT_FILENAME);
    const bool input_opened = file_stream.is_open();
    if (!input_opened) {
        cerr << "Error: Failed to open input file." << endl;
        exit(1);
    }

    /*
     * Read the input file.
     */
    input_elem_t col0_number{0}, col1_number{0}, line_number{0};
    while (file_stream >> col0_number >> col1_number) {
        /*
         * Ensure that each line contains two unsigned ints.
         */
        const bool line_parse_failed = file_stream.fail();
        if (line_parse_failed) {
            cerr << "Error: Failed to parse line " << line_number << endl;
            exit(1);
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
}

void part1() {
    /*
     * Read the file into two vectors.
     */
    vector<input_elem_t> col0, col1;
    read_file(col0, col1);

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
        const auto distance = abs(col0[i] - col1[i]);
        sum_of_distances += distance;
    }

    /*
     * Print the total distance.
     */
    cout << "Total distance: " << sum_of_distances << endl;
}

void part2() {
    /*
     * Read the file into two vectors.
     */
    vector<input_elem_t> col0, col1;
    read_file(col0, col1);

    /*
     * To find the similarity score:
     * - Create working sum and init to zero.
     * - Go through each element in the first list.
     *   - Count the number of that element in the second list.
     *   - Multiply the count by the number and add to score.
     */
    int similarity_score{0};
    for (size_t i = 0; i < col0.size(); i++) {
        const size_t num_elems = count(col1.begin(),
                                       col1.end(),
                                       col0[i]);
        similarity_score += col0[i] * num_elems;
    }

    cout << "Similarity score: " << similarity_score << endl;
}

int main() {
    part2();
}
