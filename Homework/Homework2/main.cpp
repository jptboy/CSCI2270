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

int loadWordArray(string filename,string **array);

int splitLine(string line, string *splitLineArrayptr,string **memaddressofptrtoarray);




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
    string *allwords = new string[2];
    int wordcount = loadWordArray(bookFile,&allwords);

    

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

int loadWordArray(string filename,string **array)
{
    ifstream filein(filename);
    string line;
    string *splitLineptr=NULL;
    string *allwords=new string[2];
    int allwordsidx=0;
    int allwordssize=2;
    while(getline(filein,line))
    {
        if(line!=" ")
        {
            splitLineptr=new string[2];
            int linelength= splitLine(line,splitLineptr,&splitLineptr);

            for(int i=0;i<linelength;i++)
            {
                if(allwordsidx==allwordssize)
                {
                    allwordssize*=2;
                    string *temp=new string[allwordssize];
                    for(int i=0;i<allwordssize;i++)
                    {
                        temp[i]="NULL";
                    }
                    for(int i=0;i<allwordsidx;i++)
                    {
                        temp[i]=allwords[i];
                    }
                    delete [] allwords;
                    allwords=temp;
                    temp=NULL;
                }

                allwords[allwordsidx++]=splitLineptr[i];
            }
        }
    }
    string *correctsizearray=new string[allwordsidx];
    for(int i=0; i<allwordsidx;i++)
    {
        correctsizearray[i]=allwords[i];
    }
    delete [] allwords;
    allwords=NULL;
    *array = correctsizearray;
    return allwordsidx;
}
int splitLine(string line, string *splitLineArrayptr,string **memaddressofptrtoarray)
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
    string *correctsizearray=new string[arrayitemcount];
    for(int i=0; i<arrayitemcount; i++)
    {
        correctsizearray[i]=splitLineArrayptr[i];
    }
    delete [] splitLineArrayptr;
    splitLineArrayptr=NULL;
    *memaddressofptrtoarray=correctsizearray;
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
