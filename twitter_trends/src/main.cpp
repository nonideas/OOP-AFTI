#include "../test/test.h"
#include "UsersManager.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    std::ifstream inp("tweets.txt");
    if (!inp) {
        cerr << "Enter correct path to write and read text files";
    }
    std::stringstream stream;
    stream << inp.rdbuf();
    inp.close();
    UsersManager users(stream);
    Parser::ParseTweet tweet("228 2000 <eee>, <kkk>, <eee>");
    users.add_tweet(tweet);
    cout << users.get_users().at(228).get_tweets()[0].get_hashtags()[0] << endl;
    return RUN_ALL_TESTS();
}