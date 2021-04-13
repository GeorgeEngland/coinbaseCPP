# coinbaseCPP
Uses gcc Docker Image.
## Build Docker Image
### docker build --pull --rm -f "Dockerfile" -t cpp:latest "."
## Enter Docker Image
### docker run --rm -it  cpp:latest
## Run Benchmarks
### ./build/release/testMe


## Run App
### ./build/release/coin
Expect Your Book to look like:

__________ YOUR BOOK ___________


Ask Prices: 214102  214111  214112  214112  214119  214124  214132  214136  214146  214147

Bid Prices: 214101  214100  214081  214051  214044  214038  214034  214023  214007  214000

Ask Quants: 18.7919  15.3588  16.443  9.34319  0.25  7.93422  14.4946  9.34252  39.6  1

Bid Quants: 0.0957123  0.0916843  3  7.30749  1.808  14.0159  15.4402  3.65445  0.0909333  2
