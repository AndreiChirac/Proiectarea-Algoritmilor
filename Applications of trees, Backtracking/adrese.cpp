#include <bits/stdc++.h>
using namespace std;

struct user {
    string name;
    vector <string> addresses;
    user(string n, vector < string > & a) {
        this -> name = n;
        this -> addresses = a;
    }
};
/* comparator used for sorting firstly by number of emails and if the number
is equal we sort by name*/
struct cmp {
    inline bool operator()(const user & u1,
        const user & u2) {
        if (u1.addresses.size() == u2.addresses.size()) {
            return u1.name < u2.name;
        }
        return u1.addresses.size() < u2.addresses.size();
    }
};

int main() {
    int N, i, j;
    int nr_adr;
    string name, adr, current_main_adr, new_main_adr;
    // maps every email address to the main address it is associated with
    unordered_map <string, string> points_to;
    /* for every email address, stores a vector of all the addresses that
    refer to it */
    unordered_map <string, vector <string>> references;
    /* maps every main address to its user's name */
    unordered_map <string, string> adr_to_name;

    ifstream input_file("adrese.in");
    ofstream output_file("adrese.out");

    input_file >> N;

    for (i = 0; i < N; ++i) {
        input_file >> name >> nr_adr;
        for (j = 0; j < nr_adr; ++j) {
            input_file >> adr;
            /* In case j == 0 we know the fact that it is the main adress of
            the user */
            if (j == 0) {
            	/* we have to search in the map in order to know the address 
            	we read is new or it has appeared and the name we read is a
            	person that has appeared before */
                auto it = points_to.find(adr);
                /* the adress has not been found so the persone is not an
                impostor */
                if (it == points_to.end()) {
                    current_main_adr = adr;
                    /* we make the main adresss to point to itself */
                    points_to[adr] = adr;
                    /* */
                    references[adr] = {
                        adr
                    };
                    /* we add the name to the main adress because in the end
                    we will need the name witch is first lexicographically */
                    adr_to_name[adr] = name;
                } else {
                    current_main_adr = it -> second;
                    /* if the new name is smaller lexicographically than the
                    one that is at the main address we need that the new one
                    must take it place because we want the smallest one */
                    if (name < adr_to_name[it -> second]) {
                        adr_to_name[it -> second] = name;
                    }
                }
            } else {
            	/* we read secundary adresses so we also need to find out if
            	they exist somewhere else */
                auto it = points_to.find(adr);
                /* in case it has not been found we associate the current
                adress with the main addres in points_to and in references we
                insert in the vector (vector of secundary adresses) the new
                secundary adress
                */
                if (it == points_to.end()) {
                    points_to[adr] = current_main_adr;
                    references[current_main_adr].push_back(adr);
                } else {
                	/* the key has been found so we know that in the points_to 
                	map the value is the main adress */
                    new_main_adr = it -> second;
                    /* in case that the main address is not the one that we 
                    found we have to perform the following commands */
                    if (new_main_adr != current_main_adr) {
                    	/* we need to move every secundary adress to the new
                    	main adress*/
                        for (auto it2 = references[current_main_adr].begin();
                        	it2 != references[current_main_adr].end(); ++it2) {
                            points_to[* it2] = new_main_adr;
                            references[new_main_adr].push_back(* it2);
                        }

                        references.erase(current_main_adr);
                        /* in case that at the name coresponding to the new
                        main adress is better we store the new one*/
                        if (adr_to_name[current_main_adr] <
                            adr_to_name[new_main_adr]) {
                            adr_to_name[new_main_adr] =
                        	adr_to_name[current_main_adr];
                        }
                        adr_to_name.erase(current_main_adr);
                        current_main_adr = new_main_adr;
                    }
                }
            }
        }
    }
    /* we build an array of users in order to build our output*/
    vector < user > users;
    for (auto it = references.begin(); it != references.end(); ++it) {
        sort(it -> second.begin(), it -> second.end());
        users.push_back(user(adr_to_name[it -> first], it -> second));
    }
    sort(users.begin(), users.end(), cmp());

    output_file << users.size() << '\n';
    for (auto it = users.begin(); it != users.end(); ++it) {
        output_file << it -> name << ' ' << it -> addresses.size() << '\n';
        for (auto it2 = it -> addresses.begin();
        	it2 != it -> addresses.end(); ++it2) {
            output_file << * it2 << '\n';
        }
    }
    input_file .close();
    output_file.close();
    return 0;
}
