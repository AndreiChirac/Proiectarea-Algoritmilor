#include <bits/stdc++.h>

using namespace std;

/* Unordered Map does not contain a hash function for a pair so we build a
custom hash function for pairs for the unordered_set */
struct pairhash {
 public:
    size_t operator()(const pair<int, int> &x) const {
        return hash<int>()(x.first) ^ hash<int>()(x.second);
    }
};

void back_sums(vector<int> pieces,
                unordered_set<pair<int, int>, pairhash> &set_sums,
                int index, int T) {
    /* check if we traversed all the pieces */
    if (index == pieces.size()) {
        return;
    }

    int curr_sum = 0;
    unordered_set<pair<int, int>, pairhash> copy_sums;

    /* for each piece, try to add i * piece_size to all other sums */
    for (int i = 1; i <= T; ++i) {
        curr_sum += pieces[index];

        /* Store all the new sums in a temporary set */
        for (auto it : set_sums) {
            if (it.second + i <= T) {
                copy_sums.insert(make_pair(it.first + curr_sum,
                	it.second + i));
            }
        }
        copy_sums.insert(make_pair(curr_sum, i));
    }

    /* add the pieces back to the main set and continue the backtracking */
    for (auto it : copy_sums) {
        set_sums.insert(it);
    }
    back_sums(pieces, set_sums, index + 1, T);
}

/* construct all the possible solutions using backtracking as in the
combination algorithm*/
void back_domains(vector<int> &pieces, vector<int> &solution,
                    int &max_val, int last_piece, int K, int N, int T) {
    /* we wil verify a solution when we already added N pieces to the
    solution  */
    if (pieces.size() == N) {
    	/* we use an unordered_set in order to store pairs between the sum and
    	the nr of pieces */
        unordered_set<pair<int, int>, pairhash> set_sums;
        /* store all the possible sums */
        vector<int> vector_sums;

        /* we get all the sums */
        back_sums(pieces, set_sums, 0, T);
        for (auto it : set_sums) {
            vector_sums.push_back(it.first);
        }
        /* we sort the sums obtained */
        sort(vector_sums.begin(), vector_sums.end());
        /* we remove the duplicates */
        vector_sums.erase(unique(vector_sums.begin(), vector_sums.end()),
                            vector_sums.end());

        /* compute the number of most consecutive numbers */
        int curr_val = 1, temp_max = 1;
        int last_compare = -1;
        /* we iterate through each sum and we check them to be consecutive, in
        case we start again*/
        for (auto it : vector_sums) {
        	if (it - last_compare == 1) {
            	curr_val =  curr_val + 1;
            } else {
            	curr_val = 1;
            }

            last_compare = it;
            /* we take the maximum number of consecutive sums*/
            if (temp_max < curr_val) {
                temp_max = curr_val;
            }
        }

        /* if it exceedes the already found maximum we will replace it */
        if (temp_max > max_val) {
            max_val = temp_max;
            solution = pieces;
        }
        return;
    }

    /* we construct all the possible combinations of pieces */
    for (unsigned int i = last_piece; i <= K; ++i) {
        pieces.push_back(i);
        back_domains(pieces, solution, max_val, i + 1, K, N, T);
        pieces.pop_back();
    }
}

void create_domains(vector<int> &solution, int &max_val, int K, int N, int T) {
    vector<int> pieces;
    /* we will start with the piece that has dimension 1 */
    pieces.push_back(1);
    back_domains(pieces, solution, max_val, 2, K, N, T);
}

int main() {
    ifstream input_file("lego.in");
    ofstream output_file("lego.out");
    int K, N, T;

    input_file >> K >> N >> T;

    vector<int> solution;
    int max_val = -1;

    create_domains(solution, max_val, K, N, T);

    output_file << max_val << "\n";
    for (int i = 0; i < solution.size(); ++i) {
        output_file << solution[i] << " ";
    }
    output_file << "\n";

    input_file.close();
    output_file.close();

    return 0;
}
