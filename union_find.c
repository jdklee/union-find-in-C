#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "union_find.h"

// You can use an 8-bit integer (a/k/a a byte, a/k/a an unsigned char)
// to hold ranks because they won�t ever get too big. (Why?)
typedef uint8_t rank_t;

// Represents a union-find having `size_` objects.
//
// C Invariants:
//  - `id_`   points to an initialized array of `size_` `object_t`s.
//  - `rank_` points to an initialized array of `size_` `rank_t`s.
//  - every element of the `id_` array is a valid index for the
//    `id_` array (i.e., it�s less than `size_`).
//
// Definitions:
//  - A *path* is a sequence of distinct indices i[0], i[1], ...,
//    i[k-1] such that id_[i[0]] == i[1] && id_[i[1]] == i[2] && ... &&
//    id_[i[k-2]] == i[k-1].
//  - The length of the path is `k`, the number of indices in the
//    sequence.
//  - A cycle is a path with id_[i[k-1]] = i[0].
//
// Union-find Invariants:
//  - There are no non-trivial cycles in the `id_` array; that is,
//    every cycle has length 1. (Those are the roots.)
//  - The ranks of the roots are upper bounds on the heights of
//    their trees; that is, for each index `r` such that id_[r] == r
//    there is no sequence of indices ending in `r` whose length
//    exceeds `rank_[r]`.
//
// (The values of `rank_[r]` for non-roots don�t matter.)
//
struct union_find
{
    object_t*  id_;
    rank_t*    rank_;
    size_t     size_;
};

union_find_t uf_create(size_t n)
{
    union_find_t result = malloc(sizeof(struct union_find));
    if (!result) {
        return NULL;
    }
    result->size_ = n;
    result->rank_ = malloc(n * sizeof(rank_t));
    result->id_ = malloc(n * sizeof(object_t));
    if (result->rank_==NULL){
        free(result);
        return NULL;
    }

    if(result->id_ ==NULL){
        free(result);
        return NULL;
    }
    for(size_t i =0; i<n; i++){
        result->rank_[i]= 0;
        result->id_[i]=  i;
    }
    return result;
}

void uf_destroy(union_find_t uf)
{
    free(uf->rank_);
    free(uf->id_);
    free(uf);
}

bool uf_union(union_find_t uf, object_t m, object_t n)
{
    //throw away old
    m = uf_find(uf, m); //m is the root
    n = uf_find(uf,n); // n is the root

    rank_t rank_m = uf->rank_[m];
    rank_t rank_n = uf->rank_[n];

    if (m==n){

        return false;
    }
    else {
        if (rank_m > rank_n) {
            uf->id_[n] = m;

        } else if (rank_m < rank_n) {
            uf->id_[m] = n;
        } else {
            uf->rank_[m] += 1;
            uf->id_[n] = m;
        }
        return true;
    }
}





object_t uf_find(union_find_t uf, object_t m)
{
    while (uf->id_[m]!= m){
        uf->id_[m]=uf->id_[uf->id_[m]];
        m=uf->id_[m];
    }
    return m;
}

bool uf_same_set(union_find_t uf, object_t m, object_t n)
{
    // Nothing to do.
    return uf_find(uf, m) == uf_find(uf, n);
}

size_t uf_size(union_find_t uf)
{
    // All good here.
    return uf->size_;
}