/// Written function inside the main function

/*

function(return type(data types of function parameters))function name = [&](function parameter)
{

};

*/

function<int(int,int)>get_sum=[&](int a,int b){
  return a+b;
};

function<void(int,int,int)>dfs=[&](int src,int par,int lev){
  res=max(res,lev);
  for(int i=0;i<g[src].size();i++){
    if(g[src][i]!=par){
      dfs(g[src][i],src,lev+1);
    }
  }
};

