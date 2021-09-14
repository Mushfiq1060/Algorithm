/** it does not cantains any duplicate value ***/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
using namespace std;
using namespace __gnu_pbds ;
template <typename PB>
using ordered_set = tree<PB,null_type,less<PB>,rb_tree_tag,tree_order_statistics_node_update> ;





/** if we use less_equal then ordered set contains duplicate value and upperbound act as
    lower bound and lower bound act as upperbound ***/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds ;
template <typename PB>
using ordered_set = tree<PB,null_type,less_equal<PB>,rb_tree_tag,tree_order_statistics_node_update> ;


/**

        *(s.find_by_order(x)) -> x'th element in ordered set
        s.order_of_key(x) -> position of x in ordered set if we insert x in ordered set

        s = {1,2,2,4,5,5,5,5,8,8};
        
        *(s.find_by_order(6)) -> 5
        *(s.find_by_order(3)) -> 4

        s.order_of_key(3) -> 3
        s.order_of_key(9) -> 10
        s.order_of_key(2) -> 1

**/
