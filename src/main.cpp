#include <iostream>
#include <fstream>
#include <ctime>

// Project Specific
#include "definitions.h"
#include "trie.h"
#include "optimized_trie.h"
//#include "memmg.h"

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
    // creating input stream for handling FASTA file
    ifstream ifs;
    // opening input FASTA file
    ifs.open (argv[1], ifstream::in);

    // if the trie is to use the custom memory manager
    if (optimized){
        cout << "Starting optimized Trie construction..." << endl;
        clock_t construction_start = clock();
        memmg = new MemoryAllocator(sizeof(MEMMG_TYPE));

        OptTrie *prefix = new OptTrie();

        // creating record struct and char for end of file probe
        record this_record;
        char x;

        // while there is another character in the FASTA file
        while( ifs.get(x)) {
            // retrieve one record from FASTA file
            this_record = get_record(ifs);
            prefix->add(this_record.sequence);
            // cout << "Prefix Length: " << prefix->get_size() << "\n";
        }
        clock_t construction_time = construction_start - clock();
        cout << "Trie construction completed in "
             << 1000 * (construction_time / CLOCKS_PER_SEC)
             << "ms." << endl;
    }

    // if the trie is NOT to use the custom memory manager
    if(!optimized){
        cout << "Starting unoptimized Trie construction..." << endl;
        clock_t construction_start = clock();
        Trie *prefix = new Trie();

        // creating record struct and char for end of file probe
        record this_record;
        char x;

        // while there is another character in the FASTA file
        while( ifs.get(x)) {
            // retrieve one record from FASTA file
            this_record = get_record(ifs);
            prefix->add(this_record.sequence);
            // cout << "Prefix Length: " << prefix->get_size() << endl;
        }
        clock_t construction_time = construction_start - clock();
        cout << "Trie construction completed in "
             << 1000 * (construction_time / CLOCKS_PER_SEC)
             << "ms." << endl;
    }
    ifs.close();

    return 0;
}
