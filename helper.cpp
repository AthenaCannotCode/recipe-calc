//
// Created by athena on 16.05.25.
//


#include "helper.h"

#include <vector>

template <typename T> bool has(const std::vector<T> *vec, const char* element) {
    if constexpr (std::is_same_v<T, const char*>) {
        for (const T vec_el: *vec) {
            if (!strcmp(vec_el, element)) { return true; }
        }
    } else {
        for (const T &vec_el: *vec) {
            if (vec_el == element) { return true; }
        }
    }
    return false;
}

bool is_final(const char* item_id, Globals *globals) {
    return globals->items[item_id].final;
}

void print_item_vec(const std::vector<Item> &v) {
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i].name << ": " << v[i].amount << "\n";
    }
}

template <typename T> std::vector<T> insert(std::vector<T> vec, size_t idx, size_t dest) {
    T element = vec[idx];
    for (size_t i = idx; i > dest; --i) {
        vec[i] = vec[i - 1];
    }
    vec[dest] = element;
    return vec;
}

std::vector<Item> sort_mats(std::vector<Item> mats, Globals *globals) {
    for (size_t i = 0; i < mats.size(); ++i) {
        for (size_t j = i; j < mats.size() - 1; ++j) {
            if (mats[j] > mats[j + 1]) {
                std::swap(mats[j], mats[j + 1]);
            }
        }
    }
    return mats;
}

Item get_item_with_amount(const char* item_id, int amount, Globals *globals) {
    return {
        globals->items[item_id].id,
        globals->items[item_id].name,
        amount,
        globals->items[item_id].final
    };
}

template <typename T> pop_ret<T> pop_first(std::vector<T> v) {
    T ret_e = v[0];
    std::vector<T> ret_v = {};
    for (size_t i = 1; i < v.size(); ++i) {
        ret_v.push_back(v[i]);
    }
    pop_ret<T> ret = {
        ret_e,
        ret_v
    };
    return ret;
}


bool contains(const std::map<std::string, Item> &map, std::string k) {
    for (const std::pair<std::string, Item> item : map) {
        if (item.first == k) return true;
    }
    return false;
}