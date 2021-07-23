#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "set.h"
#include "list.h"
#include "type_elem.h"

struct s_set{
    list sorted_list;
};

set set_empty(void){
    set s = NULL;
    s = calloc(1, sizeof(struct s_set));
    s->sorted_list = list_empty();
    return s;
}

set set_add(set s, type_elem e){
    unsigned int n =0;
    set saux = set_copy(s);
    bool b = false;
    type_elem k;
    while ((!set_is_empty(saux)) && (!b)){
        k = list_head(saux->sorted_list);
        if (k == e){
            b = true;
        }else if (k < e){
            n = n+1;
        }
        saux->sorted_list = list_tail(saux->sorted_list);
    }
    if (!b){
        assert(n <= set_cardinal(s));
        s->sorted_list = list_add_at(s->sorted_list,n,e);
    }
    saux= set_destroy(saux);
    return s;
}

unsigned int set_cardinal(set s){
    unsigned int N;
    N = list_length(s->sorted_list);
    return N;
}

bool set_is_empty(set s){
    bool b;
    b = list_is_empty(s->sorted_list);
    return b;
}

bool set_member(type_elem e, set s){
    bool b =false;
    set saux= set_copy(s);
    type_elem k;
    while ((!set_is_empty(saux)) && !b){
        k = list_head(saux->sorted_list);
        if (k == e){
            b = true;
        }else {
            saux->sorted_list = list_tail(saux->sorted_list);
        }
    }
    saux = set_destroy(saux);
    return b;
}

set set_elim(set s, type_elem e){
    set saux= set_copy(s);
    unsigned int n = 0;
    unsigned int l=0;
    type_elem k;
    while ((!set_is_empty(saux)) && (l!=1)){
        k = list_head(saux->sorted_list);
        if (k==e){
            l = l+1;
        }else{
            n= n+1;
            saux->sorted_list= list_tail(saux->sorted_list);
        }
    }
    s->sorted_list= list_elim_at(s->sorted_list, n);
    saux = set_destroy(saux);
    return s;
}

set set_union(set s, set s0){
    set saux = set_copy(s0);
    type_elem k;
    while (!set_is_empty(saux)){
        k = list_head(saux->sorted_list);
        s = set_add(s, k);
        saux->sorted_list = list_tail(saux->sorted_list);
    }
    saux = set_destroy(saux);
    return s;
}

set set_inters(set s, set s0){
    set saux = set_copy(s);
    type_elem k;
    while (!set_is_empty(saux)){
        k = list_head(saux->sorted_list);
        if (!set_member(k, s0)){
            s= set_elim(s,k);
        }
        saux->sorted_list= list_tail(saux->sorted_list);
    }
    saux = set_destroy(saux);
    return s;
}

set set_dif(set s, set s0){
    set saux= set_copy(s0);
    type_elem k;
    while(!set_is_empty(saux)){
        k = list_head(saux->sorted_list);
        if (set_member(k, s)){
            set_elim(s, k);
        }
        saux->sorted_list= list_tail(saux->sorted_list);
    }
    saux= set_destroy(saux);
    return s;
}

type_elem set_get(set s){
    assert(!set_is_empty(s));
    type_elem e;
    e= list_head(s->sorted_list);
    return e;
}

set set_copy(set s){
    set s1= set_empty();
    s1->sorted_list = list_copy(s->sorted_list);
    return s1; 
}

set set_destroy(set s){
    s->sorted_list = list_destroy(s->sorted_list);
    free(s);
    return s;
}


