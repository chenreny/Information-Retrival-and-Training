#include <iostream>
#include "csvstream.h"
#include <cmath>
#include <set>

using namespace std;
using rowType = std::map<std::string, std::string>;
using countType = std::map<std::string, int>;
using Pair_type = std::pair<std::string, std::string>;

class Classifier{
public:
    //MODIFIES: this
    //EFFECTS: read in data from train file, print some information and
    //initilize private member variable of this class, which is:
    //countWord<word, number in all posts>
    //countLabel<label, number in all posts>
    //countLabelWord<std::pair<label, word>, num>
    //setHelper is used to find all unique words in a post's content
    bool readData(string trainFile, string command){
        rowType word;
        try{
            csvstream csvin(trainFile);
            totalPost = 0;
            if(command == "--debug") cout << "training data:" << endl;
            while(csvin >> word){
                ++totalPost;
                if(command == "--debug"){
                    cout << "  label = " << word["tag"] << ",";
                    cout << " content = " << word["content"] << endl;
                }
                istringstream source(word["content"]);
                string singleWord;
                set<string> setHelper;
                while(source >> singleWord){
                    uniqueWords.insert(singleWord);
                    setHelper.insert(singleWord);
                }
                for(auto i : setHelper){
                    ++countWord[i];
                    Pair_type val = {word["tag"], i};
                    ++countLabelWord[val];
                }
                string label = word["tag"];
                ++countLabel[label];
            }
            cout << "trained on " << totalPost << " examples" << endl;
            if(command == "--debug"){
                cout << "vocabulary size = ";
                cout << uniqueWords.size() << endl;
            }
            cout << endl;
        }catch(csvstream_exception &e){
            cout << e.msg << endl;
            return false;
        }
        return true;
    }
    
    //MODIFIES:input string
    //EFFECTS:separate a string to a set of unique words
    set<string> unique_words(const string &str){
        istringstream source(str);
        set<string> words;
        string word;
        while(source >> word){
            words.insert(word);
        }
        return words;
    }
    
    //EFFECTS:count log prior
    double logPrior(string label){
        double result = log(countLabel[label] / static_cast<double>(totalPost));
        return result;
    }
    
    //EFFECTS:count loglikelihood
    double logLikelihood(string label, string word){
        double result = 0;
        Pair_type val = {label, word};
        if(countLabelWord.find(val) == countLabelWord.end()){
            if(countWord.find(word) == countWord.end()){
                result = log(1.0 / totalPost);
            }else{
                result = log(countWord[word] / static_cast<double>(totalPost));
            }
        }else{
            result = log(countLabelWord[val]
                         / static_cast<double>(countLabel[label]));
        }
        return result;
    }
    
    //EFFECTS:count log probability score for a given label and post
    double logProScore(string label, string post){
        istringstream source(post);
        set<string> uniqueWordsTest;
        string word;
        double result = logPrior(label);
        while(source >> word){
            uniqueWordsTest.insert(word);
        }
        for(auto i : uniqueWordsTest){
            result +=logLikelihood(label, i);
        }
        return result;
    }
    
    //EFFECTS:given a testfile, predict its label and print out information
    bool predict(string testFile, int &totalPostTest, double &rightResult){
        double correctPredict = 0;
        rowType word;
        try{
            csvstream csvin(testFile);
            while(csvin >> word){
                ++totalPostTest;
                double max = logProScore(countLabel.begin()->first,
                                         word["content"]);
                string predictLabel = countLabel.begin()->first;
                for(auto i : countLabel){
                    double temp = logProScore(i.first, word["content"]);
                    if(max < temp){
                        max = temp;
                        predictLabel = i.first;
                    }
                }
                if(word["tag"] == predictLabel) ++correctPredict;
                cout << "  correct = " << word["tag"] << ", ";
                cout << "predicted = " << predictLabel << ", ";
                cout << "log-probability score = " << max << endl;
                cout <<"  content = "<< word["content"] << endl << endl;
            }
        }catch(csvstream_exception &e){
            cout << e.msg << endl;
            return false;
        }
        rightResult = correctPredict;
        return true;
    }
    
    //MODIFIES:nothing
    //EFFECTS: help print class information
    void printClassHelper(){
        cout << "classes:" << endl;
        for(auto i : countLabel){
            cout << "  " << i.first << ", " << i.second << " examples, ";
            cout<<"log-prior = " << logPrior(i.first);
            cout << endl;
        }
    }
    
    //MODIFIES:nothing
    //EFFECTS: help print classifier information
    void printClassifierHelper(){
        cout << "classifier parameters:" <<endl;
        for(auto i : countLabel){
            for(auto j : countWord){
                Pair_type val = {i.first, j.first};
                if(countLabelWord.find(val) != countLabelWord.end()){
                    cout <<"  "<< i.first << ":";
                    cout << j.first <<", ";
                    cout <<"count = "<< countLabelWord[val];
                    cout << ", log-likelihood = ";
                    cout << logLikelihood(i.first, j.first) << endl;
                }
            }
        }
    }
    
private:
    set<string> uniqueWords;
    countType countWord;
    countType countLabel;
    std::map<Pair_type, int> countLabelWord;
    int totalPost;
    
    
public:
    set<string> getSet(){
        return uniqueWords;
    }
    
    countType getCountWord(){
        return countWord;
    }
    
    countType getCountLabel(){
        return countLabel;
    }
    
    std::map<Pair_type, int> getCountLabelWord(){
        return countLabelWord;
    }
    
    int getTotalPost(){
        return totalPost;
    }
};






int main(int argc, char* argv[]){
    cout.precision(3);
    if(argc != 3 && argc != 4){
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return 0;
    }
    if(argc == 4 && string(argv[3]) != "--debug"){
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return 0;
    }
    
    string trainFile = string(argv[1]);
    string testFile = string(argv[2]);
    string command = "";
    if(argc == 4) command = string(argv[3]);
    
    try{
        csvstream csv(trainFile);
        csvstream csv2(testFile);
    }catch(csvstream_exception &e){
        cout << e.msg << endl;
        return 0;
    }
    
    bool controlExit;
    Classifier myClassifier;
    controlExit = myClassifier.readData(trainFile, command);
    if(controlExit == false) return 0;
    if(command == "--debug"){
        myClassifier.printClassHelper();
        myClassifier.printClassifierHelper();
        cout << endl;
    }
    cout << "test data:" << endl;
    int totalPostTest = 0;
    double rightResult = 0;
    bool controlExit2;
    controlExit2 = myClassifier.predict(testFile, totalPostTest, rightResult);
    if(controlExit2 == false) return 0;
    cout << "performance: " << rightResult << " / " << totalPostTest;
    cout << " posts predicted correctly" << endl;
    
    return 0;
}

