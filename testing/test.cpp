#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"


#include "../src/main.cpp"
#include "../src/trie.cpp"
#include "../src/memmg.cpp"


TEST_CASE("FASTA file can be read and stored in record", "[fasta_in]"){

    // creating input stream for handling FASTA formatted file
    ifstream ifs;
    // opening input (test) FASTA formatted file
    ifs.open ("test_in.fasta", ifstream::in);

    SECTION("Record is created and read from FASTA formatted file"){
        record this_record;
        this_record = get_record(ifs);

        REQUIRE( this_record->header == ">Header 1")
        REQUIRE( this_record->sequence ==\
            "GTACTACGTACTGATCGATCGACTGATGCATCTTATCGTATGCG")
    }

    ifs.close();
    
}

TESET_CASE("Entire FASTA file can be read and stored in separate records",\
    "[entire_fasta_in]"){

    // creating input stream for handling FASTA formatted file
    ifstream ifs;
    // opening input (test) FASTA formatted file
    ifs.open ("test_in.fasta", ifstream::in);

    SECTION("Record is created for each record in FASTA file"){
        record this_record;
        char x;

        this_record = get_record(ifs);

        REQUIRE( this_record->header == ">Header 1")
        REQUIRE( this_record->sequence ==\
            "GTACTACGTACTGATCGATCGACTGATGCATCTTATCGTATGCG")

        this_record = get_record(ifs);

        REQUIRE( this_record->header == ">Header 2")
        REQUIRE( this_record->sequence ==\
            "TGACTGACTAGATCGTACTACTAGCATCGATCGACTGACTCAGA")

        this_record = get_record(ifs);

        REQUIRE( this_record->header == ">Header 3")
        REQUIRE( this_record->sequence ==\
            "CGACTACTGACGTACGTACGTACTGATCTAGGCTGATCGGAGTC")

    }

    ifs.close();

}

TEST_CASE("Not Optimized", "[not_optimized]"){

    SECTION("Test Node"){
        Node *test_node = new Node();

        SECTION("Set/Get value"){
            test_node->set_value("A");

            REQUIRE( test_node->get_value() == "A")

            SECTION("Append/Get child"){
                Node *child_test_node = new Node();
                child_test_node->set_value("T");

                test_node->append_child(child_test_node);
                Node *test_returned_child = test_node->get_child("T");

                REQUIRE( test_returned_child->get_value() == "T");
            }
        }
    }

    SECTION("Test Trie"){
        Trie *test_trie = new Trie();

        SECTION("Get size"){

            REQUIRE( test_trie->get_size() == 1);

        }

        SECTION("Add empty string"){
            test_trie->add("");

            REQUIRE( test_trie.get_size() == 1);

        }

        SECTION("Add"){
            test_trie->add("ACGT");

            REQUIRE( test_trie->get_size() == 5);

            SECTION("Failed Search"){

                REQUIRE( test_trie->search("ACTG") == false);

            }

            SECTION("Successful Search"){

                REQUIRE( test_trie->search("ACGT") == true);

            }
        }


    }
}

TEST_CASE("Optimized", "[optimized]"){

    SECTION("Create Trie"){


    }
}
