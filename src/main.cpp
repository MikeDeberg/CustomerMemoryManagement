#include <iostream>
#include <fstream>

// Project Specific
#include "definitions.h"
#include "compactPointer.h"
#include "trie.h"
#include "memmg.h"

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


int main(int argc, char **argv) {
    cout << "Test Smart gitPointer to Trie" << "\n";

    CompactPointer<Trie> prefix = new Trie();
    cout << "Pointer size: " << sizeof(&prefix) << "\n";;

    // creating input stream for handling FASTA file
    ifstream ifs;
    // opening input FASTA file
    ifs.open ("test_in.fasta", ifstream::in);

    // creating record struct and char for end of file probe
    record this_record;
    char x;

    // while there is another character in the FASTA file
    while( ifs.get(x)) {
        // retrieve one record from FASTA file
        this_record = get_record(ifs);
        prefix->add(this_record.sequence);
        cout << "Prefix Length: " << prefix->get_size() << "\n";
    }

    ifs.close();

    return 0;
}
