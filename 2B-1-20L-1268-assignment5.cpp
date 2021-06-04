#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<string>
#include<windows.h>
using namespace std; 


class CreatingGrid{
	private:
		int wordsinthefile;
		bool fileopen;
		string wordInput[15];
		string sorting;
		int count;
		int placeword = 0;
		int i = 0;
		int rowsofgrid;
		int colsofgrid;
		char** WordGrid;	
	public:
	
		CreatingGrid(){
				wordsinthefile = 0;
				fileopen = false;
				count = 0;
				placeword = 0;
				i = 0;
				int rowsofgrid = 0;
				int colsofgrid = 0;
				WordGrid = 0;
		     }
		
        void NumberofWords(string nameoffile){
			int loop = 0;
			
			ifstream openfile(nameoffile);
			if(!openfile)
			{
				fileopen = false;
			}
			else
			{
				fileopen = true;
			}
			
			while(!openfile.eof())
			{
				openfile >> wordInput[loop];
				loop++; // adding to loop index
				count++; // adding to the count of words taken as input from file
			}
			
			openfile.close();
			
			cout<<"Enter how many words are in the file"<<endl;
			cin>>wordsinthefile;
			
			if(wordsinthefile != count)
			{
				cout<<"You have entered incorrect number of words in the file ";
				cout<<endl;
			}
			else
			{
				cout<<"I HAVE READ THE FOLLOWING WORDS FROM FILE: "<<endl<<endl;
				for(int i = 0 ; i<= count ; i++)
				{
					cout<<wordInput[i]<<" ";
				}
				cout<<endl<<endl;
			}
		
		}
		
		bool RowsAndCols(){
			cout<<"Enter Number of Rows of Grid"<<endl;
			cin>>rowsofgrid;
			cout<<"Enter Number of Cols of Grid"<<endl;
			cin>>colsofgrid;
			
			for (int i = 0; i < wordsinthefile; i++)
			{
				if (rowsofgrid < wordInput[i].length() || colsofgrid < wordInput[i].length())
				{
					return false;
				}
			}
			
			WordGrid = new char*[rowsofgrid];
			for(i =  0 ; i < rowsofgrid ; i++)
			{
				WordGrid[i] = new char[colsofgrid];
			}
			
			return true;
		}
		
		void SortedWords(){
			cout<<"WORDS SORTED: "<<endl<<endl;
			for(int i = 0 ; i < count - 1 ; i++)
			{
				for(int j = i + 1 ; j < count ; j++)
				{
					int stringonelength = wordInput[i].length();
					int stringtwolength = wordInput[j].length();
			
					if(stringonelength < stringtwolength)   	
					{	
						sorting = wordInput[i];      // sorting in descending order as larger words are placed first in the grid making it easier for the smaller words to fill the remaining place            
						wordInput[i] = wordInput[j];
						wordInput[j] = sorting;    
					}
				}
			}
	
			for(int i = 0 ; i <= count ; i++)
			{
				cout<<wordInput[i]<<" ";
			}
			cout<<endl<<endl;    // the words which are read from file are displayed in sorted order
		}
		
		void SettingGridToEmpty(){
		
			for (int i = 0; i < rowsofgrid; i++)
			{
				for (int j = 0; j < colsofgrid; j++)
				{
					WordGrid[i][j] = ' ';	// grid is initialized and all values are set to empty
				}
			}
		}
		
