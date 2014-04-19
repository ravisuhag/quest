
#define debug
//#undef debug

#include <algorithm>
#include <iostream>
#include <string>
#include <set>
#include <fstream>
#include <sstream>
#include <queue>
#include <map>
#ifdef debug
#include <cassert>
#endif
using namespace std;

#define as 27

#define cw 0.8
#define vw 0.41
#define rw 1.0
#define sp (char)('z'+1)

double pw[100];

bool is_vowel(char c) {
  if(c=='a' || c=='e' || c=='i' || c=='o' || c=='u') return true;
  return false;
}

string final_ans;

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
  //  assert(cur);
#ifdef debug
  c2++;
  if(c2<=100 && c2>=0) {
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


set<pair<double,string> > ans;
string p;
double dp[100][100];
snode *root;
snode *rot2;
map<string,double> freq;

bool find(int pos, string &s, snode *cur) {
  if(pos==s.size()) return true;
  if(!cur->a[s[pos]-'a']) return false;
  return find(pos+1,s,cur->a[s[pos]-'a']);
}

string transform(string x) {
  string ret = "";
  for(int i=0; i<x.size(); i++) {
    if(x[i]<='Z' && x[i]>='A') ret+=x[i]+'a'-'A';
    else if(x[i]<='z' && x[i]>='a') ret+=x[i];
  }
  return ret;
}

double go3(int p1, int p2, snode *cur) {
  if(p1==-1) return cur->x;//5.0;
  if(p2==-1) return pw[p1];
    //if(p1==-1 || p2==-1) return 1+max(p1,p2);
  //assert(dp[p1][p2]>=0.0);
  return dp[p1][p2];
}

void go2(int p1, int p2, char c, snode *cur) {
  if(p2==-1) return;
  double f = 1.0;//0.5+max(0.0,(10.0-cur->l)/20.0);
  dp[p1][p2] = 1e9;

  dp[p1][p2] = min(dp[p1][p2],go3(p1-1,p2,cur)+f*(is_vowel(p[p1])?vw:cw));
  dp[p1][p2] = min(dp[p1][p2],go3(p1,p2-1,cur->p)+f*(is_vowel(c)?vw:cw));
  double res=1.0;
  if(is_vowel(p[p1])) res+=vw; else res+=cw;
  if(is_vowel(c)) res+=vw; else res+=cw;
  res/=2.1;
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
    string y = acc(cur);
    ans.insert(make_pair(dp[p.size()-1][cur->l],y));//*(1.0/(1.0+freq[y])),y));
    if(ans.size()>20) ans.erase(*ans.rbegin());
  }
  //if(ans.size()>0 && dp[p.size()-1][cur->l]>ans.rbegin()->first) return;
  for(int i=0; i<26; i++) {
    if(cur->a[i]) go4(cur->a[i]);
  }
}

