#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef struct{
    string name;
    char grade;
    int profit;
    map<int,tuple<int,int,int>> not_possible_to_attend;
} movie;
map<char,tuple<int,int,int>> movie_grade;
/*
    
*/
void classify(movie movies[4],vector<int> &v)
{
    int s=v.size(),x,y,z,p,q,r;
    for(int i=0;i<s;i++)
    {
        for(int j=0;j<4;j++)
        {
            tie(x,y,z)=movie_grade[char('A'+j)];
            if(v[i]>=x&&v[i]<=y)
            {
                /*for(int k=0;k<4;k++)
                {
                    tie(p,q,r)=movies[j].not_possible_to_attend[k];
                    if(v[i]>=p&&v[i]<=q)
                    {
                        r++;
                    }
                    movies[j].not_possible_to_attend[k]=make_tuple(p,q,r);
                }*/
                z++;
            }
            movie_grade[char('A'+j)]=make_tuple(x,y,z);
            
        }
    }
    for(int i=0;i<s;i++)
    {
        for(int j=0;j<4;j++)
        {
            tie(x,y,z)=movie_grade[movies[j].grade];
            if(v[i]>=x&&v[i]<=y)
            {
                for(int k=0;k<4;k++){
                tie(p,q,r)=movies[j].not_possible_to_attend[k];
                if(v[i]>=p&&v[i]<=q)
                    {
                        r++;
                    }
                    movies[j].not_possible_to_attend[k]=make_tuple(p,q,r);
                }
            }
        }
    }
}
void pre()
{
    movie_grade['A']=make_tuple(24,50,0);
    movie_grade['B']=make_tuple(15,25,0);
    movie_grade['C']=make_tuple(3,18,0);
    movie_grade['D']=make_tuple(45,70,0);
}
void post(movie movies[4])
{
    for(int i=0;i<4;i++)
    {
        movies[i].not_possible_to_attend[0]=make_tuple(3,20,0);
        movies[i].not_possible_to_attend[1]=make_tuple(21,40,0);

 
        movies[i].not_possible_to_attend[2]=make_tuple(41,49,0);
        movies[i].not_possible_to_attend[3]=make_tuple(50,70,0);
    }
}
int main(int argc, char const *argv[])
{
    pre();
    movie movies[4];
    int i;
    for(i=0;i<4;i++) cin>>movies[i].name;
    for(i=0;i<4;i++) cin>>movies[i].grade;
    for(i=0;i<4;i++) cin>>movies[i].profit;
    post(movies);
    int n;
    cin>>n;
    vector<int> visitors(n);
    for(i=0;i<n;i++) cin>>visitors[i];
    classify(movies,visitors);
    string s="0123";
    vector<string> ans;
    int mprofit=-1;
    /*for(i=0;i<4;i++)
    {
        cout<<movies[i].name<<' '<<movies[i].grade<<' '<<get<2>(movie_grade[movies[i].grade])<<'\n';
        for(int j=0;j<4;j++)
        {
            cout<<get<2>(movies[i].not_possible_to_attend[j])<<' ';
        }
        cout<<'\n';
    }*/
    do{
        int p=0;
        for(i=0;i<4;i++)
        {
            auto ch=movie_grade[movies[s[i]-'0'].grade];
            auto c=get<2>(ch)-get<2>(movies[s[i]-'0'].not_possible_to_attend[i]);
            p+=c*(movies[s[i]-'0'].profit);
        }
        if(p>mprofit)
        {
            ans.clear();
            ans.push_back(s);
            mprofit=p;
        }
        else if(p==mprofit)
        {
            ans.push_back(s);
        }
    }
    while(next_permutation(s.begin(),s.end()));
    for(auto &i:ans)
    {
        for(auto &ch:i)
        {
            cout<<movies[ch-'0'].name<<' ';
        }
        cout<<'\n';
    }
    cout<<"Maximum Profit: "<<mprofit;
    return 0;
}
 