		void GenerateWordPosition(){
			
			
			int placeword = 0;  // this decides if the function of diagonal , vertical or horizontal is going to be called
			int q = 0; //to control loop index
	
			while(q < count )   // so all words can be placed 
			{
				placeword = rand() % 3;     // %3 since we have 3 functions and we want the words to be placed randomly using it
				
				if(placeword == 2)
				{
					int MatrixRow , MatrixCol;
					int matrixboundsforrow = ((rowsofgrid+1) - wordInput[q].length());    // calculates the bounds/limit for words
					int matrixboundsforcol = ((colsofgrid+1) - wordInput[q].length());
					MatrixRow = rand() % matrixboundsforrow;
					MatrixCol = rand() % matrixboundsforcol;
					bool occupied = 0; // space occupied or not
					int wordlength = wordInput[q].length();
	
					for( int i = MatrixCol , j = 0 , x = MatrixRow ; j < wordlength ; i++ , j++ , x++) // checks if the word can be placed within bounds and there is enough space
					{
						if(wordInput[q][j] == WordGrid[x][i]) //checking overlapping
						{	
							occupied = 1;  // can place word
						}
						else if((WordGrid[x][i] == ' '))
						{
							occupied = 1;  // can place word
						}
						else
						{
							occupied = 0; // cannot place word as space not available or out of bounds
							break;
						}
					}
	
					if(occupied != 0)
					{
						int i = 0 ;
						while( wordInput[q][i] != '\0')
						{
							WordGrid[MatrixRow][MatrixCol] = wordInput[q][i];
							i++;
							MatrixRow++;   // cols and rows are incremented since word is being placed diagonally
							MatrixCol++;
							//q++;	
						}
						q++;
						
					}
	
					 //q++;// index is incremented and next word is brought up to be placed			
				}
		
				if(placeword == 1)
				{
					int MatrixRow , MatrixCol;
					int matrixboundsforrows = ((colsofgrid+1) - wordInput[q].length()); // checking if word is in the bounds of the matrix
					int matrixboundsforcols = ((rowsofgrid+1) - wordInput[q].length());
					
					MatrixCol = rand() % matrixboundsforcols; // so word is in bounds
					MatrixRow = rand() % rowsofgrid;   // location on matrix is randomly selected
		
					bool occupied = 0; // already explained
					int wordlength = wordInput[q].length();
		
		
			for( int i = MatrixCol , j = 0 ; j < wordlength ; i++ , j++ )
			{
				if(wordInput[q][j] == WordGrid[MatrixRow][i]) 
				{
					occupied = 1;
				}
				else if(WordGrid[MatrixRow][i] == ' ')
				{
					occupied = 1;
				}
				else
				{
					occupied = 0;
					break;
				}
			}
			
			if(occupied != 0)
			{
				int i = 0 ;
				while( wordInput[q][i] != '\0')
				{
					WordGrid[MatrixRow][MatrixCol] = wordInput[q][i];
					i++;
					MatrixCol++;	// only col increases since horizontally ------
					//q++;
				}
				q++;
				
			}
			//q++;
						
		}
			
			if(placeword == 0)
			{
				
					int MatrixRow , MatrixCol;
					int matrixboundsforrows = ((rowsofgrid+1) - wordInput[q].length()); // checking if word is in the bounds of the matrix
					int matrixboundsforcols = ((colsofgrid+1) - wordInput[q].length());
					
					MatrixRow = rand() % matrixboundsforrows; // so word is in bounds
					MatrixCol = rand() % colsofgrid;   // location on matrix is randomly selected
		
					bool occupied = 0; // already explained
					int wordlength = wordInput[q].length();
		
		
			for( int i = MatrixRow , j = 0 ; j < wordlength ; i++ , j++ )
			{
				if(wordInput[q][j] == WordGrid[i][MatrixCol]) 
				{
					occupied = 1;
				}
				else if(WordGrid[i][MatrixCol] == ' ')
				{
					occupied = 1;
				}
				else
				{
					occupied = 0;
					break;
				}
			}
			
			if(occupied != 0)
			{
				int i = 0 ;
				while( wordInput[q][i] != '\0')
				{
					WordGrid[MatrixRow][MatrixCol] = wordInput[q][i];
					i++;
					MatrixRow++;	// only row increases since vertically |
					//q++;
				}
				q++;
			}
			//q++;
				
		}
	}
				
}

	void CheckEmptyPlaces(){
		
		for(int i = 0 ; i < rowsofgrid ; i++)
		{		
			for(int j = 0 ; j < colsofgrid ; j++)
			{
				if(WordGrid[i][j] == ' ')  // if grid is empty 
				{
			 		do{
						WordGrid[i][j] = rand();  // fill grid with a random alphabet
			      }while(!(WordGrid[i][j]>=65 && WordGrid[i][j]<=90));
				}
			}
		}
	}