void init2() {
  root = new snode;
  rot2 = new snode;
  //a.clear();
  int tot = 0;
  
  ifstream fin("product_names.txt");
  string s;

#ifdef debug
  int c1 = 0;
#endif
  string s2,s3;
  while(getline(fin,s2)) {
    s3 = s2;
    tot++;
    s = s2;
    s2 = "";
#ifdef debug
    c1++;
    //if(c1<20) cout<<"Read: "<<s<<endl;
#endif

    stringstream ss(s);
    while(ss>>s) {
      s = transform(s);
      //if(s=="gol") cout<<"from2: "<<s3<<endl;
#ifdef debug
      if(c1<20) {
	//cout<<"Tokenized into: "<<s<<endl;
      }
#endif
      if(s.size()>0) {
	s2 += (s+sp);
	freq[s]++;//1.0/(1.0+freq[s]);
	insert(0,root,s);
	//a.insert(s);
      }
    }
    if(s2.size()>0) {
      //if(s2.find("gol{trolleys")!=string::npos) cout<<"From: "<<s3<<endl;
      //      b.push_back(s2);
      insert(0,rot2,s2);
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
  
}

priority_queue<pair<double,string>  > ans2;
vector<vector<pair<double,string> > > d;

string btrans(string x) {
  string ret = "";
  for(int i=0; i<x.size(); i++) {
    if(x[i]=='{') ret+=" ";
    else ret+=x[i];
  }
  return ret;
}

void doit2(string s) {
  final_ans= "";
  string fname = "ans_"+s+".txt";
  // ofstream fout(fname.c_str());
  d.clear();
  while(!ans2.empty()) ans2.pop();
  stringstream ss(s);
  int tp = 0;
  while(ss>>s) {
    s = transform(s);
    if(s.size()==0) continue;
    doit(s);
    tp++;
    vector<pair<double,string> > d2;
    int pp = 0;
    set<pair<double,string> > ans3;
    for(set<pair<double,string> >::iterator it = ans.begin(); it!=ans.end(); it++) {
      ans3.insert(make_pair(it->first*(10.0/(1.0+freq[it->second])),it->second));
    }
    ans = ans3;
    for(set<pair<double,string> >::iterator it = ans.begin(); it!=ans.end(); it++,pp++) {
      // fout<<"("<<it->second<<","<<it->first<<") ";
      //if(s=="granding") cout<<it->first<<" "<<it->second<<endl;
      if(pp<5) d2.push_back(make_pair(it->first,it->second));
    }
    // fout<<endl;
    d.push_back(d2);
    if(d2.size()!=5) {
      cout<<"WTF"<<endl;
#ifdef debug
      assert(false);
#endif
    }
  }
  int tot = 1;
  for(int i=0; i<tp; i++) tot*=5;
  cout<<"TOT: "<<tot<<endl;
  for(int i=0; i<tot; i++) {
    int cj = i;
    vector<string> tof;
    double cx = 0;
    for(int j=0; j<tp; j++) {
      tof.push_back(d[j][cj%5].second);
      cx+=(1.0/(1.0+d[j][cj%5].first));
      cj/=5;
    }
    sort(tof.begin(),tof.end());
    do {
      string ret = "";
      for(int j=0; j<tp; j++) {
	ret+=(tof[j]+sp);
      }
      if(find(0,ret,rot2)) {
	
	/*
      bool f = false;
      for(vector<string>::iterator it = b.begin(); it!=b.end() && (!f); it++) {
	bool f2 = true;
	for(int j=0; j<tp; j++) {
	  if(it->find(tof[j])==string::npos) {
	    f2 = false;
	    break;
	  }
	}
	f |= f2;
      }
      if(f) {
	*/
	ans2.push(make_pair(cx,ret));
      }
      
    } while(next_permutation(tof.begin(),tof.end()));

  }
  int tp2 = 0;
  while(!ans2.empty() && tp2<10) {
    tp2++;
    pair<double,string> tpp = ans2.top();
    // fout<<btrans(tpp.second)<<" "<<tpp.first<<endl;
    final_ans+= btrans(tpp.second)+";";
    //cout<<tpp.second<<" "<<tpp.first<<endl;
    ans2.pop();
  }

}  

string test[17] = {"home","lappy","vibratory granding","stainless steel sacrap","golf trollieys","duplex tuber","coton kurtis","bottle display stamds","self inking stamds","flask round botton","push botton switches","wedding carf","utility carf","extraction toolls","rubber gromnts","kids gromnts","asbestors fiber"};

//string test[] = {"golf trollieys"};

int main(int argc, char *argv[]) {
  srand(time(NULL));
  clock_t start = clock();
  init2();
#ifdef debug
  cout<<"Took: "<<(double)(clock()-start)/CLOCKS_PER_SEC<<"s."<<endl;
#endif
  for(int i=0; i<17; i++) {

  string s= test[i];
  start = clock();
   doit2(s);  
#ifdef debug
  //cout<<"Took: "<<(double)(clock()-start)/CLOCKS_PER_SEC<<"s."<<endl;
#endif
  }
  return 0;
}
