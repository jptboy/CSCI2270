#include <iostream>
#include <fstream>
#include <sstream>
using std::string;
using std::cin;
using std::cout;
using std::ofstream;
using std::ifstream;
using std::endl;
using std::stringstream;//i am doing these individual using statements to avoid polluting the namespace
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
};//struct defintion
void getStopWords(string ignoreWordFileName,string ignoreWords[]);

bool isStopWord(string word,string ignoreWords[]);

int getTotalNumberNonStopWords(wordItem list[],int length);

void arraySort(wordItem list[], int length);

void printTopN(wordItem wordItemList[],int topN);

int loadWordArray(string filename,string **array);

int splitLine(string line, string *splitLineArrayptr,string **memaddressofptrtoarray);




int main(int argc, char const *argv[])
{
    //array doubling of structs starts line 127
    if(argc<4)
    {
        cout<<"You ran the program without enough command line arguments, the program will now exit!"<<endl;
        std::exit(1);
    }//we give an error if there is less than 4 arguments because the person did not run the file correctly

    int topN=std::stoi(argv[1]);//integer for topN words
    string bookFile=argv[2];
    string ignoreFile=argv[3];

    string *stopwords= new string[50];
    wordItem *wordsptr= new wordItem[100];
    int worditemctr=0;
    int worditemsize=100;

    getStopWords(ignoreFile,stopwords);//we call the getStopWords function which fills the stopwrods array in the heap
    string *allwords = new string[2];
    int wordcount = loadWordArray(bookFile,&allwords);//we get the total number of words in the file by calling this function and it also loads the allwords array with everyword in the file as a string
    
    

    int arraydoublings=0;//variable to track array doublings

    for(int i=0; i<wordcount;i++)
    {
        if(isStopWord(allwords[i],stopwords) ||  allwords[i]=="\n" || allwords[i]=="")//we take the array with all of the words and if the word is a stop word a newline or empty we change it to NULL
        {
            allwords[i]="NULL";
        }
    }


    /*
    Below is where we took care of the  NULL strings and placed every word that wasnt null into another array
    */

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
    wordItem *trasharraytosatisfyassignmentpdf=new wordItem[wordcount];//the assignment said we had to use the gettotalnonstopwords function and I did this to satisfy the requirement because I already found the total number of nonstop words prior

    for(int i=0; i<wordcount;i++)
    {
        if(isStopWord(trasharraytosatisfyassignmentpdf[i].word,stopwords))
        {
            trasharraytosatisfyassignmentpdf[i].word="NULL";
        }
    }
    for(int i=0;i<wordcount;i++)
    {
        wordItem newItem(allwords[i],1);
        trasharraytosatisfyassignmentpdf[i]=newItem;
    }

    /*
    Here is my array doubling algorithim where I fill the array of struts from the array of strings

    */
    for(int i=0;i<noncommoncount;i++)
    {
        if(worditemctr==worditemsize)//if the number of actual word items equals the actual size of the words item array
        {
            worditemsize*=2;//we multiply the size by two
            wordItem *temp= new wordItem[worditemsize];//create a new array in the heap and use a temp pointer to point to it

            for(int i=0; i<worditemctr;i++)
            {
                temp[i]=wordsptr[i];//we fill that new array with the stuff from the old array
            }
            delete [] wordsptr;//we delete the contents of the old array in the heap
            wordsptr=temp;//we point the pointer to the new array
            temp=NULL;//we set temp=NULL because we don't want it pointing to anything now
            arraydoublings++;//increment the amount of array doublings
        }
        
        wordItem newItem(allnoncommons[i],1);//as we are iterating through all the words in the array of strings called allnoncommons we generate word items with a count of 1
        //check if word already in array, if it is dont add just increment the count
        bool found=false;//we check to see if the word item is already in the array and if it is we just increment the count
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
            wordsptr[worditemctr++]=newItem;//if not we add it to the array
        }
    }


    arraySort(wordsptr,worditemctr);
    

    int uniques = worditemctr;
    int totalarraydoublings=arraydoublings;
    int totalnoncommonwords= getTotalNumberNonStopWords(trasharraytosatisfyassignmentpdf,wordcount);

    printTopN(wordsptr,topN);
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
//this function splits each line into a dynamically sized array(by calling splitline) and loads each word from each dynamically sized array into another dynamically sized array that holds all words and it returns the number of all words loaded
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
//splitting each line into a dynamically sized array
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
int getTotalNumberNonStopWords(wordItem list[],int length)
{
    int number=0;
    for(int i=0; i<length;i++)
    {
        if(!(list[i].word=="NULL" ||  list[i].word=="\n" || list[i].word==""))
        {
            number++;
        }
        
    }
    return number;
}
void arraySort(wordItem wordsptr[], int worditemctr)//wordsptr is list and worditemctr is the length
{
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
}
void printTopN(wordItem wordsptr[],int topN)
{
    for(int i=0; i<topN; i++)
    {
        cout << wordsptr[i].count << " - " << wordsptr[i].word << endl;
    }  
}