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
    int worditemctr=0;
    int worditemsize=100;

    getStopWords(ignoreFile,stopwords);
    string *allwords = new string[2];
    int wordcount = loadWordArray(bookFile,&allwords);
    int arraydoublings=0;

    for(int i=0; i<wordcount;i++)
    {
        if(isStopWord(allwords[i],stopwords) ||  allwords[i]=="\n" || allwords[i]=="")
        {
            allwords[i]="NULL";
        }
    }

    int noncommonssize=2;
    int noncommoncount=0;
    string *allnoncommons=new string[noncommonssize];
    for(int i=0; i<wordcount;i++)
    {
        if(noncommoncount==noncommonssize)
        {
            noncommonssize*=2;
            string *temp=new string[noncommonssize];
            for(int i=0; i< noncommonssize;i++)
            {
                temp[i]="NULL";
            }

            for(int i=0;i<noncommoncount;i++)
            {
                temp[i]=allnoncommons[i];
            }
            delete [] allnoncommons;
            allnoncommons=temp;
            temp=NULL;
        }
        if(allwords[i]!="NULL")
            allnoncommons[noncommoncount++]=allwords[i];
    }
    
    for(int i=0;i<noncommoncount;i++)
    {
        if(worditemctr==worditemsize)
        {
            worditemsize*=2;
            wordItem *temp= new wordItem[worditemsize];

            for(int i=0; i<worditemctr;i++)
            {
                temp[i]=wordsptr[i];
            }
            delete [] wordsptr;
            wordsptr=temp;
            temp=NULL;
            arraydoublings++;
        }
        
        wordItem newItem(allnoncommons[i],1);
        //check if word already in array, if it is dont add just increment the count
        bool found=false;
        for(int j=0; j<worditemctr;j++)
        {
            if(newItem.word==wordsptr[j].word)
            {
                wordsptr[j].count++;
                found=true;
            }
        }
        if(!found)
        {
            wordsptr[worditemctr++]=newItem;
        }
    }


    for(int i=0;i<worditemctr;i++)
    {
        for(int j=0;j<worditemctr;j++)
        {
            if(wordsptr[i].count>wordsptr[j].count)
            {
                wordItem temp;
                temp = wordsptr[i];
                wordsptr[i]= wordsptr[j];
                wordsptr[j]=temp;
            }
        }
    }

    int uniques = worditemctr;
    int totalarraydoublings=arraydoublings;
    int totalnoncommonwords=noncommoncount;

    for(int i=0; i<topN; i++)
    {
        cout << wordsptr[i].count << " - " << wordsptr[i].word << endl;
    }    
    cout << "#" << endl;
    cout << "Array doubled: " << totalarraydoublings << endl;
    cout << "#" << endl;
    cout << "Unique non-common words: " << uniques <<endl;
    cout << "#" << endl;
    cout << "Total non-common words: " << totalnoncommonwords << endl;

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