		void OutputGrid(string nameoffile){
		
		ofstream FileWrite(nameoffile);
		
		for(int i = 0 ; i < rowsofgrid ; i++)
			{
				for(int j = 0 ; j < colsofgrid ; j++)
				{
					FileWrite<<WordGrid[i][j]<<" ";  // write to the file we created
					cout<<WordGrid[i][j]<<" "; // display on console screen
				}
				cout<<endl;
				FileWrite<<endl;
			}
	
			FileWrite.close();
		}
		

};


class SearchingGrid{
	
	private:
		char** wordgrid;
		int matrixrows;
		int matrixcols;
		int testcases;
		int counter;
		bool check;
		bool match;
		string listofwords[15];
		int wordlength;
		int m;
	public:
		SearchingGrid(){
			
			wordgrid = 0;
			matrixrows = 0;
			matrixcols = 0;
			testcases = 0;
			counter = 0;
			check = false;
			//match = false;
			wordlength = 0;
			//listofwords = 0;
			m = 0;
			for (int i = 0; i < 15; i++)
			{
				listofwords[i] = " ";
			}
		}
		
		void GridInput(string myfile1, string myfile2){
			
			ifstream file1(myfile1);
			ifstream file2(myfile2);
			
			file2>>matrixrows;
			file2>>matrixcols;
			file2>>testcases;
			
			wordgrid = new char*[matrixrows];
			for(int i = 0 ; i < matrixrows ; i++)
			{
				wordgrid[i] = new char[matrixcols];
			}
			
			for( int i = 0 ; i < matrixrows ; i++)
			{
				for(int j = 0 ; j < matrixcols ; j++)
				{
					file1>>wordgrid[i][j] ; // characters from file are inputted into the matrix
				}
			}
			
			file1.close();
			file2.close();
		
			cout<<endl;
			cout<<" GRID READ FROM FILE "<<endl;
			
			for(int i = 0 ; i < matrixrows ; i++)
            {
				for(int j = 0 ; j < matrixcols ; j++)
            	{
                	cout<<wordgrid[i][j]<<" "; // the grid with inputted characters is displayed on console
                	Sleep(3);
        		}
        		cout<<endl;
        	}
			
	}
		
		void InputWordsFromFile(string myfile){
			
			
			ifstream file2(myfile);
			
			int ignore1;
			
			file2>>ignore1;
			file2>>ignore1;
			file2>>ignore1;
			
			for(int i = 0 ; i < testcases ; i++)
			{
				file2>>listofwords[i];
			}
			
			for(int i = 0 ; i < testcases ; i++)
			{
				cout<<listofwords[i]<<" ";
			}
			
			file2.close();
		}
		
