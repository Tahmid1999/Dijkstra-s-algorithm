///Dijkstra

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<iomanip>
#include<windows.h>


using namespace std;



 class Lebel{
 private:
    int cost;
    int parent_field;
    bool flag;


  public:


      void set_cost(int x){

      cost=x;
      }


      void set_parent_field(int y){

      parent_field=y;
      }

      void set_flag(bool z){

      flag=z;
      }

      int get_cost(){
            return cost;
      }

      int get_parent_field(){
            return parent_field;
      }

      bool get_flag(){
            return flag;

      }

  };



///Prototypes
void create_graph(int** &, int );
void populate_graph(int** X,int s,int low,int high,int parcentage);
void display_graph(int** X,int s,int mx);
int max(int** X, int s);
int num_dig(int n);
void select_s_d(int& s,int& d,int n);
void randomized_s_d(int& s,int& d,int n);
void dijkstra(int** G,int n,int s,int d);
int findMinVertex(Lebel* lebel,int n);
void print_path(int s,int d,Lebel* &lebel,int n);



int main(){
   int **G;
   int n;
   int p;
   int low;
   int high;
   int s;
   int d;
   bool desicion=false;
   cout<<"Enter number of nodes :";
   cin>>n;
   create_graph(G,n);
   cout<<"How much connectedness do you want(your input consider as percentage): ";
   cin>>p;
   while(p>100){
    cout<<"Invalid!!! Please input value within 100 "<<endl;
    cout<<"How much connectedness do you want(your input consider as percentage): ";
    cin>>p;
   }
   cout<<"Enter the lowest weight :";
   cin>>low;
   cout<<"Enter the highest weight :";
   cin>>high;
   populate_graph(G,n,low,high,p);
   display_graph(G,n,max(G,n));
   int ch;

        cout<<"Enter [1] for select source & destination. "<<endl;
        cout<<"Enter [2] for randomized source & destination. "<<endl;
        cout<<"Enter [3] to Exit."<<endl;
        cout<<"Enter your choice..."<<endl;
 do{
        cout<<"Your choice :";
        cin>>ch;
        switch(ch){
        case 1: select_s_d(s,d,n);
                dijkstra(G,n,s,d);
                break;
        case 2: randomized_s_d(s,d,n);
                dijkstra(G,n,s,d);
                break;
        }
   }while(ch!=3);
   system("pause");
   return 0;

}

void create_graph(int** &X, int sz){
	X =new int*[sz];
    for(int i = 0; i < sz; i++)
    X[i] = new int[sz];
}

void populate_graph(int** X,int s,int low,int high,int parcentage){

 int count=0;

 double edges=parcentage/100.0;
 int max_edges=(s*(s-1))/2;
 double estimated_edges=(parcentage*max_edges)/100.00;

 if((estimated_edges-(int)estimated_edges)>=0.50)estimated_edges=(int)estimated_edges+1;


 cout<<"Your "<<parcentage<<"% densely graph is creating..........";

 clock_t start;
 double duration;

 start = clock(); // get current time


 while(true){
   srand(time(0));
   for(int i=0;i<s;i++){
     for(int j=0;j<s;j++){
        if(j==i){
            X[i][j]=0;
        }

        else if(j<i){
            X[i][j]=X[j][i];
        }

        else if(j>i){
              double val=(double)rand()/RAND_MAX;
               if(val<=edges){
                        X[i][j] = low+rand()%(high+1-low);
                        count++;
            }
            else {
                X[i][j]=-1;
            }
        }

      }

    }

    if(count==(int)estimated_edges){

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    system("cls");
    cout << "Your graph generation took "<< duration << " seconds" <<endl;
    break;

       }
   count=0;

   }

}


int max(int** X, int s){
	int mx=X[0][0];
	for(int i=0;i<s;i++){
      for(int j=0;j<s;j++){
		if(X[i][j]>mx)mx=X[i][j];
	}
	}
	return mx;
}



int num_dig(int n){
	if(n<10)return 1;
	return 1+num_dig(n/10);
}

void display_graph(int** X,int s,int mx){
  cout<<endl;
  for(int i=0;i<s;i++){
      for(int j=0;j<s;j++){
            cout<<setw(num_dig(mx)+2)<<X[i][j];
      }
      cout<<endl;
  }

}

void select_s_d(int& s,int& d,int n){

  cout<<"Enter source & destination between "<<"1 to "<<n<<endl;
  cout<<"Enter source node :";
  cin>>s;
  cout<<"Enter destination node :";
  cin>>d;

  while(s<1 || s>n || d<1 || d>n){
    cout<<"Invalid!!"<<endl;
    cout<<"Enter source & destination between "<<"1 to "<<n<<endl;
    cout<<"Enter source node :";
    cin>>s;
    cout<<"Enter destination node :";
    cin>>d;

  }

  s=s-1;
  d=d-1;

}

void randomized_s_d(int& s,int& d,int n){

 srand(time(0));
 s=rand()%n;
 while(true){
    srand(time(0));
    d=rand()%n;
    if(d!=s){
        break;
    }
 }


}




void dijkstra(int** G,int n,int s,int d){


bool desicion=false;
Lebel* lebel=new Lebel[n];
for(int i=0;i<n;i++){
    lebel[i].set_cost(-1);
    lebel[i].set_parent_field(-1);
    lebel[i].set_flag(false);
}

    lebel[s].set_cost(0);
    lebel[s].set_parent_field(s);
    lebel[s].set_flag(false);





for(int i =0; i<n; i++){
    int minVertex=findMinVertex(lebel,n);

     if(lebel[minVertex].get_cost()==-1 ){
        break;
    }
    else if(minVertex==d){
        desicion=true;
        print_path(s,d,lebel,n);
        break;
    }
    lebel[minVertex].set_flag(true);
    for(int j=0;j<n;j++){
        if(G[minVertex][j]>0 && !lebel[j].get_flag()){
            int cost=lebel[minVertex].get_cost()+G[minVertex][j];
             if(cost<lebel[j].get_cost() || lebel[j].get_cost()==-1){
                lebel[j].set_cost(cost);
                lebel[j].set_parent_field(minVertex);
             }
        }
    }
}

if (desicion==false){
    cout<<"Destination from "<<s+1<<" to "<<d+1<<endl;
    cout<<"There is no path"<<endl;
}

}

int findMinVertex(Lebel* lebel,int n){
        int minVertex=-1;

        for(int i=0;i<n;i++){
              if(!lebel[i].get_flag() && (minVertex==-1||(lebel[i].get_cost()>=0 && lebel[minVertex].get_cost()==-1) ||(lebel[i].get_cost()>=0 && lebel[minVertex].get_cost()>=0 && lebel[i].get_cost()<=lebel[minVertex].get_cost()))){
                minVertex=i;
            }
        }
        return minVertex;
}




void print_path(int s,int d,Lebel* &lebel,int n){
  cout<<"Destination from "<<s+1<<" to "<<d+1<<endl;
  int A[n];
  for(int i=0;i<n;i++){
    A[i]=-1;
  }
  int a=d;
  cout<<"Cost :"<<lebel[d].get_cost()<<endl;


  int i=0;
  while(true){
    A[i]=lebel[a].get_parent_field();
    a=lebel[a].get_parent_field();
    if(a==s){
        break;
    }
   i++;
  }


 cout<<"Path is :";
 for (int j=n-1;j>=0;j--){
        if(A[j]!=-1){
        cout << A[j]+1 << "=>";
        }
 }
        cout<<d+1<<endl;

delete []lebel;
delete []A;

}

