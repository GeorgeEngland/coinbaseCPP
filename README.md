# coinbaseCPP
## Build Docker Image
### docker build --pull --rm -f "Dockerfile" -t cpp:latest "."
## Enter Docker Image
### docker run --rm -it  cpp:latest
## Run Benchmarks
### ./build/release/testMe

--------------------------------------------------------------------

Benchmark                          Time             CPU   Iterations

--------------------------------------------------------------------

BM_HANDLE_SNAP                  9.02 ms         9.02 ms           68

BM_HANDLE_L2                   0.463 us        0.463 us      1521808

BM_HANDLE_X_L2THREADS/1         54.0 us         40.4 us        17556

BM_HANDLE_X_L2THREADS/2         72.9 us         60.6 us        11561

BM_HANDLE_X_L2THREADS/4          115 us          103 us         6915

BM_HANDLE_X_L2THREADS/8          276 us          269 us         2495

BM_HANDLE_X_L2THREADS/16         709 us          694 us         1017

BM_HANDLE_X_L2THREADS/32        1322 us         1298 us          552

BM_HANDLE_X_L2THREADS/64        2284 us         2253 us          299

BM_HANDLE_X_L2THREADS/128       4287 us         4237 us          163

BM_HANDLE_X_L2THREADS/256       8331 us         8244 us           84


## Run App
### ./build/release/coin
Expect Your Book to look like:

__________ YOUR BOOK ___________


Ask Prices: 214102  214111  214112  214112  214119  214124  214132  214136  214146  214147

Bid Prices: 214101  214100  214081  214051  214044  214038  214034  214023  214007  214000

Ask Quants: 18.7919  15.3588  16.443  9.34319  0.25  7.93422  14.4946  9.34252  39.6  1

Bid Quants: 0.0957123  0.0916843  3  7.30749  1.808  14.0159  15.4402  3.65445  0.0909333  2
