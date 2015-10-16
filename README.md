# zRSplitByFixedSizeBars.c
C library for R to split integer vectors to equal size bars (could be equal volume bars for example). 
It returns the start and stop indexes of the vector where the volume split should occur.

1. Compile for R:
	R CMD SHLIB zSplitByFixedSizeBars.c

2. Load in R.
		
	Windows:
		dyn.load("zSplitByFixedSizeBars.dll")

	Linux:
		dyn.load("zSplitByFixedSizeBars.so")

3. Use:
	.Call("zSplitByFixedSizeBars", integerVector, intVolumeToSplitBy, intLengthOfTheIntegerVector)

4. Example and output:
	Input vector of volumes (note that indexes are from 1 to 4): 
	c(1200, 500, 700, 320)


	output of the C code in R:
	[1,]    1    1 1000
	[2,]    1    3 1000
	[3,]    3    4  720

	The output means that:
	From index 1 to index 1 volume is 1000, then from index 1 (we have 200 more there) to index 3 
	we have a volume of 1000 and finally from index 3 (we have 400 more there) to index 4 the volume is 720.

5. Benchmark:
	The code runs on ~100 million records in less then a second.