		void checkword(string filename){
			
			ofstream output(filename);
			
			int forloop = 0;
			bool check = false;
			bool match = false;
			
			while(m < testcases)
			{
				match = false;  // to check if word matches/found
				check = false;
				
				wordlength = listofwords[m].length(); // built in function to calculate length of the string
				
				//RIGHTTOLEFT CHECK
				for(int i = 0 ; i < matrixrows ; i++ ) //grid searching
				{
					for(int j = matrixcols - 1 ; j >= 0 ; j--)  //grid searching
					{
						if(wordgrid[i][j] == listofwords[m][0]) // if first character matches
						{
							for(int x = 1 ; x < wordlength ; x++) //to check for remaining characters
							{
								if(wordgrid[i][j-x] != listofwords[m][x]) //decreasing collumn number since we are comparing backward horizontally
								{
									match = false;
									break;	//jumps out of loop if a character doesnt matches
								}
								else
								{
									match = true;
								}
							}
				
							if(match != false) // if word matches then print on console and in the created file
							{
								output << endl << listofwords[m] << " FROM (" << i << ", " << j << ") TO (" << i << ", " << j - wordlength + 1 << ") \n";
								cout << endl << listofwords[m] << " FROM (" << i << ", " << j << ") TO (" << i << ", " << j - wordlength + 1 << ") \n";	
								check = true;
							}
						}
					}
				}
				
				
				//LEFT TO RIGHT 
				for(int i = 0 ; i < matrixrows ; i++) 
				{			
					for(int j = 0 ; j < matrixcols ; j++)
						{                                        //grid traversing ( done in programming fundamentals lab aswell )
							if(wordgrid[i][j] == listofwords[m][0])
							{
								for(int x = 1 ; x < wordlength ; x++)
								{
									if(wordgrid[i][j+x] != listofwords[m][x]) //collumn number being added each time since this horizontal checking
									{
										match = false;
										break;
									}
									else
									{
										match = true;
									}
								}
				
								if(match != false) //explained
								{
									output << endl << listofwords[m] << " FROM (" << i << ", " << j << ") TO (" << i << ", " << j + wordlength - 1 << ") \n";	
									cout << endl << listofwords[m] << " FROM (" << i << ", " << j << ") TO (" << i << ", " << j + wordlength - 1 << ") \n";
									check = true;
								}
							}
						}
				}
				
				
				//TOP TO BOTTOM
				
				for(int j = 0 ; j < matrixrows-1 ; j++)
				{		
					for(int i = 0 ; i < matrixcols-1 ; i++)
					{
						if(wordgrid[j][i] == listofwords[m][0])
						{
							for(int x = 1 ; x < wordlength ; x++)
							{
								if(wordgrid[j + x][i] != listofwords[m][x])  // row number being increased since this is checking vertically forward
								{
									match = false;
									break;
								}
								else
								{
									match = true;
								}
							}
				
							if(match != false)
							{
								output << endl << listofwords[m] << " FROM (" << i << ", " << j << ") TO (" << i + wordlength - 1 << ", " << j << ")\n";	
								cout << endl << listofwords[m] << " FROM (" << i << ", " << j << ") TO (" << i + wordlength - 1 << ", " << j << ")\n";
								check = true;
							}
						}
					}
				}
				
				
				// BOTTOM TO TOP
				
				for(int i = 0 ; i < matrixcols - 1 ; i++)
				{
					for(int j = matrixrows - 1 ; j >= 1 ; j--)
					{
						if(wordgrid[j][i] == listofwords[m][0])
						{
							for(int x = 1 ; x < wordlength ; x++)
							{
								if(wordgrid[j - x][i] != listofwords[m][x]) //row number being decreased since this is checking vertically backward now
								{
									match = false;
									break;
								}
								else
								{
									match = true;
								}
							}
							
							if(match != false)
							{
								output << endl << listofwords[m] << " FROM (" << i << ", " << j << ") TO (" << i - wordlength + 1 << ", " << j << ")\n";	
								cout << endl << listofwords[m] << " FROM (" << i << ", " << j << ") TO (" << i - wordlength + 1 << ", " << j << ")\n";
								check = true;
							}
						}
					}
				} 
				
				// RIGHT DIAGONAL
				
				for(int i = 0 ; i < matrixcols - 1 ; i++)
				{
					for(int j = 1 ; j < matrixrows  ; j++)
					{
						if(wordgrid[i][j] == listofwords[m][0])
						{
							for(int x = 1 ; x < wordlength ; x++)
							{
								if(wordgrid[i + x][j + x] != listofwords[m][x]) // for forward diagonal checking both the row and collumn is incremented
								{
									match = false;
									break;
								}
								else
								{
									match = true;
								}
							}
							
							if(match != false)
							{
								output << endl << listofwords[m] << " FROM (" << i << ", " << j << ") TO (" << i + wordlength - 1 << ", " << j + wordlength - 1 << ")\n";	
								cout << endl << listofwords[m] << " FROM (" << i << ", " << j << ") TO (" << i + wordlength - 1 << ", " << j + wordlength - 1 << ")\n";
								check = true;
							}
						}
					}
				}
				
				// LEFT DIAGONAL 
				
				for(int i = 0 ; i < matrixcols - 1 ; i++)
				{
					for(int j = 1 ; j < matrixrows - 1 ; j++)
					{
						if(wordgrid[i][j] == listofwords[m][0])
						{
							for(int x = 1 ; x < wordlength ; x++)
							{
								if(wordgrid[i - x][j - x] != listofwords[m][x])  //// for backward diagonal checking both the row and collumn is decremented
								{
									match = false;
									break;
								}
								else
								{
									match = true;
								}
							}
							
							if(match != false)
							{
								output << endl << listofwords[m] << " FROM (" << i << ", " << j << ") TO (" << i - wordlength + 1 << ", " << j - wordlength + 1 << ")\n";	
								cout << endl << listofwords[m] << " FROM (" << i << ", " << j << ") TO (" << i - wordlength + 1 << ", " << j - wordlength + 1 << ")\n";
								check = true;
							}
						}
					}
				}	
				
				
				if(match == false && check == false)
				{
					cout<<listofwords[m]<<"      WORD NOT FOUND ";
					cout<<endl;
				}
				
			m++;		
			}//counter loop main loop
			
			output.close();
		}
};



