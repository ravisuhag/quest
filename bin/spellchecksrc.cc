#include <algorithm>
#include <iostream>
#include <string>
#include <set>
#include <fstream>
#include <sstream>


using namespace std;

#define debug
//#undef debug
#define as 26

#define cw 0.8
#define vw 0.4
#define rw 1.0

double pw[100];

bool is_vowel(char c) {
  if(c=='a' || c=='e' || c=='i' || c=='o' || c=='u') return true;
  return false;
}


struct snode {
  snode *a[as];
  bool end;
  snode *p;
  int l;
  int c;
  double x;
  snode() {
    for(int i=0; i<as; i++) a[i] = 0;
    end = false;
    p = 0;
    l = -1;
    c = -1;
    x = 0.0;
  }
  snode(snode *p2, int c2) {
    for(int i=0; i<as; i++) a[i] = 0;
    end = false;
    p = p2;
    l = p->l+1;
    c = c2;
    x = p->x+rw*(is_vowel(c2+'a')?vw:cw);
  }
};

int c2=0;

void insert(int p, snode *cur, string &s) {
#ifdef debug
  c2++;
  if(c2<=20 && c2>=0) {
    //cout<<"inserting: "<<p<<" "<<s<<endl;
  }
#endif
  if(p==s.size()) {
    cur->end = true;
    return;
  }
  if(!cur->a[s[p]-'a']) cur->a[s[p]-'a'] = new snode(cur,s[p]-'a');
  insert(p+1,cur->a[s[p]-'a'],s);
}


string acc(snode *cur) {
  if(cur->l==-1) return "";
  return acc(cur->p)+(char)(cur->c+'a');
}


set<string> a;
set<pair<double,string> > ans;
string p;
double dp[100][100];
snode *root;


string transform(string x) {
  string ret = "";
  for(int i=0; i<x.size(); i++) {
    if(x[i]<='Z' && x[i]>='A') ret+=x[i]+'a'-'A';
    else if(x[i]<='z' && x[i]>='a') ret+=x[i];
  }
  return ret;
}

double go3(int p1, int p2, snode *cur) {
  if(p1==-1) return cur->x;
  if(p2==-1) return pw[p1];
    //if(p1==-1 || p2==-1) return 1+max(p1,p2);
  //assert(dp[p1][p2]>=0.0);
  return dp[p1][p2];
}

void go2(int p1, int p2, char c, snode *cur) {
  if(p2==-1) return;
  double f = 0.5+max(0.0,(10.0-cur->l)/20.0);
  dp[p1][p2] = 1e9;

  dp[p1][p2] = min(dp[p1][p2],go3(p1-1,p2,cur)+f*(is_vowel(p[p1])?vw:cw));
  dp[p1][p2] = min(dp[p1][p2],go3(p1,p2-1,cur->p)+f*(is_vowel(c)?vw:cw));
  double res=1.0;
  if(is_vowel(p[p1])) res*=vw; else res*=cw;
  if(is_vowel(c)) res*=vw; else res*=cw;
  dp[p1][p2] = min(dp[p1][p2],go3(p1-1,p2-1,cur->p)+f*(p[p1]==c?0.0:res));
  
}


void go4(snode *cur) {
  for(int i=0; i<p.size(); i++) {
    go2(i,cur->l,cur->c+'a',cur);
  }
  if(cur->end==true) {
    //cout<<"Trying: "<<acc(cur)<<" "<<dp[p.size()-1][cur->l]<<" "<<cur->l<<endl;
    // for(int i=0; i<p.size(); i++) cout<<dp[i][cur->l]<<" ";
    //cout<<endl;
    ans.insert(make_pair(dp[p.size()-1][cur->l],acc(cur)));
    if(ans.size()>10) ans.erase(*ans.rbegin());
  }
  //if(ans.size()>0 && dp[p.size()-1][cur->l]>ans.rbegin()->first) return;
  for(int i=0; i<26; i++) {
    if(cur->a[i]) go4(cur->a[i]);
  }
}

void init2() {
  root = new snode;
  a.clear();
  int tot = 0;
  cout<<"Calling init function";
  
  ifstream fin("product_names.txt");
  string s;

#ifdef debug
  int c1 = 0;
#endif
  string s2;
  while(getline(fin,s2)) {
    tot++;
    s = s2;
#ifdef debug
    c1++;
    //if(c1<20) cout<<"Read: "<<s<<endl;
#endif

    stringstream ss(s);
    while(ss>>s) {
      s = transform(s);
      //      if(s=="hme") cout<<"from: "<<s2<<endl;
#ifdef debug
      if(c1<20) {
	//cout<<"Tokenized into: "<<s<<endl;
      }
#endif
      if(s.size()>0) {
	insert(0,root,s);
	//a.insert(s);
      }
    }
  }
#ifdef debug
  cout<<tot<<endl;
#endif
}




/*
double go(int p1, int p2, string s) {
  if(p1==-1 || p2==-1) return 1+max(p1,p2);
  if(dp[p1][p2]>=0.0) return dp[p1][p2];
  dp[p1][p2] = 1e9;
  dp[p1][p2] = min(dp[p1][p2],go(p1-1,p2,s)+1);
  dp[p1][p2] = min(dp[p1][p2],go(p1,p2-1,s)+1);
  dp[p1][p2] = min(dp[p1][p2],go(p1-1,p2-1,s)+(p[p1]==s[p2]?0:1));
  return dp[p1][p2];
}
*/

string final_ans;

void doit(string s) {
  ans.clear();
  p = s;
  p = transform(p);
  //assert(p.size()>0);
  for(int i=0; i<p.size(); i++) {
    pw[i] = rw*(i>0?pw[i-1]:0.0)+(is_vowel(p[i])?vw:cw);
  }
#ifdef debug
  cout<<"P: "<<p<<endl;
#endif
  string fname = "ans_"+s+".txt";
  ofstream fout(fname.c_str());
  /*
  for(set<string>::iterator it = a.begin(); it!=a.end(); it++) {
    if(!it->size()) continue;
    for(int i=0; i<p.size(); i++){ 
      for(int j=0; j<it->size(); j++) {
	dp[i][j] = -1.0;
      }
    }
    double x = go(p.size()-1,it->size()-1,*it);
    ans.insert(make_pair(x,*it));
    if(ans.size()>10) ans.erase(*ans.rbegin());
  }
  */
  for(int i=0; i<p.size(); i++) {
    for(int j=0; j<100; j++) {
      dp[i][j] = -1.0;
    }
  }
  go4(root);
  final_ans = "";
  for(set<pair<double,string> >::iterator it = ans.begin(); it!=ans.end(); it++) {
    fout<<it->second<<" "<<it->first<<endl;
    final_ans+=it->second;
    final_ans+=";";
  }
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  clock_t start = clock();
  init2();
#ifdef debug
  cout<<"Took: "<<(double)(clock()-start)/CLOCKS_PER_SEC<<"s."<<endl;
#endif
  string s= "home";
  start = clock();
  doit(s);  
#ifdef debug
  cout<<"Took: "<<(double)(clock()-start)/CLOCKS_PER_SEC<<"s."<<endl;
#endif
  
  s = "lappy";
  start = clock();
  doit(s);
#ifdef debug
  cout<<"Took: "<<(double)(clock()-start)/CLOCKS_PER_SEC<<"s."<<endl;
#endif
  
  return 0;
}