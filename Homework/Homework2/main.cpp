#include <iostream>
#include <fstream>
#include <sstream>
using std::string;
using std::cin;
using std::cout;
using std::ofstream;
using std::ifstream;
using std::endl;
using std::stringstream;
struct wordItem
{

    wordItem()
    {
        word="NULL";
        count=-1;    
    };
    wordItem(string newWord, int newVal)
    {
        word=newWord;
        count=newVal;
    }
    string tostring()
    {
        return word;
    }
    string word;
    int count;
};
void getStopWords(string ignoreWordFileName,string ignoreWords[]);

bool isStopWord(string word,string ignoreWords[]);

int getTotalNumberNonStopWords(wordItem list[],int length);

void arraySort(wordItem list[], int length);

void printTopN(wordItem wordItemList[],int topN);

void loadWordArray(string filename,wordItem words[],string ignoreWords[]);

int splitLine(string line, string *splitLineArrayptr);




int main(int argc, char const *argv[])
{
    if(argc<4)
    {
        cout<<"You ran the program without enough command line arguments, the program will now exit!"<<endl;
        std::exit(1);
    }

    int topN=std::stoi(argv[1]);
    string bookFile=argv[2];
    string ignoreFile=argv[3];

    string *stopwords= new string[50];
    wordItem *wordsptr= new wordItem[100];

    getStopWords(ignoreFile,stopwords);

    loadWordArray(bookFile,wordsptr,stopwords);

}
bool isStopWord(string word,string ignoreWords[])
{
    for(int i=0; i<50;i++)
    {
        if(ignoreWords[i]==word)
        {
            return true;
        }
    }
    return false;
}

void loadWordArray(string filename,wordItem words[],string ignoreWords[])
{
    ifstream filein(filename);
    string line;
    string *splitLineptr=NULL;
    while(getline(filein,line))
    {
        if(line!="\n")
        {
            splitLineptr=new string[2];
            splitLine(line,splitLineptr,&splitLineptr);
        }
    }

}
int splitLine(string line, string *splitLineArrayptr,string **addrToArrPtr)
{
    stringstream splitter(line);
    string word;
    int arrayitemcount=0;
    int arraysize=2;
    while(getline(splitter,word,' '))
    {
        if(arrayitemcount==arraysize)
        {
            arraysize*=2;
            string *temp=new string[arraysize];
            for(int i=0; i<arraysize;i++)
            {
                temp[i]="NULL";
            }
            for(int i=0; i<arrayitemcount; i++)
            {
                temp[i]=splitLineArrayptr[i];
            }
            delete [] splitLineArrayptr;
            splitLineArrayptr=temp;
            temp=NULL;
        }
        splitLineArrayptr[arrayitemcount++]=word;
    }
    *addrToArrPtr=splitLineArrayptr;
    return arrayitemcount;
}
void getStopWords(string ignoreWordFileName,string ignoreWords[])
{
    ifstream ignorefilein(ignoreWordFileName);
    string line;
    int ignorearrayIndex=0;
    while(getline(ignorefilein,line))
    {
        ignoreWords[ignorearrayIndex]=line;
        ignorearrayIndex++;
    }
    ignorefilein.close();
}
