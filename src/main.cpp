#include <iostream>
#include <fstream>
#include <ctime>

// Project Specific
#include "definitions.h"
#include "trie.h"
#include "optimized_trie.h"
//#include "memmg.h"

#define QUERY_CAP 10000

using namespace std;


// stores one header and one sequence each can be up to 80 cahracters long
struct record{
    string header;
    string sequence;
};


// retrieves a single record (header, sequence) from FASTA file
record get_record(ifstream& ifs){
    string this_header;
    string this_seq;
    getline(ifs, this_header);
    getline(ifs, this_seq);

    record new_record = {this_header, this_seq};

    return new_record;
}

MemoryAllocator *memmg;
int main(int argc, char **argv) {
    cout << argc << endl;
    // If there is an additional flag
    bool optimized = false;
    if (argc == 3){
        // If the flag is setting the runtime behavior to using the
        // custom memory manager
        if (*argv[2] == '!'){
            optimized = true;
        }
    }

    ifstream ifs;      // input stream for handling FASTA file
    ifstream queries;  // stream for queries; pointed at the same file as ifs

    ifs.open (argv[1], ifstream::in);
    queries.open (argv[1], ifstream::in);


    //Declaration of start time
    clock_t construction_start;
    clock_t construction_time;
    clock_t search_start;
    clock_t search_time;

    //Declare record struct and char for end of file probe
    record this_record;
    char x;

    // if the trie is to use the custom memory manager
    if (optimized){
        cout << "Starting optimized Trie construction..." << endl;
        memmg = new MemoryAllocator(sizeof(MEMMG_TYPE));

        //Begin Construction Portion
        construction_start = clock(); //start time initialiazation
        OptTrie *prefix = new OptTrie();
        // while there is another character in the FASTA file
        while( ifs.get(x) ) {
            // retrieve one record from FASTA file
            this_record = get_record(ifs);
            prefix->add(this_record.sequence);
        }
        construction_time = clock() - construction_start;

        cout << "Starting unoptimized Trie search..." << endl;
        search_start = clock();
        //Begin search portion
        for(int i = 1; queries.get(x) && i < QUERY_CAP; i++) {
            this_record = get_record(queries);
            prefix->search(this_record.sequence);
        }
        search_time = clock() - search_start;
    }

    // if the trie is NOT to use the custom memory manager
    if(!optimized){
        cout << "Starting unoptimized Trie construction..." << endl;
        construction_start = clock(); //start time initialiazation
        Trie *prefix = new Trie();
        // while there is another character in the FASTA file
        while( ifs.get(x)) {
            // retrieve one record from FASTA file
            this_record = get_record(ifs);
            prefix->add(this_record.sequence);
        }
        construction_time = clock() - construction_start;

        cout << "Starting unoptimized Trie search..." << endl;
        search_start = clock();
        //Begin search portion
        for(int i = 1; queries.get(x) && i < QUERY_CAP; i++) {
            this_record = get_record(queries);
            prefix->search(this_record.sequence);
        }
        search_time = clock() - search_start;
    }

    cout << "Trie construction completed in "
         << 1000 * (construction_time / CLOCKS_PER_SEC)
         << "ms." << endl;

    cout << "Trie search completed in "
         << 1000 * (construction_time / CLOCKS_PER_SEC)
         << "ms." << endl;

    ifs.close();

    return 0;
}
