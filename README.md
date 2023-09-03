# coding-fun

`interval_map<K,V>` is a data structure that associates keys of type K with values of type V.
It is designed to be used efficiently in situations where intervals of consecutive keys are associated with the same value.

Constructor takes in default value as `minV` s.t. all queries `<` the minK is assigned `minV`.
K comparable by only `<` and V comparable by only `==`.
