// Kontenery
#include <vector>	// Tablica
#include <set>		// Zbiór
#include <map>		// Słownik

// Adaptery
#include <queue>	// Kolejka
#include <stack>	// Stos

#include <iostream>
#include <stdio.h>

#include "Slav.h"

#define REPORT_ADAPTERS showMeAdapterSizes(queueOfSlavs,stackOfSlavs)
#define REPORT_CONTAINERS showMeContainerSizes(vectorOfSlavs,setOfSlavs,mapOfSlavs)


#include <cstdlib>
#include <time.h>

using namespace std;

void showMeContainerSizes(vector <Slav *>, set <Slav *>, map <Slav *, Slav*>);
void showMeAdapterSizes(queue <Slav *>, stack <Slav *>);

void containers(Slav *, int);
void adapters(Slav *, int);

int main(int argc, char const *argv[])
{
	int n = 2 * atoi(argv[1]);
	Slav *slavs = new Slav[n];
	cout << "# Generated Slavs" << endl;
	for (int i = 0; i < n; ++i)
		cout << slavs[i].description() << endl;

	containers(slavs, n);
	adapters(slavs, n);

	delete [] slavs;
}

void containers(Slav * slavs, int n)
{
	vector <Slav *> vectorOfSlavs;
	set <Slav *> setOfSlavs;
	map <Slav *, Slav *> mapOfSlavs;
	
	printf("# Containers\n");
	REPORT_CONTAINERS;
	printf("## vector\n");

	// Umieść Słowian w losowej kolejności w wektorze.
	srand( time( NULL ) );
	vectorOfSlavs.push_back(&slavs[0]);
	
	for(int i=0;i<n-1;i++)
	{
		int g = rand()%vectorOfSlavs.size();
		vectorOfSlavs.insert(vectorOfSlavs.begin()+g,&slavs[i+1]);
	}

	// Wykorzystując iterator i funkcję description(), wyświetl wszystkich Słowian w wektorze

	vector<Slav*>::iterator it;
	for( it=vectorOfSlavs.begin(); it!=vectorOfSlavs.end(); ++it )
   	{
    	 cout<<(*it)->description()<<endl;
   	}


	REPORT_CONTAINERS;
	printf("## set\n");

	// Przenieś wszystkich Słowian z wektoru do zbioru.
	
   	for(int i=0;i<n;i++)
   	{
    	 setOfSlavs.insert(vectorOfSlavs[i]);
   		 vectorOfSlavs.pop_back();
   	}


	REPORT_CONTAINERS;
	printf("## map\n");

	// Stwórz słownik tworzący pary Słowian, z tych znajdujących się w zbiorze, czyszcząc zbiór
	
	map<Slav*,Slav*>::iterator itm;
	set < Slav*	>::iterator ito;
	set < Slav*	>::iterator itk;
	ito=setOfSlavs.begin();
	itk=setOfSlavs.begin();

	while(ito!=setOfSlavs.end())
	{
		mapOfSlavs[*ito++]=*ito++;
		setOfSlavs.erase(itk++);
		setOfSlavs.erase(itk++);
	}
	// Wykorzystując iterator, wyświetl wszystkie pary Słowian

 	for(itm=mapOfSlavs.begin();itm!=mapOfSlavs.end();itm++)
 		cout<<(*itm).first->description()<<" "<<(*itm).second->description()<<endl;


	REPORT_CONTAINERS;
}

void adapters(Slav * slavs, int n)
{
	queue <Slav *> queueOfSlavs;
	stack <Slav *> stackOfSlavs;

	printf("# Adapters\n");
	REPORT_ADAPTERS;
	printf("## queue\n");

	// Umieść Słowian w kolejce.
	
	for(int i=0;i<n;i++)
	queueOfSlavs.push(&slavs[i]);


	REPORT_ADAPTERS;

	printf("## stack\n");
	// Przenieś Słowian z kolejki do stosu.

	for(int i=0; i<n;i++)
	{
		stackOfSlavs.push(queueOfSlavs.front());
		queueOfSlavs.pop();
	}

	REPORT_ADAPTERS;

	// Wyświetl Słowian zdejmowanych ze stosu.

	for(int i=0;i<n;i++)
	{
		cout << (*(stackOfSlavs.top()))->description() << endl;
		stackOfSlavs.pop();
	}
	
	REPORT_ADAPTERS;
}

void showMeContainerSizes(vector <Slav *> vector, set <Slav *> set, map <Slav *, Slav*> map)
{
	printf("[vector_size = %lu, set_size = %lu, map_size = %lu, existingSlavs = %i]\n",
		vector.size(),
		set.size(),
		map.size(),
		Slav::counter());
}

void showMeAdapterSizes(queue <Slav *> queue, stack <Slav *> stack)
{
	printf("[queue_size = %lu, stack_size = %lu, existingSlavs = %i]\n",
		queue.size(),
		stack.size(),
		Slav::counter());

}