int main()
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	char option;
	char temp;
	cout<<"****************************************************************************************************************"<<endl;
    Sleep(600);
    
    cout<<"              				WELCOME TO WORD SEARCH GAME                		   "<<endl;
    Sleep(600);
	cout<<"****************************************************************************************************************"<<endl;		
	
	cout<<endl;
	cout<<endl;
	
	cout<<"****************************************************************************************************************"<<endl;
    Sleep(600);
    
    cout<<"              		     		PLEASE SELECT AN OPTION 							"<<endl;
	cout<<"			C : CREATE GRID"<<endl;
	cout<<"			S : SEARCH WORDS FROM GRID"<<endl;
	cout<<"			Q : QUIT GAME"<<endl;

    Sleep(600);
    cout<<endl;
	cout<<"****************************************************************************************************************"<<endl;		
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	
	cin>>option;
	
	while (option != 'Q' && option != 'q')
	{
		if(option == 'C' || option == 'c')
		{
			cout<<"OPTION 1 SELECTED "<<endl<<endl;
			string filename;
			string outfile;
			cout<<"Enter File Name For List Of Words "<<endl;	
			cin>>filename;
			CreatingGrid obj;
			obj.NumberofWords(filename);
			obj.SortedWords();
			
			if (obj.RowsAndCols() == true)
			{
				cout<<"Enter Output File Name to Place Grid"<<endl;
				cin>>outfile;
				cout<<endl;
				cout<<endl;
				obj.SettingGridToEmpty();
				obj.GenerateWordPosition();
				obj.CheckEmptyPlaces();
				obj.OutputGrid(outfile);
				cout << "\nGrid successfully created!";
			}
			else
			{
				cout << "\nGrid can not be formed.";
			}
			
			
			cout<<endl;
			cout << "\nPress any key to return to home screen:\t";
			cin >> temp;
			system("cls");
		}
		else if(option == 'S' || option == 's' )
		{
			cout<<"OPTION 2 SELECTED"<<endl<<endl;
			string secondfile;
			string searchfile;
			string outputfile;
			cout<<"Enter File Name to Read Grid "<<endl;
			cin>>secondfile;		
			cout<<"Enter File Name for Inputting Search List "<<endl;
			cin>>searchfile;
			cout<<"Enter Output File Name to Store Result "<<endl;
			cin>>outputfile;
			SearchingGrid newobj;
			newobj.GridInput(secondfile,searchfile);
			newobj.InputWordsFromFile(searchfile);
			newobj.checkword(outputfile);
			cout << "\nPress any key to return to home screen:\t";
			cin >> temp;
			system("cls");
		}
		cout<<"****************************************************************************************************************"<<endl;
	    Sleep(600);
	    
	    cout<<"              		     		PLEASE SELECT AN OPTION 							"<<endl;
		cout<<"			C : CREATE GRID"<<endl;
		cout<<"			S : SEARCH WORDS FROM GRID"<<endl;
		cout<<"			Q : QUIT GAME"<<endl;
	
	    Sleep(600);
	    cout<<endl;
		cout<<"****************************************************************************************************************"<<endl;		
		cin >> option;
	}
	cout<<"\nEXITING PROGRAM ";
	return 0;
}
