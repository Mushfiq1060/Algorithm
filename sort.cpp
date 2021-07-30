sort(x.begin(),x.end(),[this](pair<long long,long long>a,pair<long long,long long>b){
  if(a.first==b.first)
    return a.second<b.second;
  return a.first<b.first;
});
