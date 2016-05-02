#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "../src/trie.cpp"

#include <string>


TEST_CASE("Not Optimized", "[not_optimized]"){

    Node *test_node = new Node();
    Node *child_test_node = new Node();

    SECTION("Set/Get value"){
        string test_a = "A";
        test_node->set_value(test_a[0]);

        REQUIRE( test_node->get_value() == test_a[0]);

    }

    SECTION("Append/Get child"){
        string test_a = "T";
        child_test_node->set_value(test_a[0]);

        test_node->append_child(child_test_node);
        Node *test_returned_child = test_node->get_child(test_a[0]);

        REQUIRE( test_returned_child->get_value() == test_a[0]);
    }


    SECTION("Get size"){
        Trie *test_trie = new Trie();
        REQUIRE( test_trie->get_size() == 0);
        test_trie->clear();
    }

    SECTION("Add empty string"){
        Trie *test_trie = new Trie();
        test_trie->add("");

        REQUIRE( test_trie->get_size() == 0);

        test_trie->clear();

    }

    SECTION("Add"){
        Trie *test_trie = new Trie();
        string seq = "ACGT";
        test_trie->add(seq);

        REQUIRE( test_trie->get_size() == 4);

        test_trie->clear();

    }

    SECTION("Failed Search"){
        Trie *test_trie = new Trie();
        string seq = "ACGT";
        test_trie->add(seq);
        string bad_seq = "ACTG";

        REQUIRE( test_trie->search(bad_seq) == false);

        test_trie->clear();

    }

    SECTION("Successful Search"){
        Trie *test_trie = new Trie();
        string seq = "ACGT";
        test_trie->add(seq);
        string test_seq = "ACGT";
        REQUIRE( test_trie->search(test_seq) == true);

        test_trie->clear();

    }
}

// TEST_CASE("Optimized", "[optimized]"){
//
//
//
// }
// TEST_CASE("FASTA file can be read and stored in record", "[fasta_in]"){
//
//     // creating input stream for handling FASTA formatted file
//     ifstream ifs;
//     // opening input (test) FASTA formatted file
//     ifs.open ("test_in.fasta", ifstream::in);
//
//     SECTION("Record is created and read from FASTA formatted file"){
//         record this_record;
//         this_record = get_record(ifs);
//
//         REQUIRE( this_record.header == ">Header 1");
//         REQUIRE( this_record.sequence == "GTACTACGTACTGATCGATCGACTGATGCATCTTATCGTATGCG");
//     }
//
//     ifs.close();
//
// }
//
// TEST_CASE("Entire FASTA file can be read and stored in separate records", "[entire_fasta_in]"){
//
//     // creating input stream for handling FASTA formatted file
//     ifstream ifs;
//     // opening input (test) FASTA formatted file
//     ifs.open ("test_in.fasta", ifstream::in);
//
//     SECTION("Record is created for each record in FASTA file"){
//         record this_record;
//         char x;
//
//         this_record = get_record(ifs);
//
//         REQUIRE( this_record.header == ">Header 1");
//         REQUIRE( this_record.sequence == "GTACTACGTACTGATCGATCGACTGATGCATCTTATCGTATGCG");
//
//         this_record = get_record(ifs);
//
//         REQUIRE( this_record.header == ">Header 2");
//         REQUIRE( this_record.sequence == "TGACTGACTAGATCGTACTACTAGCATCGATCGACTGACTCAGA");
//
//         this_record = get_record(ifs);
//
//         REQUIRE( this_record.header == ">Header 3");
//         REQUIRE( this_record.sequence == "CGACTACTGACGTACGTACGTACTGATCTAGGCTGATCGGAGTC");
//
//     }
//
//     ifs.close();
//
// }
